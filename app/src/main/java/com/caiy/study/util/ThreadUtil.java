package com.caiy.study.util;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.atomic.AtomicInteger;

import com.caiy.study.activity.PlayerStudyActivity;

import android.util.Log;

/**
 * Created by yongc on 2017/5/22.
 */

public class ThreadUtil {

    private static ExecutorService sThreadPoll = Executors.newCachedThreadPool(new ThreadUtil.MyThreadFactory());
    private static final String TAG = "ThreadUtil";


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

    public static void submit(Runnable runnable){
        sThreadPoll.submit(runnable);
    }
}
