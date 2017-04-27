#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>
#include <string>


JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_FmodBridge_playFixVoice(JNIEnv *env, jclass type_, jstring path_, jint type) {
    const char *path = env->GetStringUTFChars(path_, 0);

    // TODO
//    __android_log_print(ANDROID_LOG_INFO,"caiy","%sccc","ceshiceshi");

    env->ReleaseStringUTFChars(path_, path);
}