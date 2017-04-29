package com.caiy.study.bridge;

/**
 * Created by yongc on 17/4/27.
 */

public class FmodBridge {

    static {
//        System.loadLibrary("fmodL");
//        System.loadLibrary("fmod");
        System.loadLibrary("fmod-lib");
    }

    public static native String playFixVoice(String path, int type);

}
