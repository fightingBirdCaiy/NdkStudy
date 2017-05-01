package com.caiy.study.bridge;

/**
 * Created by yongc on 17/4/27.
 */

public class FmodBridge {

    public static final int TYPE_NORMAL = 0;
    public static final int TYPE_LUOLI = 1;
    public static final int TYPE_DASHU = 2;
    public static final int TYPE_JINGSONG = 3;
    public static final int TYPE_GAOGUAI = 4;
    public static final int TYPE_KONGLING = 5;

    static {
        System.loadLibrary("fmodL");
        System.loadLibrary("fmod");
        System.loadLibrary("fmod-lib");
    }

    public static native String playFixVoice(String path, int type);

}
