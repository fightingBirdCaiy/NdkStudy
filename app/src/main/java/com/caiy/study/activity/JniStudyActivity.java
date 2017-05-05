package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.JniStudyBridge;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * Created by yongc on 17/5/4.
 */

public class JniStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_study);

        JniStudyBridge.studyHelloWorld();
    }
}
