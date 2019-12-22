package com.milo.lameencode.demo;

import android.Manifest;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.milo.lameencode.Mp3Encode;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView sampleText;
    private Button   mBtnPcm2Mp3;
    private Button   mBtnWav2Mp3;

    private static final String WAV     = Environment.getExternalStorageDirectory().toString() + "/test/0.wav";
    private static final String WAV2MP3 = Environment.getExternalStorageDirectory().toString() + "/test/wav2mp3.mp3";

    private static final String PCM     = Environment.getExternalStorageDirectory().toString() + "/test/1.pcm";
    private static final String PCM2MP3 = Environment.getExternalStorageDirectory().toString() + "/test/pcm2mp31.mp3";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();

        sampleText.setText(Mp3Encode.getLameVersion());

        requestPermissions(new String[]{Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE}, 100);
    }

    @Override
    public void onClick(View v) {
        if (v == mBtnPcm2Mp3) {
            Mp3Encode.pcm2Mp3(PCM, PCM2MP3, 44100, 1, 44100, 0, 3, 3);
        } else if (v == mBtnWav2Mp3) {
            Mp3Encode.wav2Mp3(WAV, WAV2MP3, 16000, 1, 16000, 0, 3, 3);
        }
    }

    private void initView() {
        sampleText = (TextView) findViewById(R.id.sample_text);
        mBtnPcm2Mp3 = (Button) findViewById(R.id.mBtnPcm2Mp3);
        mBtnPcm2Mp3.setOnClickListener(this);

        mBtnWav2Mp3 = (Button) findViewById(R.id.mBtnWav2Mp3);
        mBtnWav2Mp3.setOnClickListener(this);
    }

}
