#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyDataType(JNIEnv *env, jclass type) {

    LOGE("------%s start------", "studyDataType");
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

    LOGE("------%s end------", "studyDataType");
    LOGI("%s"," ")//打印空行
}

void changePointer(int* p){
    *p = 64;
}

void changeValue(int i){
    i = 128;
}

int addTest(int a, int b){
    LOGI("函数指针add方法调用了"," ");
    return a+b;
}

int delTest(int a, int b){
    LOGI("函数指针del方法调用了"," ");
    return a-b;
}

//函数指针
void functionPointer(int(*functionCallback)(int a, int b), int a, int b){
    int result = functionCallback(a,b);
    LOGI("result=%d",result);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyPointer(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyPointer");

    int i = 16;
    int* p = &i;//一级指针
    int** pp = &p;//二级指针
    LOGI("i=%d", i);
    LOGI("i=%#x", i);
    LOGI("&i=%d", &i);
    LOGI("&i=%#x", &i);
    LOGI("p=%d", p);
    LOGI("p=%#x", p);
    LOGI("&p=%d", &p);
    LOGI("&p=%#x", &p);
    LOGI("*p=%d", *p);
    LOGI("*p=%#x", *p);
    LOGI("pp=%d", pp);
    LOGI("pp=%#x", pp);
    LOGI("&pp=%d", &pp);
    LOGI("&pp=%#x", &pp);
    LOGI("*pp=%d", *pp);
    LOGI("*pp=%#x", *pp);

    *p = 32;
    LOGI("i=%d", i);
    changePointer(p);//引用传递，值改变
    LOGI("引用传递i=%d", i);
    changeValue(i);//值传递，值未改变
    LOGI("值传递i=%d", i);

    int* nullPointer = NULL;//空指针
    LOGI("nullPointer=%d", nullPointer);
    LOGI("nullPointer=%#x", nullPointer);

//    int* yePointer =(int*)0x55feb4;//野指针
//    *yePointer = 1024;//野指针 赋值操作

    //指针运算
    int array[] = {10,11,12,13,14,15};
    int* arrayPoint = array;
    LOGI("array=%d",array);
    LOGI("array=%#x",array);
    LOGI("&array=%#x",&array);
    LOGI("*array=%#x",*array);
    LOGI("array[0]=%#x",array[0]);
    LOGI("&array[0]=%#x",&array[0]);
    LOGI("arrayPoint=%d",arrayPoint);
    LOGI("arrayPoint=%#x",arrayPoint);
    LOGI("&arrayPoint=%#x",&arrayPoint);
    LOGI("*arrayPoint=%#x",*arrayPoint);
    arrayPoint++;//指针的加减法，移动sizeof(数据类型)个字节
    LOGI("*arrayPoint++=%#x",*arrayPoint);
    //通过指针给数组赋值
    //高级写法 []运算符的重载
    int ii=0;
    for(; ii<5; ii++){
        array[ii] = 11;
    }
    //普通写法 指针方式
    arrayPoint = array;
    for(; arrayPoint<array+5; arrayPoint++){
        *arrayPoint = 10;
    }

    int a = 5;
    int b = 3;
    functionPointer(addTest,a,b);//函数指针，类似java的回调 5+3 = 8
    functionPointer(delTest,a,b);//函数指针，类似java的回调 5-3 = 2

    LOGE("------%s end------", "studyPointer");
    LOGI("%s"," ")//打印空行
}

