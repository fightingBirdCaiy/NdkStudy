#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_JniStudyBridge_studyHelloWorld(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyHelloWorld");

    // TODO

    LOGE("------%s end------", "studyHelloWorld");
    LOGI("%s"," ")//打印空行
}