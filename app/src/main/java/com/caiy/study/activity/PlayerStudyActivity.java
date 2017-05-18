package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.PlayerStudyBridge;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by yongc on 2017/5/16.
 */

public class PlayerStudyActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player_study);

        PlayerStudyBridge.init();
    }
}
