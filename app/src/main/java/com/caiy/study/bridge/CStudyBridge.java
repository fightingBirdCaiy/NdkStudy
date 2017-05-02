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

}
