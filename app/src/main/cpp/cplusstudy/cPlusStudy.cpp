#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CPlusStudyBridge_studyClass(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyClass");

    // TODO

    LOGE("------%s end------", "studyClass");
    LOGI("%s"," ")//打印空行
}