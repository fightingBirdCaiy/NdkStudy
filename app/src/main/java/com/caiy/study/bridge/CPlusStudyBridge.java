package com.caiy.study.bridge;

/**
 * Created by yongc on 17/5/9.
 */

public class CPlusStudyBridge {

    static{
        System.loadLibrary("cPlusStudy");
    }

    /**
     * 学习基本概念
     */
    public native static void studyBasicConcept();

    /**
     * 学习类
     */
    public native static void studyClass();

    /**
     * 学习面向对象
     */
    public native static void studyOOP();
}
