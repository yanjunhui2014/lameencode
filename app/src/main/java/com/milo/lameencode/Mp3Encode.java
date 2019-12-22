package com.milo.lameencode;

/**
 * 标题：
 * 功能：
 * 备注：
 * <p>
 * Created by Milo  2019/12/22
 * E-Mail : 303767416@qq.com
 */
public class Mp3Encode {

    static {
        System.loadLibrary("lamemp3");
    }

    public native static String getLameVersion();

    /**
     * @param pcmPath       pcm 路径
     * @param mp3Path       mp3路径
     * @param pcmSampleRate pcm采样率
     * @param pcmChannels   pcm声道数 1或2
     * @param mp3SampleRate mp3采样率
     * @param byteRate      比特率，多为8/16
     * @param mode          0-5，0-立体声(双声道)，1-联合立体，2-lame不支持，3-单身道,4-默认，5-不要使用，系统检测用的
     * @param quality       0-9 级别越小，音质越高，但转换速度会比较慢。3最接近无损，转换不慢， 5又好又快，7音质尚可，转换很快。
     */
    public native static void pcm2Mp3(String pcmPath, String mp3Path, int pcmSampleRate, int pcmChannels, int mp3SampleRate, int byteRate, int mode, int quality);

    /**
     * @param wavPath       wav 路径
     * @param mp3Path       mp3路径
     * @param wavSampleRate wav采样率
     * @param wavChannels   wav声道数 1或2
     * @param mp3SampleRate mp3采样率
     * @param byteRate      比特率，多为8/16
     * @param mode          0-5，0-立体声(双声道)，1-联合立体，2-lame不支持，3-单身道,4-默认，5-不要使用，系统检测用的
     * @param quality       0-9 级别越小，音质越高，但转换速度会比较慢。3最接近无损，转换不慢， 5又好又快，7音质尚可，转换很快。
     */
    public native static void wav2Mp3(String wavPath, String mp3Path, int wavSampleRate, int wavChannels, int mp3SampleRate, int byteRate, int mode, int quality);


}
