package com.caiy.study.activity;

import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.atomic.AtomicInteger;

import com.caiy.study.R;
import com.caiy.study.bridge.PlayerStudyBridge;
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

    private static ExecutorService sThreadPoll = Executors.newCachedThreadPool(new MyThreadFactory());
    private static final String TAG = "PlayerStudyActivity";

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

        View playerLayout = findViewById(R.id.player_layout);
        final SurfaceView videoView = (SurfaceView)findViewById(R.id.player_video_view);
        playerLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final PlayerStudyBridge bridge = new PlayerStudyBridge();
                final String inputVideo = Environment.getExternalStorageDirectory().getAbsolutePath() + File
                        .separatorChar  + "input.mp4";
                sThreadPoll.submit(new Runnable() {
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
                sThreadPoll.submit(new Runnable() {
                    @Override
                    public void run() {
                        bridge.playAudio(inputAudio);
                    }
                });
            }
        });
    }

    private static class MyThreadFactory implements ThreadFactory {
        static final AtomicInteger threadNumber = new AtomicInteger(1);

        @Override
        public Thread newThread(Runnable r) {
            String threadName = TAG + "_" + threadNumber.getAndIncrement();
            Thread thread = new Thread(r,threadName);
            Log.i(TAG,"新创建了线程:" + threadName);
            return thread;
        }
    }

}
