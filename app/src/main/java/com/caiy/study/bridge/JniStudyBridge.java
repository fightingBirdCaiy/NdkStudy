package com.caiy.study.bridge;

/**
 * Created by yongc on 17/5/4.
 */

public class JniStudyBridge {

    static {
        System.loadLibrary("jniStudy");
    }

    /**
     * 学习HelloWorld示例
     */
    public static native void studyHelloWorld();

}
