package com.caiy.study;

import com.caiy.study.activity.HelloActivity;
import com.caiy.study.bridge.HelloBridge;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

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
    }

}
