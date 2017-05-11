package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.CPlusStudyBridge;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by yongc on 17/5/9.
 */

public class CPlusStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_c_plus_study);

        CPlusStudyBridge.studyClass();
        CPlusStudyBridge.studyOOP();
    }
}
