package com.caiy.study.bridge;

/**
 * Created by yongc on 2017/5/17.
 */

public class PlayerStudyBridge {

    static {
        System.loadLibrary("avutil-54");
        System.loadLibrary("swresample-1");
        System.loadLibrary("avcodec-56");
        System.loadLibrary("avformat-56");
        System.loadLibrary("swscale-3");
//        System.loadLibrary("postproc-53");
        System.loadLibrary("avfilter-5");
//        System.loadLibrary("avdevice-56");
        System.loadLibrary("playerStudy");
    }


    public native static void decode(String input, String output);
}
