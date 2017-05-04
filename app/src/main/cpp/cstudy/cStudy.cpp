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

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyMalloc(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyMalloc");

    int length = 3;
    int *p = (int *) malloc(length * sizeof(int));//10*4 = 40 分配内存
//  int* p = calloc(length, sizeof(int));//10*4 = 40 分配内存 另外一种方法
    LOGI("p=%#x", p);
    LOGI("*p=%#x", *p);
    LOGI("sizeof(p)=%d", sizeof(p));
    LOGI("sizeof(*p)=%d", sizeof(*p));
    int i = 0;
    for (; i < length; i++) {
        p[i] = i + 10;
        LOGI("p[%d]=%#x,&p[%d]=%#x", i, p[i], i, &p[i]);
    }
    free(p);
    p = NULL;

    int *p1 = (int *) malloc(length * sizeof(int));
    int addLength = 2;

    //重新分配内存的两种情况：
    //缩小，缩小的那一部分数据会丢失
    //扩大，（连续的）
    //1.如果当前内存段后面有需要的内存空间，直接扩展这段内存空间，realloc返回原指针
    //2.如果当前内存段后面的空闲字节不够，那么就使用堆中的第一个能够满足这一要求的内存块，将目前的数据复制到新的位置，并将原来的数据库释放掉，返回新的内存地址
    //3.如果申请失败，返回NULL，原来的指针仍然有效
    int *p2 = (int *) realloc(p1, (length + addLength) * sizeof(int));//重新分配内存
    int j = 0;

    if (p2 != NULL) {
        for (; j < length + addLength; j++) {
            p2[j] = j;
            LOGI("p2[%d]=%#x,&p2[%d]=%#x", j, p2[j], j, &p2[j]);
        }

        free(p2);
        LOGI("free后仍然有值:p2=%#x", p2);
//        free(p2);//注意不要释放两次 TODO 暂未找到多次释放后的问题
        p2 = NULL;
        LOGI("置为NULL后就真正为NULL了:p2=%#x", p2);

        //下一次分配之前，如果不释放,会造成内存泄露
        p2 = (int *) malloc(sizeof(int));
        LOGI("下一次分配:p2=%#x", p2);
        free(p2);
        p2 = NULL;
    }else{
        if(p1 != NULL){
            free(p1);
            p1 = NULL;
        }
    }

    //1.不能多次释放（否则会产生中断）
    //2.释放完之后（指针仍然有值），给指针置NULL，标志释放完成
    //3.内存泄露（p重新赋值之后，再free，并没有真正释放内存（之前的内存））

    LOGE("------%s end------", "studyMalloc");
    LOGI("%s"," ")//打印空行
}


extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyString(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyString");

    //字符数组实现。数组可以修改其中某一个值，不可以整体赋值。
    char str1[] = {'a','b','c','\0'};//可以不指定长度，但是需要有结束符
    char str2[6] = {'a','b','c'};//可以指定长度
    char str3[] = "abcdef";//
    LOGI("str3=%s",str3);
    str3[2] = '1';
    LOGI("str3=%s",str3);

    //字符指针实现。字符指针不可以修改其中某一个值，可以整体赋值。
    char* str4 = "jkl";
    LOGI("str4=%s",str4);
    str4 = "12345678";
    LOGI("str4=%s",str4);
//    LOGI("*str4=%#x",*str4);
//    LOGI("&str4=%#x",&str4);
    str4 += 2;//截取字符串
    LOGI("str4=%s",str4);
    while(*str4){
//        LOGI("*str4=%c,str4=%#x,&str4=%#x",*str4,str4,&str4);
        LOGI("str4=%s",str4);
        LOGI("*str4=%c",*str4);
        str4++;
    }

    //strcpy 字符串拷贝
    char dest[10];
    LOGI("dest=%s",dest);//乱码显示
    char* src = "abcdef";
    strcpy(dest,src);
    LOGI("dest=%s",dest);

    //strcat 字符串拼接
    strcat(dest,src);
    LOGI("dest=%s",dest);

    //strchr 字符查找
    char* p = strchr(dest,'f');
    if(p){
        LOGI("%c的索引位置%d",*p,p-dest);
    }else{
        LOGI("未找到%s",p);
    }

    //strstr 字符串查找
    char* match = "def";
    char* pp = strstr(dest,match);
    if(pp){
        LOGI("%s的索引位置%d",match,pp-dest);
    }else{
        LOGI("未找到%s",pp);
    }

    LOGE("------%s end------", "studyString");
    LOGI("%s"," ")//打印空行
}

void play(char* name){
    LOGI("%s在玩农药",name);
}

struct Person{
    char* name;
    int age;
    void(*play)(char* name);//函数指针
} wangwu = {"王五",22,play};

//在结构体定义的时候取别名
typedef struct Person2{
    char* name;
    int age;
}P_1,*P_2;//P_1是结构体的别名，P_2是结构体指针的别名，与变量的声明区分开（没有typedef）

struct{
    char* name;
    int age;
    struct Person delegate;
    void(*play)(char* name);//函数指针
} singleInstance = {"单例",99,wangwu,play};

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyStruct(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyStruct");

    struct Person zhangsan = {"张三",20,play};//结构体赋值方式1 初始化的时候赋值
    zhangsan.play(zhangsan.name);

    struct Person lisi;//结构体赋值方式2 初始化的时候未赋值
    lisi.name = "李四";
    lisi.age = 21;
    lisi.play = play;
    lisi.play(lisi.name);

    wangwu.play(wangwu.name);//结构体赋值方式3

    singleInstance.play(singleInstance.name);//匿名结构体
    singleInstance.delegate.play(singleInstance.delegate.name);//嵌套结构体

    struct Person* p = &zhangsan;//结构体指针
    LOGI("(*p).name=%s,(*p).age=%d",(*p).name,(*p).age);
    LOGI("p->name=%s,p->age=%d",p->name,p->age);

    struct Person persons[] = {{"小冯",23,play},{"小李",24,play}};
    LOGI("sizeof(persons)=%d", sizeof(persons));
    LOGI("sizeof(struct Person)=%d", sizeof(struct Person));//结构体的大小
    int size = sizeof(persons)/sizeof(struct Person);

    //结构体数组
    int i=0;
    for(;i<size;i++){
        LOGI("persons[i].name=%s,persons[i].age=%d",persons[i].name,persons[i].age);
    }
    struct Person* personPointer = persons;
    for(;personPointer<persons+size;personPointer++){
        LOGI("(*personPointer).name=%s,(*personPointer).age=%d",(*personPointer).name,(*personPointer).age);
    }

    //动态内存分配
    size = 3;
    i = 0;
    struct Person* mallocPoint = (Person *) malloc(size * sizeof(struct Person));
    for(;i<size;i++){
        mallocPoint->name = "name";
        mallocPoint->age = i;
        LOGI("mallocPoint->age=%d",mallocPoint->age);
        mallocPoint++;
    }
    free(mallocPoint);
    mallocPoint = NULL;

    //取别名
    typedef struct Person P;//结构体取别名
    P per;
    //
    typedef struct Person* PP;//结构体指针取别名
    PP perPointer;

    P_1 p1;//结构体取别名
    P_2 p2 = &p1;//结构体指针取别名

    LOGE("------%s end------", "studyStruct");
    LOGI("%s"," ")//打印空行
}

union MyNumber{
    int i;
    long l;
    double d;
};

typedef enum Direction{
    East,
    West,
    North,
    Sourth,
    Middle
} Direction;

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyUnionAndEnum(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyUnionAndEnum");

    //联合体
    union MyNumber myNumber;
    myNumber.i = 1;
    myNumber.l = 2;
    myNumber.d = 3.0;//最后一次赋值有效
    LOGI("myNumber.i=%d,myNumber.l=%ld,myNumber.d=%lf",myNumber.i,myNumber.l,myNumber.d);

    //枚举
    Direction direction = Middle;
    LOGI("direction=%#x,&direction=%#x",direction,&direction);

    LOGE("------%s end------", "studyUnionAndEnum");
    LOGI("%s"," ")//打印空行
}


extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyIO(JNIEnv *env, jclass type, jstring readPath_, jstring writePath_) {
    LOGE("------%s start------", "studyIO");

    const char *readPath = env->GetStringUTFChars(readPath_, 0);
    const char *writePath = env->GetStringUTFChars(writePath_, 0);

    FILE* readFile = fopen(readPath,"r");
    FILE* writeFile = fopen(writePath,"w");
    if(readFile == NULL || writeFile == NULL){
        LOGE("文件无法打开readPath=%s,writePath=%s",readPath,writePath);
    }else{
        char buffer[64];
        while(fgets(buffer,64,readFile)){//读取文件
            LOGI("正在读取文件%s的内容:%s",readPath,buffer);
            fputs(buffer,writeFile);//写文件
        }

        fseek(readFile,0,SEEK_END);//seek到文件的结尾，0L代表向前偏移几个字节
        long readFileSize = ftell(readFile);//返回当前的文件指针相对于文件开头的位移量
        LOGI("readFileSize=%ld",readFileSize)

        fclose(readFile);
        fclose(writeFile);

        FILE* readWriteFile = fopen(writePath,"r");
        while(fgets(buffer,64,readWriteFile)){
            LOGI("正在读取文件%s的内容:%s",writePath,buffer);
        }

        fclose(readWriteFile);
    }

    //TODO 读写二进制文件
    //TODO 文件加解密
    //TODO 二进制文件加解密
    //TODO 文件分割合并

    env->ReleaseStringUTFChars(readPath_, readPath);
    env->ReleaseStringUTFChars(writePath_, writePath);


    LOGE("------%s end------", "studyIO");
    LOGI("%s"," ")//打印空行
}

#define MAX 100

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CStudyBridge_studyPreCompile(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyPreCompile");

    #include "cInclude.cpp";

    int i= 100;
    if(i == MAX){
        LOGI("宏定义常量MAX=%d",i);
    }

    //打印日志的LOGI就属于宏定义函数

    LOGE("------%s end------", "studyPreCompile");
    LOGI("%s"," ")//打印空行
}
