#include <jni.h>
#include <string>
#include <android/log.h>
//使用这两个Window相关的头文件需要在CMake脚本中引入android库
#include <android/native_window_jni.h>
#include <android/native_window.h>
////编码
//#include <libavcodec/avcodec.h>
////封装格式处理
//#include <libavformat/avformat.h>
////像素处理
//#include <libswscale/swscale.h>
#include "libyuv.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
}

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

#define MAX_AUDIO_FRME_SIZE 48000 * 4

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_PlayerStudyBridge_decode(JNIEnv *env, jclass type, jstring input_, jstring output_) {
    LOGE("------%s start------", "decode");
    const char *input = env->GetStringUTFChars(input_, 0);
    const char *output = env->GetStringUTFChars(output_, 0);

    LOGI("input=%s",input);
    LOGI("output=%s",output);

    //1.注册所有组件，例如初始化一些全局的变量、初始化网络等等
    av_register_all();
//    avcodec_register_all();

    //封装格式上下文，统领全局的结构体，保存了视频文件封装格式的相关信息
    AVFormatContext *pformatContext = avformat_alloc_context();

    //2.打开输入视频文件
    int openInputReturn = avformat_open_input(&pformatContext,input,NULL,NULL);
    if(openInputReturn != 0){
        LOGE("%s","打开输入视频文件失败");
        return;
    }

    //3.获取视频文件信息，例如得到视频的宽高
    //第二个参数是一个字典，表示你需要获取什么信息，比如视频的元数据
    if(avformat_find_stream_info(pformatContext,NULL) < 0){
        LOGE("%s","无法获取视频文件信息");
        return;
    }

    //获取视频流的索引位置
    //遍历所有类型的流（音频流、视频流、字幕流），找到视频流
    int v_stream_idx = -1;
    int i = 0;
    for(;i< pformatContext->nb_streams;i++){
        AVMediaType avMediaType = pformatContext->streams[i]->codec->codec_type;
        LOGI("位置i=%d,avMediaType=%d",i,avMediaType);
        if(avMediaType == AVMEDIA_TYPE_VIDEO){
            v_stream_idx = i;
        }
    }

    if(v_stream_idx == -1){
        LOGE("%s","找不到视频流");
        return;
    }

    //只有知道视频的编码方式，才能够根据编码方式去找到解码器
    //获取视频流中的编解码上下文
    AVCodecContext *pCodecContext = pformatContext->streams[v_stream_idx]->codec;

    //4.根据编解码上下文中的编码id查找对应的解码
    AVCodec *pCodec = avcodec_find_decoder(pCodecContext->codec_id);
    //（迅雷看看，找不到解码器，临时下载一个解码器，比如视频加密了）
    if(pCodec == NULL){
        LOGE("%s","找不到解码器，或者视频已加密");
        return;
    }

    //5.打开解码器，解码器有问题（比如说我们编译FFmpeg的时候没有编译对应类型的解码器）
    if(avcodec_open2(pCodecContext,pCodec,NULL) != 0){
        LOGE("%s","解码器无法打开");
        return;
    }

    LOGI("视频的文件格式:%s",pformatContext->iformat->name);
    LOGI("视频时长:%lld",pformatContext->duration/1000000);
    LOGI("视频的宽高:%d,%d",pCodecContext->width,pCodecContext->height);
    LOGI("解码器的名称:%s",pCodec->name);

    //准备读取
    //AVPacket用于存储一帧一帧的压缩数据（H264）
    //缓冲区，开辟空间
    AVPacket *pPacket = (AVPacket *) av_malloc(sizeof(AVPacket));
    //内存分配
    AVFrame *pFrame = av_frame_alloc();
    //YUV420 用于存储解码后的像素数据(YUV)
    AVFrame *pFrameYUV = av_frame_alloc();

    //只有指定了AVFrame的像素格式、画面大小才能真正分配内存
    //缓冲区分配内存
    uint8_t *out_buffer = (uint8_t *) av_malloc(sizeof(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecContext->width,
                                                                          pCodecContext->height)));
    //初始化缓冲区
    avpicture_fill((AVPicture *)pFrameYUV,out_buffer,AV_PIX_FMT_YUV420P,pCodecContext->width,pCodecContext->height);

    //用于转码（缩放）的参数，转之前的宽高，转之后的宽高，格式等
    SwsContext *pSwsContext = sws_getContext(pCodecContext->width,pCodecContext->height,pCodecContext->pix_fmt,
                                  pCodecContext->width,pCodecContext->height,AV_PIX_FMT_YUV420P,SWS_BICUBIC,NULL,NULL,NULL);

    int got_picture,ret;
    FILE *fp_yuv = fopen(output,"wb+");

    int frame_count = 0;

    //6.一帧一帧的读取压缩数据
    while(av_read_frame(pformatContext,pPacket) >= 0){
        //只要视频压缩数据（根据流的索引位置判断）
        if(pPacket->stream_index == v_stream_idx){
            //7.解码一帧视频压缩数据，得到视频像素数据
            ret = avcodec_decode_video2(pCodecContext,pFrame,&got_picture,pPacket);
            if(ret < 0){
                LOGE("%s","解码错误");
                return;
            }

            //为0说明解码完成，非0正在解码
            if(got_picture){
                //AVFrame转为像素格式YUV420，宽高
                //2 6输入、输出数据
                //3 7输入、输出画面一行的数据的大小 AVFrame 转换是一行一行转换的
                //4 输入数据第一列要转码的位置 从0开始
                //5 输入画面的高度
                //TODO 编译错误，待解决
//                sws_scale(pSwsContext, pFrame->data, pFrame->linesize, 0,
//                          pCodecContext->height,
//                          pFrameYUV->data,
//                          pFrameYUV->linesize);


                int y_size = pCodecContext->width * pCodecContext->height;
                fwrite(pFrameYUV->data[0],1,y_size,fp_yuv);
                fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);
                fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);

                frame_count++;
                LOGI("解码第%d帧完成",frame_count);
            }
        }
        av_free_packet(pPacket);
    }

    fclose(fp_yuv);

    av_frame_free(&pFrame);

    avcodec_close(pCodecContext);

    avformat_free_context(pformatContext);

    env->ReleaseStringUTFChars(input_, input);
    env->ReleaseStringUTFChars(output_, output);
    LOGE("------%s end------", "decode");
    LOGI("%s"," ")//打印空行
}

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_PlayerStudyBridge_player(JNIEnv *env, jobject instance, jstring input_, jobject surface) {
    LOGE("------%s start------", "player");
    const char *input = env->GetStringUTFChars(input_, 0);

    //1.注册所有组件，例如初始化一些全局的变量、初始化网络等等
    av_register_all();
    //avcodec_register_all();

    //封装格式上下文，统领全局的结构体，保存了视频文件封装格式的相关信息
    AVFormatContext *pFormatCtx = avformat_alloc_context();

    //TODO 设置屏幕方向
//    av_dict_set(&pFormatCtx->metadata,"rotate","180",0);

    //2.打开输入视频文件
    if (avformat_open_input(&pFormatCtx, input, NULL, NULL) != 0) {
        LOGE("%s", "无法打开输入视频文件");
        return;
    }

    //3.获取视频文件信息，例如得到视频的宽高
    //第二个参数是一个字典，表示你需要获取什么信息，比如视频的元数据
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGE("%s", "无法获取视频文件信息");
        return;
    }

//    AVDictionaryEntry* tag = NULL;
//    tag = av_dict_get(pFormatCtx->metadata,"rotate",tag,0);
//
//    if(tag == NULL){
//        LOGI("不存在方向信息");
//    }else{
//        LOGI("key=%s,value=%s",tag->key,tag->value);
//    }


    //获取视频流的索引位置
    //遍历所有类型的流（音频流、视频流、字幕流），找到视频流
    int v_stream_idx = -1;
    int i = 0;
    //number of streams
    for (; i < pFormatCtx->nb_streams; i++) {
        //流的类型
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            v_stream_idx = i;
            break;
        }
    }

    if (v_stream_idx == -1) {
        LOGE("%s", "找不到视频流\n");
        return;
    }

    //只有知道视频的编码方式，才能够根据编码方式去找到解码器
    //获取视频流中的编解码上下文
    AVCodecContext *pCodecCtx = pFormatCtx->streams[v_stream_idx]->codec;
    //4.根据编解码上下文中的编码id查找对应的解码器
    AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    //（迅雷看看，找不到解码器，临时下载一个解码器，比如视频加密了）
    if (pCodec == NULL) {
        LOGE("%s", "找不到解码器，或者视频已加密\n");
        return;
    }

    //5.打开解码器，解码器有问题（比如说我们编译FFmpeg的时候没有编译对应类型的解码器）
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        LOGE("%s", "解码器无法打开\n");
        return;
    }

    //准备读取
    //AVPacket用于存储一帧一帧的压缩数据（H264）
    //缓冲区，开辟空间
    AVPacket *packet = (AVPacket *) av_malloc(sizeof(AVPacket));

    //AVFrame用于存储解码后的像素数据(YUV)
    //内存分配
    AVFrame *yuv_frame = av_frame_alloc();
    AVFrame *rgb_frame = av_frame_alloc();

    int got_picture, ret;
    int frame_count = 0;

    //窗体
    ANativeWindow *pWindow = ANativeWindow_fromSurface(env, surface);
    //绘制时的缓冲区
    ANativeWindow_Buffer out_buffer;

    //6.一帧一帧的读取压缩数据
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        //只要视频压缩数据（根据流的索引位置判断）
        if (packet->stream_index == v_stream_idx) {
            //7.解码一帧视频压缩数据，得到视频像素数据
            ret = avcodec_decode_video2(pCodecCtx, yuv_frame, &got_picture, packet);
            if (ret < 0) {
                LOGE("%s", "解码错误");
                return;
            }

            //为0说明解码完成，非0正在解码
            if (got_picture) {

                //1、lock window
                //设置缓冲区的属性：宽高、像素格式（需要与Java层的格式一致）
                ANativeWindow_setBuffersGeometry(pWindow, pCodecCtx->width, pCodecCtx->height,
                                                 WINDOW_FORMAT_RGBA_8888);
                ANativeWindow_lock(pWindow, &out_buffer, NULL);

                //2、fix buffer

                //初始化缓冲区
                //设置属性，像素格式、宽高
                //rgb_frame的缓冲区就是Window的缓冲区，同一个，解锁的时候就会进行绘制
                avpicture_fill((AVPicture *) rgb_frame, (const uint8_t *) out_buffer.bits, AV_PIX_FMT_RGBA,
                               pCodecCtx->width,
                               pCodecCtx->height);

                //YUV格式的数据转换成RGBA 8888格式的数据
                //FFmpeg可以转，但是会有问题，因此我们使用libyuv这个库来做
                //https://chromium.googlesource.com/external/libyuv
                //参数分别是数据、对应一行的大小
                libyuv::I420ToARGB(yuv_frame->data[0], yuv_frame->linesize[0],
                           yuv_frame->data[2], yuv_frame->linesize[2],
                           yuv_frame->data[1], yuv_frame->linesize[1],
                           rgb_frame->data[0], rgb_frame->linesize[0],
                           pCodecCtx->width, pCodecCtx->height);

                //3、unlock window
                ANativeWindow_unlockAndPost(pWindow);

                frame_count++;
                LOGI("解码绘制第%d帧", frame_count);
            }
        }

        //释放资源
        av_free_packet(packet);
    }

    av_frame_free(&yuv_frame);
    avcodec_close(pCodecCtx);
    avformat_free_context(pFormatCtx);

    env->ReleaseStringUTFChars(input_, input);
    LOGE("------%s end------", "player");
    LOGI("%s"," ")//打印空行
}

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_PlayerStudyBridge_playAudio(JNIEnv *env, jobject instance, jstring input_) {
    LOGE("------%s start------", "playAudio");
    const char *input = env->GetStringUTFChars(input_, 0);

    //注册组件
    av_register_all();
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    //打开音频文件
    if (avformat_open_input(&pFormatCtx, input, NULL, NULL) != 0) {
        LOGI("%s", "无法打开音频文件");
        return;
    }
    //获取输入文件信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGI("%s", "无法获取输入文件信息");
        return;
    }
    //获取音频流索引位置
    int i = 0, audio_stream_idx = -1;
    for (; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_idx = i;
            break;
        }
    }

    //获取解码器
    AVCodecContext *codecCtx = pFormatCtx->streams[audio_stream_idx]->codec;
    AVCodec *codec = avcodec_find_decoder(codecCtx->codec_id);
    if (codec == NULL) {
        LOGI("%s", "无法获取解码器");
        return;
    }
    //打开解码器
    if (avcodec_open2(codecCtx, codec, NULL) < 0) {
        LOGI("%s", "无法打开解码器");
        return;
    }
    //压缩数据
    AVPacket *packet = (AVPacket *) av_malloc(sizeof(AVPacket));
    //解压缩数据
    AVFrame *frame = av_frame_alloc();
    //frame->16bit 44100 PCM 统一音频采样格式与采样率
    SwrContext *swrCtx = swr_alloc();

    //重采样设置参数-------------start
    //输入的采样格式
    enum AVSampleFormat in_sample_fmt = codecCtx->sample_fmt;
    //输出采样格式16bit PCM
    enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    //输入采样率
    int in_sample_rate = codecCtx->sample_rate;
    //输出采样率
    int out_sample_rate = in_sample_rate;
    //获取输入的声道布局
    //根据声道个数获取默认的声道布局（2个声道，默认立体声stereo）
    //av_get_default_channel_layout(codecCtx->channels);
    uint64_t in_ch_layout = codecCtx->channel_layout;
    //输出的声道布局（立体声）
    uint64_t out_ch_layout = AV_CH_LAYOUT_STEREO;

    swr_alloc_set_opts(swrCtx,
                       out_ch_layout, out_sample_fmt, out_sample_rate,
                       in_ch_layout, in_sample_fmt, in_sample_rate,
                       0, NULL);
    swr_init(swrCtx);

    //输出的声道个数
    int out_channel_nb = av_get_channel_layout_nb_channels(out_ch_layout);

    //重采样设置参数-------------end

    //JNI begin------------------
    jclass player_class = env->GetObjectClass(instance);

    //AudioTrack对象
    jmethodID create_audio_track_mid = env->GetMethodID(player_class, "createAudioTrack",
                                                           "(II)Landroid/media/AudioTrack;");
    jobject audio_track = env->CallObjectMethod(instance, create_audio_track_mid,
                                                   out_sample_rate, out_channel_nb);

    //调用AudioTrack.play方法
    jclass audio_track_class = env->GetObjectClass(audio_track);
    jmethodID audio_track_play_mid = env->GetMethodID(audio_track_class, "play", "()V");
    jmethodID audio_track_stop_mid = env->GetMethodID(audio_track_class, "stop", "()V");
    env->CallVoidMethod(audio_track, audio_track_play_mid);

    //AudioTrack.write
    jmethodID audio_track_write_mid = env->GetMethodID(audio_track_class, "write","([BII)I");
    //JNI end------------------

    //16bit 44100 PCM 数据
    uint8_t *out_buffer = (uint8_t *) av_malloc(MAX_AUDIO_FRME_SIZE);

    int got_frame = 0, index = 0, ret;
    //不断读取压缩数据
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        //解码音频类型的Packet
        if (packet->stream_index == audio_stream_idx) {
            //解码
            ret = avcodec_decode_audio4(codecCtx, frame, &got_frame, packet);

            if (ret < 0) {
                LOGI("%s", "解码完成");
            }
            //解码一帧成功
            if (got_frame > 0) {
                LOGI("解码：%d", index++);
                swr_convert(swrCtx, &out_buffer, MAX_AUDIO_FRME_SIZE,
                            (const uint8_t **) frame->data, frame->nb_samples);
                //获取sample的size
                int out_buffer_size = av_samples_get_buffer_size(NULL, out_channel_nb,
                                                                 frame->nb_samples, out_sample_fmt,
                                                                 1);

                //out_buffer缓冲区数据，转成byte数组
                jbyteArray audio_sample_array = env->NewByteArray(out_buffer_size);
                jbyte *sample_bytep = env->GetByteArrayElements(audio_sample_array, NULL);
                //out_buffer的数据复制到sampe_bytep
                memcpy(sample_bytep, out_buffer, out_buffer_size);
                //同步
                env->ReleaseByteArrayElements(audio_sample_array, sample_bytep, 0);

                //AudioTrack.write PCM数据
                env->CallIntMethod(audio_track, audio_track_write_mid,
                                      audio_sample_array, 0, out_buffer_size);
                //释放局部引用
                env->DeleteLocalRef(audio_sample_array);
            }
        }

        av_free_packet(packet);
    }

    env->CallVoidMethod(audio_track, audio_track_stop_mid);

    av_frame_free(&frame);
    av_free(out_buffer);

    swr_free(&swrCtx);
    avcodec_close(codecCtx);
    avformat_close_input(&pFormatCtx);

    env->ReleaseStringUTFChars(input_, input);
    LOGE("------%s end------", "playAudio");
    LOGI("%s"," ")//打印空行
}