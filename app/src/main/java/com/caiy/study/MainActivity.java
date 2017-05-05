package com.caiy.study;

import com.caiy.study.activity.CStudyActivity;
import com.caiy.study.activity.FmodActivity;
import com.caiy.study.activity.HelloActivity;
import com.caiy.study.activity.JniStudyActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends Activity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initView();
    }

    private void initView() {
        setContentView(R.layout.activity_main);
        initEvent();
    }

    private void initEvent() {

        View helloLayout = findViewById(R.id.hello_layout);
        helloLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, HelloActivity.class);
                startActivity(intent);
            }
        });

        View cStudyLayout = findViewById(R.id.c_study_layout);
        cStudyLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, CStudyActivity.class);
                startActivity(intent);
            }
        });

        View jniStudyLayout = findViewById(R.id.jni_study_layout);
        jniStudyLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, JniStudyActivity.class);
                startActivity(intent);
            }
        });

        View fmodLayout = findViewById(R.id.fmod_layout);
        fmodLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, FmodActivity.class);
                startActivity(intent);
            }
        });
    }

}
