package com.caiy.study.activity;

import com.caiy.study.R;
import com.caiy.study.bridge.FmodBridge;
import com.caiy.study.bridge.HelloBridge;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * Created by yongc on 17/4/27.
 */

public class FmodActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fmod);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        String value = FmodBridge.playFixVoice("fmod学习",666);
        tv.setText(value);
    }

}
