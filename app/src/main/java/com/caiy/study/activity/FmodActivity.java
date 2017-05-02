package com.caiy.study.activity;

import java.io.File;

import com.caiy.study.R;
import com.caiy.study.bridge.FmodBridge;
import com.caiy.study.bridge.HelloBridge;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by yongc on 17/4/27.
 */

public class FmodActivity extends Activity{

    private final String path = Environment.getExternalStorageDirectory().getAbsolutePath() +
                                File.separator +
                                "fmod.mp3";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initView();
        initEvent();
    }

    private void initView() {
        setContentView(R.layout.activity_fmod);
    }

    private void initEvent() {
        //正常播放
        View normalView = findViewById(R.id.normal_layout);
        normalView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FmodBridge.playFixVoice(path,FmodBridge.TYPE_NORMAL);
            }
        });

        //萝莉播放
        View luoLiView = findViewById(R.id.luoli_layout);
        luoLiView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FmodBridge.playFixVoice(path,FmodBridge.TYPE_LUOLI);
            }
        });

        //大叔播放
        View daShuView = findViewById(R.id.dashu_layout);
        daShuView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FmodBridge.playFixVoice(path,FmodBridge.TYPE_DASHU);
            }
        });

        //惊悚播放
        View jingSongView = findViewById(R.id.jingsong_layout);
        jingSongView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(FmodActivity.this,"请自行开启该功能，慎用！",Toast.LENGTH_SHORT).show();
//                FmodBridge.playFixVoice(path,FmodBridge.TYPE_JINGSONG);
            }
        });

        //搞怪播放
        View gaoGuaiView = findViewById(R.id.gaoguai_layout);
        gaoGuaiView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FmodBridge.playFixVoice(path,FmodBridge.TYPE_GAOGUAI);
            }
        });

        //空灵播放
        View kongLingView = findViewById(R.id.kongling_layout);
        kongLingView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FmodBridge.playFixVoice(path,FmodBridge.TYPE_KONGLING);
            }
        });
    }

}
