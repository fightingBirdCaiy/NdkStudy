#include "fmod.hpp"
#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <android/log.h>

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);


//变声的类型
#define TYPE_NORMAL 0//正常
#define TYPE_LUOLI 1//萝莉
#define TYPE_DASHU 2//大叔
#define TYPE_JINGSONG 3//惊悚
#define TYPE_GAOGUAI 4//搞怪
#define TYPE_KONGLING 5//空灵

//使用fmod的命名空间
using namespace FMOD;

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_caiy_study_bridge_FmodBridge_playFixVoice(JNIEnv *env, jclass type_, jstring path_,
                                                   jint type) {
    const char *path = env->GetStringUTFChars(path_, NULL);

    FMOD::System *system = NULL;
    FMOD::Sound *sound = NULL;
    FMOD::Channel *channel = NULL;
    FMOD::DSP *dsp = NULL;
    bool isPlaying = true;
    float frequency;

    LOGE("准备播放音频:%s", path);

//    FILE * fouttest = fopen(path,"rw");
//    if(fouttest == NULL){
//        LOGE("文件无法打开:%s", path);
//    }

    //fmod初始化
    System_Create(&system);
    //指定最大的声轨数等参数
    system->init(32, FMOD_INIT_NORMAL, NULL);

    //创建声音对象
    system->createSound(path, FMOD_DEFAULT, NULL, &sound);

    switch (type) {
        case TYPE_NORMAL:
            //原声播放
            //指定的是音轨0，最后update的时候才会播放
            system->playSound(sound, 0, false, &channel);
            LOGI("%s", "音频播放了:normal");
            break;

        case TYPE_LUOLI:
            //创建一个数字信号处理对象DSP
            //DSP（数字信号处理）主要原理是：通过改变声音的两个参数：响度（振幅） 声调（频率）
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            //设置参数，提高频率，升高一个八度
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.5);
            //把处理对象添加到Channel的音轨0中(注意这里要先播放然后添加音轨特效)
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);
            LOGI("%s", "音频播放了:luo li");
            break;

        case TYPE_DASHU:
            //创建一个数字信号处理对象DSP
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            //设置参数，提高频率，升高一个八度
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
            //把处理对象添加到Channel的音轨0中
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);
            LOGI("%s", "音频播放了:da shu");
            break;

        case TYPE_JINGSONG:
            //惊悚
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);
            LOGI("%s", "音频播放了:jing song");
            break;

        case TYPE_GAOGUAI:
            //搞怪
            //提高说话的速度
            system->playSound(sound, 0, false, &channel);
            channel->getFrequency(&frequency);
            frequency = frequency * 1.6;
            channel->setFrequency(frequency);
            LOGI("%s", "音频播放了:gao guai");
            break;

        case TYPE_KONGLING:
            //空灵
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);
            LOGI("%s", "音频播放了:空灵");
            break;

        default:
            break;
    }

    //update的时候才会播放
    system->update();

    //每秒钟判断一下是否在播放
    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        usleep(1 * 1000 * 1000);//单位是微妙，这里是1秒延时
    }

    //释放资源
    sound->release();
    system->close();
    system->release();

    env->ReleaseStringUTFChars(path_, path);

    return env->NewStringUTF(path);
}

}