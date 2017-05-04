#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_caiy_study_bridge_HelloBridge_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "HelloActivity\n\n文案来自 C++";
    return env->NewStringUTF(hello.c_str());
}
