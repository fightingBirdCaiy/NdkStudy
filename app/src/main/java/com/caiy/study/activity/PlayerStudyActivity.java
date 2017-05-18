package com.caiy.study.activity;

import java.io.File;

import com.caiy.study.R;
import com.caiy.study.bridge.PlayerStudyBridge;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;

/**
 * Created by yongc on 2017/5/16.
 */

public class PlayerStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
    }

    private void initView() {
        setContentView(R.layout.activity_player_study);
        initEvent();
    }

    private void initEvent() {
        View decodeLayout = findViewById(R.id.decode_layout);
        decodeLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String inputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar
                        + "input.mp4";
                String outputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar
                        + "output_1280x720_yuv420p.yuv";
                PlayerStudyBridge.decode(inputVideo, outputVideo);
            }
        });
    }

}
