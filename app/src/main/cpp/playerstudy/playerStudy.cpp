#include <jni.h>
#include <string>
#include <android/log.h>
////编码
//#include <libavcodec/avcodec.h>
////封装格式处理
//#include <libavformat/avformat.h>
////像素处理
//#include <libswscale/swscale.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

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
//                sws_scale(pSwsContext, pFrame->data, pFrame->linesize, 0, pCodecContext->height,
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