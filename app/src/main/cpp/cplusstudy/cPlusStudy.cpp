#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

class Teacher{
public :
    Teacher(){
        this->name = "";
        this->age = 0;
        LOGI("Teacher默认构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    Teacher(char* name, int age){
        this->name = name;
        this->age = age;
        LOGI("Teacher两个参数的构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    Teacher(const Teacher &other){
        this->name = other.name;
        this->age = other.age;
        LOGI("Teacher拷贝构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    ~Teacher(){
        LOGI("Teacher析构函数调用了");
    }
private :
    char* name;
    int age;
};

class Student{
public:
    Student(){
        LOGI("Student默认构造函数调用了")
    }
    Student(char* name, int age, char* t_name, int t_age) : teacher(t_name,t_age){
        this->name = name;
        this->age = age;
        LOGI("Student两个参数的构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    ~Student(){
        LOGI("Student析构函数调用了");
    }
private:
    char* name;
    int age;
    Teacher teacher;
};

class CopyTest{
    friend void updateAge(CopyTest &target, int age);//友元函数声明
public:
    CopyTest(){
        this->name = (char *) malloc(sizeof(char) * 100);
        strcpy(this->name,"默认name");
        this->age = 0;
        count++;
        LOGI("CopyTest默认构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    CopyTest(char* name, int age){
        int size = strlen(name) + 1;
        this->name = (char *) malloc(sizeof(char) * size);
        strcpy(this->name,name);
        this->age = age;
        count++;
        LOGI("CopyTest两个参数的构造函数调用了name=%s,age=%d",this->name,this->age);
    }
    CopyTest(const CopyTest &copy){
        int size = strlen(copy.name) + 1;
        this->name = (char *)malloc(sizeof(char)*size);
        strcpy(this->name,copy.name);
        this->age = copy.age;
        count++;
        LOGI("CopyTest拷贝构造函数调用了name=%s,age=%d",this->name,this->age);
    }

    ~CopyTest(){
        LOGI("CopyTest析构函数调用了:this->name的地址%#x", this->name);
        free(this->name);
    }

    static int getCount(){
        return count;
    }

    //常函数
    //this本身是指针常量(指针不能变)
    //这里加入const后，this更是一个常量指针(常量不能变)
    void testConstMethod(CopyTest* other) const{
        LOGI("this=%#x",this);
//        this->age = 1;//常量指针，值不能变
//        this = other;//编译错误，指针不能变
    }
private:
    char* name;
    int age;
    static int count;
};

//静态属性初始化
int CopyTest::count = 0;

void updateAge(CopyTest &target, int age){
    target.age = age;
    LOGI("target.age=%d",target.age);
}

class FriendA{
    friend class FriendB;
public:
private:
    int age;
};

class FriendB{
public:
    void initFriendA(){
        friendA.age = 30;
        LOGI("friendA.age=%d",friendA.age);
    }
private:
    FriendA friendA;
};

class Point{
public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    Point operator+(Point &other){
        return Point(this->x + other.x,this->y + other.y);
    }

    void toString(){
        LOGI("Point类this->x=%d,this->y=%d",this->x,this->y);
    }
private:
    int x;
    int y;
};

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CPlusStudyBridge_studyClass(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyClass");

    Teacher t1;//默认构造函数调用方式一
//    Teacher t2();//该方法无效，不会调用默认构造函数
    Teacher t3 = Teacher();//默认构造函数调用方式二

    Teacher t4("李老师",25);//两个参数构造函数调用方式一
    Teacher t5 = Teacher("刘老师",26);//两个参数构造函数调用方式二

    //初始化列表
    Student s1 = Student();//Teacher和Student默认构造函数都会被调用
    Student s2 = Student("小明同学",12,"赵老师",27);//Teacher和Student两个参数的构造函数都会被调用

    //析构函数 调用情况请查看日志

    //拷贝构造函数
    Teacher tCopy = t5;//会调用拷贝构造函数
    Teacher &tRefrence = t5;//引用赋值，不会调用拷贝构造函数

    //深拷贝
    CopyTest c1 = CopyTest("CopyTest",1);
    CopyTest copyTest = c1;

    //构造和析构函数不会被调用
    CopyTest* c2 = (CopyTest *) malloc(sizeof(CopyTest));
    free(c2);

    //构造和析构函数会被调用
    CopyTest* c3 = new CopyTest();//构造函数会被调用
    delete c3;//如果这行去掉，则析构函数不会被调用

    int* arr1 = (int*) malloc(sizeof(int) * 10);
    arr1[1] = 1;
    free(arr1);

    int* arr2 = new int[10];
    arr2[2] = 2;
    free(arr2);

    LOGI("CopyTest::getCount()=%d",CopyTest::getCount());//类的静态属性和函数

    LOGI("sizeof(CopyTest)=%d",sizeof(CopyTest));//类的大小

    //常函数
    CopyTest c4 = CopyTest("c4",4);
    CopyTest c5 = CopyTest("c5",5);
    c4.testConstMethod(&c5);

    //友元函数
    CopyTest c6 = CopyTest("c6",6);
    updateAge(c6, 16);

    //友元类
    FriendB friendB = FriendB();
    friendB.initFriendA();

    //操作符重载
    Point p1 = Point(1,2);
    Point p2 = Point(10,20);
    Point p3 = p1 + p2;
    p3.toString();

    LOGE("------%s end------", "studyClass");
    LOGI("%s"," ")//打印空行
}