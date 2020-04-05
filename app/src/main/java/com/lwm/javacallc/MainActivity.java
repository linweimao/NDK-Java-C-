package com.lwm.javacallc;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

// 点击按钮时会操作 JNITest，然后操作 Test.c
public class MainActivity extends Activity implements View.OnClickListener {


    private static final String TAG = MainActivity.class.getSimpleName();
    private JNITest jniTest;
    private Button add;
    private Button string;
    private Button array;
    private Button checkpw;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniTest = new JNITest();
        initView();
    }

    private void initView() {
        add = (Button) findViewById(R.id.add);
        string = (Button) findViewById(R.id.string);
        array = (Button) findViewById(R.id.array);
        checkpw = (Button) findViewById(R.id.checkpw);
        add.setOnClickListener(this);
        string.setOnClickListener(this);
        array.setOnClickListener(this);
        checkpw.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.add:
                add();
                break;
            case R.id.string:
                string();
                break;
            case R.id.array:
                array();
                break;
            case R.id.checkpw:
                checkpw();
                break;
        }
    }

    public void add() {
        int result = jniTest.add(99, 1);
        Log.e(TAG, "result: " + result);
        Toast.makeText(MainActivity.this, "result: " + result, Toast.LENGTH_SHORT).show();
    }

    public void string() {

        String result = jniTest.sayHello("I am from Java ");
        Log.e(TAG, "result: " + result);
        Toast.makeText(MainActivity.this, "result: " + result, Toast.LENGTH_SHORT).show();
    }

    // 处理图片时就用到这个（C语言处理数组）
    public void array() {
        int array[] = {1, 2, 3, 4, 5};
        int[] result = jniTest.increaseArrayEles(array);
        for (int i = 0; i < array.length; i++) {
            // 为什么不接收(jniTest.increaseArrayEles(array);)数组的值，而用 array 去打印
            // 因为 array 对应内存地址的值被操作了，所以值变了
            Log.e(TAG, "array[" + i + "]= " + result[i]);
            Toast.makeText(MainActivity.this, "array[" + i + "]= " + result[i], Toast.LENGTH_SHORT).show();
        }
    }

    public void checkpw() {
        int result = jniTest.checkPwd("123456");
        Log.e(TAG, "result= " + result);
        Toast.makeText(MainActivity.this, "result= " + result, Toast.LENGTH_SHORT).show();
    }

}
