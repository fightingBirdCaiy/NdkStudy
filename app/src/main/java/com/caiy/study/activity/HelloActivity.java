package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.HelloBridge;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * Created by yongc on 17/4/27.
 */

public class HelloActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello);

        // Example of a call to a native method
        // 调用jni方法的例子
        TextView tv = (TextView) findViewById(R.id.sample_text);
        HelloBridge helloBridge = new HelloBridge();
        tv.setText(helloBridge.stringFromJNI());
    }

}
