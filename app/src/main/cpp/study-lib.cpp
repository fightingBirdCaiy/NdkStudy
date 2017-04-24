#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_caiy_study_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "来自 C++";
    return env->NewStringUTF(hello.c_str());
}
