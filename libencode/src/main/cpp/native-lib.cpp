#include <jni.h>
#include <string>
#include <lame.h>

const int BUFF_SIZE = 8192;

extern "C"
JNIEXPORT void JNICALL
Java_com_milo_lameencode_Mp3Encode_pcm2Mp3(JNIEnv *env, jclass type, jstring pcmPath_,
                                           jstring mp3Path_, jint pcmSampleRate, jint pcmChannels,
                                           jint mp3SampleRate, jint byteRate, jint mode,
                                           jint quality) {
    jboolean isCopy;
    const char *cpcm = env->GetStringUTFChars(pcmPath_, &isCopy);
    const char *cmp3 = env->GetStringUTFChars(mp3Path_, &isCopy);

    // 打开pcm文件
    FILE *fpcm = fopen(cpcm, "rb");
    FILE *fmp3 = fopen(cmp3, "wb+");

    int channel = pcmChannels;

    short int wav_buffer[BUFF_SIZE * channel];
    unsigned char mp3_buffer[BUFF_SIZE];

    // init lame
    lame_global_flags *lameConvert;
    lameConvert = lame_init();

    lame_set_in_samplerate(lameConvert, pcmSampleRate);
    lame_set_num_channels(lameConvert, pcmChannels);
    lame_set_out_samplerate(lameConvert, mp3SampleRate);
    if (byteRate > 0) {
        lame_set_brate(lameConvert, byteRate);
    }
    lame_set_mode(lameConvert, (MPEG_mode) mode);
    lame_set_quality(lameConvert, quality);

    lame_set_VBR(lameConvert, vbr_default);
    lame_init_params(lameConvert);
    int read;
    int write;
    int total = 0;
    do {
        read = fread(wav_buffer, sizeof(short int) * channel, BUFF_SIZE, fpcm);
        total += read * sizeof(short int) * channel;
        if (read != 0) {
            write = lame_encode_buffer(lameConvert, wav_buffer, nullptr, read, mp3_buffer,
                                       BUFF_SIZE);
        } else {
            write = lame_encode_flush(lameConvert, mp3_buffer, BUFF_SIZE);
        }
        fwrite(mp3_buffer, 1, write, fmp3);

    } while (read != 0);
    lame_mp3_tags_fid(lameConvert, fmp3);
    lame_close(lameConvert);
    fclose(fpcm);
    fclose(fmp3);

    env->ReleaseStringUTFChars(pcmPath_, cpcm);
    env->ReleaseStringUTFChars(mp3Path_, cmp3);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_milo_lameencode_Mp3Encode_wav2Mp3(JNIEnv *env, jclass type, jstring wavPath_,
                                           jstring mp3Path_, jint wavSampleRate, jint wavChannels,
                                           jint mp3SampleRate, jint byteRate, jint mode,
                                           jint quality) {
    jboolean isCopy;
    const char *cwav = env->GetStringUTFChars(wavPath_, &isCopy);
    const char *cmp3 = env->GetStringUTFChars(mp3Path_, &isCopy);

    // 打开wav文件
    FILE *fwav = fopen(cwav, "rb");

    // 移除wav文件头
    fseek(fwav, 4 * 1024, SEEK_CUR);

    FILE *fmp3 = fopen(cmp3, "wb+");

    int channel = wavChannels;

    short int wav_buffer[BUFF_SIZE * channel];
    unsigned char mp3_buffer[BUFF_SIZE];

    // init lame
    lame_global_flags *lameConvert;
    lameConvert = lame_init();

    lame_set_in_samplerate(lameConvert, wavSampleRate);
    lame_set_num_channels(lameConvert, wavChannels);
    lame_set_out_samplerate(lameConvert, mp3SampleRate);
    if (byteRate > 0) {
        lame_set_brate(lameConvert, byteRate);
    }
    lame_set_mode(lameConvert, (MPEG_mode) mode);
    lame_set_quality(lameConvert, quality);

    lame_set_VBR(lameConvert, vbr_default);
    lame_init_params(lameConvert);
    int read;
    int write;
    int total = 0;
    do {
        read = fread(wav_buffer, sizeof(short int) * channel, BUFF_SIZE, fwav);
        total += read * sizeof(short int) * channel;
        if (read != 0) {
            write = lame_encode_buffer(lameConvert, wav_buffer, nullptr, read, mp3_buffer,
                                       BUFF_SIZE);
        } else {
            write = lame_encode_flush(lameConvert, mp3_buffer, BUFF_SIZE);
        }
        fwrite(mp3_buffer, 1, write, fmp3);

    } while (read != 0);
    lame_mp3_tags_fid(lameConvert, fmp3);
    lame_close(lameConvert);
    fclose(fwav);
    fclose(fmp3);

    env->ReleaseStringUTFChars(wavPath_, cwav);
    env->ReleaseStringUTFChars(mp3Path_, cmp3);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_milo_lameencode_Mp3Encode_getLameVersion(JNIEnv *env, jclass type) {
    return env->NewStringUTF(get_lame_version());
}