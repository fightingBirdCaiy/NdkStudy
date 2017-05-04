package com.caiy.study.activity;

import java.io.File;

import com.caiy.study.R;
import com.caiy.study.bridge.CStudyBridge;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;

/**
 * Created by yongc on 17/5/2.
 */

public class CStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_c_study);

        CStudyBridge.studyDataType();
        CStudyBridge.studyPointer();
        CStudyBridge.studyMalloc();
        CStudyBridge.studyString();
        CStudyBridge.studyStruct();
        CStudyBridge.studyUnionAndEnum();

        String readPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "read.txt";
        String writePath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "write.txt";
        CStudyBridge.studyIO(readPath,writePath);
        CStudyBridge.studyPreCompile();
    }

}
