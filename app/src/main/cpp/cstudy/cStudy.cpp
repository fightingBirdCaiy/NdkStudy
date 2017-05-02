#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyDataType(JNIEnv *env, jclass type) {

    //具体跟操作系统有关
    //基本数据类型
    LOGI("short类型所占的字节数%d", sizeof(short));
    LOGI("int类型所占的字节数%d", sizeof(int));
    LOGI("long类型所占的字节数%d", sizeof(long));
    LOGI("float类型所占的字节数%d", sizeof(float));
    LOGI("double类型所占的字节数%d", sizeof(double));
    LOGI("char类型所占的字节数%d", sizeof(char));

    //注意：这里大小是5
    LOGI("字符串\"test\"所占的字节数%d", sizeof("test"));

    short numberShort = 99;
    LOGI("格式化输出numberShort=%d", numberShort);
    int numberInt = 98;
    LOGI("格式化输出numberInt=%d", numberInt);
    long numberLong = 97;
    LOGI("格式化输出numberLong=%ld", numberLong);
    float numberFloat = 3.14;
    LOGI("格式化输出numberFloat=%f", numberFloat);
    double numberDouble = 0.618;
    LOGI("格式化输出numberDouble=%lf", numberDouble);
    char cChar = 'a';
    LOGI("格式化输出cChar=%c", cChar);

    LOGI("格式化输出numberInt十六进制=%x", numberInt);

    LOGI("格式化输出numberInt八进制=%o", numberInt);

    LOGI("格式化输出numberInt带0x前缀的十六进制=%#x", numberInt);

    LOGI("格式化输出字符串=%s", "test字符串");
}