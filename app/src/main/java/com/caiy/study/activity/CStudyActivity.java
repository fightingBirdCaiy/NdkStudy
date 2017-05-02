package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.CStudyBridge;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by yongc on 17/5/2.
 */

public class CStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_c_study);

        CStudyBridge.studyDataType();
    }

}
