package com.caiy.study.activity;

import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.atomic.AtomicInteger;

import com.caiy.study.R;
import com.caiy.study.bridge.PlayerStudyBridge;
import com.caiy.study.util.ThreadUtil;
import com.caiy.study.view.VideoView;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.SurfaceView;
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
                final String inputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File
                        .separatorChar + "input.mp4";
                final String outputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File
                        .separatorChar + "output_1280x720_yuv420p.yuv";
                ThreadUtil.submit(new Runnable() {
                    @Override
                    public void run() {
                        PlayerStudyBridge.decode(inputVideo, outputVideo);
                    }
                });
            }
        });

        View playerLayout = findViewById(R.id.player_layout);
        final SurfaceView videoView = (SurfaceView)findViewById(R.id.player_video_view);
        playerLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final PlayerStudyBridge bridge = new PlayerStudyBridge();
                final String inputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File
                        .separatorChar  + "input.mp4";
                ThreadUtil.submit(new Runnable() {
                    @Override
                    public void run() {
                        bridge.player(inputVideo,videoView.getHolder().getSurface());
                    }
                });
            }
        });

        View audioPlayerLayout = findViewById(R.id.audio_player_layout);
        audioPlayerLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final PlayerStudyBridge bridge = new PlayerStudyBridge();
                final String inputAudio = Environment.getExternalStorageDirectory().getAbsolutePath() + File
                        .separatorChar  + "fmod.mp3";
                ThreadUtil.submit(new Runnable() {
                    @Override
                    public void run() {
                        bridge.playAudio(inputAudio);
                    }
                });
            }
        });
    }


}
