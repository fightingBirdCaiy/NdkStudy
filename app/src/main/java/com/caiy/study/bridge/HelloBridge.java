package com.caiy.study.bridge;

/**
 * Created by yongc on 17/4/27.
 */

public class HelloBridge {

    // Used to load the 'study-lib' library on application startup.
    static {
        System.loadLibrary("study-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

}
