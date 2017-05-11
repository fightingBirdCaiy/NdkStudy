#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"TAG",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"TAG",FORMAT,##__VA_ARGS__);

namespace name1{
    int i = 1;

    namespace name2{
        int i = 2;
    }

    struct StructDemo{
    public:
        char* desc;
        void toString(){
            LOGI("StructDemo toString方法调用了,this->desc=%s",this->desc);
        }
    private:

    };
}

void testDefault(int a, int b = 2, int c = 3){
    LOGI("testDefault方法调用了,a=%d,b=%d,c=%d",a,b,c);
}

void testArgs(int a, int b, ...){
    va_list args;
    va_start(args,b);
    char c = va_arg(args,char);
    int d = va_arg(args,int);
    va_end(args);
    LOGI("testArg方法调用了,a=%d,b=%d,c=%c,d=%d",a,b,c,d);
}

void swapInt(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

void swapIntRef(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void swapChar(char a, char b){
    char temp = a;
    a = b;
    b = temp;
}

void swapCharRef(char &a, char &b){
    char temp = a;
    a = b;
    b = temp;
}

template <typename T>
void swapTeplate(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
class A{
public:
    A(T t){
        this->t = t;
        LOGI("A类 一个参数的构造函数调用了");
    }
protected:
    T t;
};

//普通类继承模板类
class B:public A<int>{
public:
    B(int i):A<int>(i){
        LOGI("B类 一个参数的构造函数调用了");
    }
};

//模板类继承模板类
template<class T>
class C:public A<T>{
public:
    C(T t):A<T>(t){
        LOGI("C类 一个参数的构造函数调用了");
    }
};

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CPlusStudyBridge_studyBasicConcept(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyBasicConcept");

    //命名空间
    LOGI("name1::i=%d",name1::i);
    LOGI("name1::name2::i=%d",name1::name2::i);

    //结构体
    name1::StructDemo structDemo;
    structDemo.desc = "c++中的结构体StructDemo";
    structDemo.toString();

    //类 后面有单独介绍，这里不重复写

    //bool变量 大于0为真，小于等于0为假
    bool condition = true;
    if(condition){
        LOGI("条件为真，condition=%d",condition);
    }else{
        LOGI("条件为假，condition=%d",condition);
    }
    condition = false;
    LOGI("condition固定成false,condition=%d",condition);

    //函数默认值
    testDefault(1);
    testDefault(2,4);
    testDefault(8,16,32);

    //可变参数
    testArgs(1,2,'c',3);

    int aInt = 1;
    int bInt = 2;
    swapInt(aInt,bInt);
    LOGI("swap(aInt,bInt)后,aInt=%d,bInt=%d",aInt,bInt)
    aInt = 3;
    bInt = 4;
    swapIntRef(aInt,bInt);
    LOGI("swapIntRef(aInt,bInt)后,aInt=%d,bInt=%d",aInt,bInt)
    char aChar = 'a';
    char bChar = 'b';
    swapChar(aChar,bChar);
    LOGI("swapChar(aChar,bChar)后,aChar=%c,aChar=%c",aChar,bChar);
    aChar = 'c';
    bChar = 'd';
    swapCharRef(aChar,bChar);
    LOGI("swapCharRef(aChar,bChar)后,aChar=%c,aChar=%c",aChar,bChar);

    //模板函数
    aInt = 10;
    bInt = 20;
    swapTeplate(aInt,bInt);
    LOGI("swapTeplate(aInt,bInt)后,aInt=%d,bInt=%d",aInt,bInt)
    aChar = 'A';
    bChar = 'B';
    swapTeplate(aChar,bChar);
    LOGI("swapTeplate(aChar,bChar)后,aChar=%c,aChar=%c",aChar,bChar);

    //模板类
    A<int> a(10);
    A<char> a2('a');
    B b = B(20);
    C<double> c = C<double>(10.0);

    LOGE("------%s end------", "studyBasicConcept");
    LOGI("%s"," ")//打印空行
}

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

class Father{
public:
    Father(){
        this->name = "默认名";
        this->age = 100;
        LOGI("Father默认构造函数调用了");
    }
    Father(char* name, int age){
        this->name = name;
        this->age = age;
        LOGI("Father两个参数的构造函数调用了,name=%s,age=%d",this->name,this->age);
    }
    Father(const Father &other){
        this->name = other.name;
        this->age = other.age;
        LOGI("Father拷贝构造函数调用了,name=%s,age=%d",this->name,this->age);
    }

    ~Father(){
        LOGI("Father析构函数调用了");
    }

    void toString(){
        LOGI("Father toString函数调用了,name=%s,age=%d",this->name,this->age);
    }

    virtual void talk(){
        LOGI("Father talk函数调用了,name=%s,age=%d",this->name,this->age);
    }
private:
    char* name;
    int age;
};

class Son :public Father{
public:
    Son(){
        this->toy = "默认玩具";
    }

    Son(char* name, int age, char* toy) :Father(name,age){
        this->toy = toy;
        LOGI("Son 三个参数的构造函数调用了,toy=%s",this->toy);
    }

    Son(const Son &other):Father(){
        //TODO 拷贝时父类的属性如何拷贝
        this->toy = other.toy;
        LOGI("Son 拷贝构造函数调用了,toy=%s",this->toy);
    }

    ~Son(){
        LOGI("Son析构函数调用了");
    }

    void toString(){
        LOGI("Son toString函数调用了,toy=%s",this->toy);
    }

    virtual void talk(){
        LOGI("Son talk函数调用了,toy=%s",this->toy);
    }
private:
    char* toy;
};

void talk(Father &father){
    father.talk();
}

//相当与java中的接口
class Shape{
public:
    virtual double area() = 0;
};

class Circle :public Shape{
public:
    Circle(double radius){
        this->radius = radius;
    }

    double area(){
         return 3.14*radius*radius;
    }
private:
    double radius;
};

class Rectangle :public Shape{
public:
    Rectangle(double width, double height){
        this->width = width;
        this->height = height;
    }

    double area(){
        return width*height;
    }
private:
    double width;
    double height;
};

extern "C"
JNIEXPORT void JNICALL
Java_com_caiy_study_bridge_CPlusStudyBridge_studyOOP(JNIEnv *env, jclass type) {
    LOGE("------%s start------", "studyOOP");

    Son son = Son("父亲",23,"乐高积木");



    Father father = son;//Father的拷贝构造函数、析构函数会被调用
    Father &fatherRef = son;//Father的析构函数不会被调用

    //调用父类的toString方法
    son.Father::toString();
    father.toString();
    fatherRef.toString();

    //调用子类的toString方法
    son.Son::toString();
    son.toString();

    Son son2 = son;//Father和Son的构造和析构函数都会被调用

    //TODO
    //虚继承 virtual public

    //多态 虚函数
    Father fatherMulti = Father();
    Son sonMulti = Son();
    talk(fatherMulti);
    talk(sonMulti);

    //多态 纯虚函数 相当于 接口
    Circle circle = Circle(1);
    Rectangle rectangle = Rectangle(2,3);
    LOGI("circle.area()=%lf",circle.area());
    LOGI("rectangle.area()=%lf",rectangle.area());

    LOGE("------%s end------", "studyOOP");
    LOGI("%s"," ")//打印空行
}