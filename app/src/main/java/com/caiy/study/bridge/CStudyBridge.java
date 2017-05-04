package com.caiy.study.bridge;

/**
 * Created by yongc on 17/5/2.
 */

public class CStudyBridge {

    static {
        System.loadLibrary("cStudy");
    }

    /**
     * 学习数据类型
     */
    public native static void studyDataType();

    /**
     * 学习指针
     */
    public native static void studyPointer();

    /**
     * 学习内存分配
     */
    public native static void studyMalloc();

    /**
     * 学习字符串
     */
    public native static void studyString();

    /**
     * 学习结构体
     */
    public native static void studyStruct();

    /**
     * 学习联合体和枚举
     */
    public native static void studyUnionAndEnum();
}
