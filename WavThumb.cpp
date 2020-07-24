#include "WavThumb.h"

#include <file/file.h>
#include <log/log.h>

#include <algorithm>

#include "AudioLimit.h"
#include "WavReader.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <libavformat/avformat.h>
#include <libavutil/avstring.h>
#include <libavutil/parseutils.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>
#ifdef __cplusplus
}
#endif

// const int16_t  PCMS16MaxValue     =  32767;
// const uint16_t PCMS16MaxAmplitude =  32768; // because minimum is -32768

// float uint16ToFloat(uint16_t val)
//{
//    return float(val) / PCMS16MaxAmplitude;
//}

// uint16_t floatToUint16(float val)
//{
//    return val * PCMS16MaxValue;
//}

WavThumb::WavThumb() {}

WavThumb::~WavThumb() {}

std::vector<MinMaxRmsValue> WavThumb::getWavThumbFromWav(WavTrack *trcak, Param audioParam)
{
    std::vector<int8_t> dataWav;
    int64_t start = audioParam.trackStartSample;
    int64_t duration = audioParam.trackDurationSample;
    int64_t end = start + duration - 1;

    for (auto &clip : trcak->wavClips) {
        int64_t fileOffset = 0;
        int64_t numSamples = 0;
        int64_t clipTrackStart = clip->trackOffsetSample;
        int64_t clipTrackEnd = clip->getTrackEndSample();
        // 6种情况
        if (clipTrackEnd < start) {
            continue;
        } else if (clipTrackStart > end) {
            break;
        } else if (clipTrackStart <= start) {
            // left
            int64_t num = start - clip->trackOffsetSample;
            fileOffset = clip->fileOffsetSample + num;
            // right
            if (clipTrackEnd <= end) {
                numSamples = clip->numSample - num;
            } else {
                numSamples = duration;
            }
        } else {
            fileOffset = clip->fileOffsetSample;
            if (clipTrackEnd > end) {
                numSamples = (end - clipTrackStart) + 1;
            } else {
                numSamples = clip->numSample;
            }
        }

        if (clip->isBlank()) {
            int64_t size = numSamples * sampleSize;
            dataWav.insert(dataWav.end(), size, 0);
        } else {
            WavReader read;
            read.open(clip->fileManage->getWavFileName());
            std::vector<int8_t> dataClip;
            int64_t readSize = numSamples * sampleSize;
            read.seek(fileOffset * sampleSize); // go back to the beginning
            dataClip.resize(readSize);
            uint8_t *buff = reinterpret_cast<uint8_t *>(dataClip.data()); // reinterpret_cast<char*>(alloca(length));
            int64_t len = read.read(buff, readSize);
            if (len < readSize) {
                LOG_INFO("getWavThumbFromWav clip data deficiencies");
            }
            read.wavClose(); // 关闭文件输入流
            dataWav.insert(dataWav.end(), dataClip.begin(), dataClip.end());
        }
    }

    //计算
    std::vector<MinMaxRmsValue> dataThumb;
    int samples = dataWav.size() / sampleSize;
    if (samples > audioParam.visibleWidth) {
        double interval = samples / double(audioParam.visibleWidth);

        float *buffFloat = reinterpret_cast<float *>(dataWav.data());
        //    qDebug()<<"getWavThumbFromWav"<<dataWav.size();
        int8_t max = INT8_MIN;
        int8_t min = INT8_MAX;
        int8_t preMax = INT8_MAX;
        int8_t preMin = INT8_MIN;
        double intervalFractionalPart = 0;
        float rms = 0;
        float sumsq = 0;
        while (samples) {
            max = INT8_MIN;
            min = INT8_MAX;
            sumsq = 0;
            double skip = interval + intervalFractionalPart;
            int len = int(skip);                   // 取整
            intervalFractionalPart = (skip - len); //小数
            len = std::min(len, samples);

            for (int i = 0; (i < len); i++) {

                int8_t value = (int8_t)AudioLimit::aulimit(-128, 127, AudioLimit::roundToInt((*buffFloat) * 127.0f));
                buffFloat++;

                min = std::min(min, value);
                max = std::max(max, value);

//                float f = value;
//                sumsq += (f * f);
            }
//            rms = float(sqrt(sumsq / len));

            min = std::min(min, preMax);
            max = std::max(max, preMin);
            MinMaxRmsValue data{min, max,0};
            preMax = max;
            preMin = min;
            dataThumb.emplace_back(data);
            samples -= len;
        }

    } else {
        float *buffFloat = reinterpret_cast<float *>(dataWav.data());
        while (samples) {
            int8_t value = int8_t(AudioLimit::aulimit(-128, 127, AudioLimit::roundToInt((*buffFloat) * 127.0f)));
            MinMaxRmsValue data{value, value,0};
            dataThumb.emplace_back(data);
            buffFloat++;
            samples--;
        }
    }
    LOG_INFO("getWavThumbFromWav:%d", dataThumb.size());
    return dataThumb;
}
//#include <QDebug>
std::vector<MinMaxRmsValue> WavThumb::getWavThumb(WavTrack *trcak, Param audioParam)
{
    std::vector<int8_t> wavThumbAll;
    int64_t start = audioParam.trackStartSample;
    int64_t duration = audioParam.trackDurationSample;
    int64_t end = start + duration - 1;
    double remainder = 0;
    for (auto &clip : trcak->wavClips) {
        int64_t fileOffset = 0;
        int64_t numSamples = 0;
        int64_t clipTrackStart = clip->trackOffsetSample;
        int64_t clipTrackEnd = clip->getTrackEndSample();
        // 6种情况
        if (clipTrackEnd < start) {
            continue;
        } else if (clipTrackStart > end) {
            break;
        } else if (clipTrackStart <= start) {
            // left
            int64_t num = start - clip->trackOffsetSample;
            fileOffset = clip->fileOffsetSample + num;
            // right
            if (clipTrackEnd <= end) {
                numSamples = clip->numSample - num;
            } else {
                numSamples = duration;
            }
        } else {
            fileOffset = clip->fileOffsetSample;
            if (clipTrackEnd > end) {
                numSamples = (end - clipTrackStart) + 1;
            } else {
                numSamples = clip->numSample;
            }
        }

        double sizeDecimal = numSamples / double(originalSamplesPerThumbnailSample) + remainder;
        int64_t size = sizeDecimal;
        remainder = sizeDecimal - size;
        if (clip->isBlank()) {
            wavThumbAll.insert(wavThumbAll.end(), size * sampleSize, 0);
        } else {
            std::ifstream fileopen;
            file::open_stream(fileopen, clip->fileManage->getThumbFileName(), std::ios::binary);

            std::vector<int8_t> dataClip;
            // TODO:start开始不是originalSamplesPerThumbnailSample的倍数所以开始不同数据就会有不同.
            int64_t thumbStartSample = fileOffset / originalSamplesPerThumbnailSample * sampleSize;
            int64_t thumbSampleReadSize = size * sampleSize;

            if (!fileopen) { //简析
                LOG_WARNING("getWavThumb fileopen fail.");
                wavThumbAll.insert(wavThumbAll.end(), thumbSampleReadSize, 0);
                //                return s;
            } else {                                                  //文件读取
                fileopen.seekg(thumbStartSample, std::ifstream::beg); // go back to the beginning
                dataClip.resize(thumbSampleReadSize);

                char *buff = reinterpret_cast<char *>(dataClip.data()); // reinterpret_cast<char*>(alloca(length));
                fileopen.read(buff, thumbSampleReadSize);

                fileopen.close(); // 关闭文件输入流
                wavThumbAll.insert(wavThumbAll.end(), dataClip.begin(), dataClip.end());
            }
        }
    }

    std::vector<MinMaxRmsValue> trackThumb;

    //计算peak
    uint64_t durationSampls = wavThumbAll.size() / 2/*4*/;

    uint64_t intervalTime = 1;
    double interval = durationSampls / double(audioParam.visibleWidth);

    MinMaxRmsValue val;
//    val.maxAverage = INT8_MIN;
    val.max = INT8_MIN;
//    val.minAverage = INT8_MAX;
    val.min = INT8_MAX;
    //计算值:一个声道,8bit,
    uint64_t dataIndex = 0;
    for (uint64_t i = 0; i < durationSampls; i++) {
        if (i == uint64_t(interval * intervalTime)) {
            trackThumb.emplace_back(val);

            intervalTime++;
//            val.maxAverage = INT8_MIN;
            val.max = INT8_MIN;
//            val.minAverage = INT8_MAX;
            val.min = INT8_MAX;
        }
        val.min = std::min(val.min, wavThumbAll[dataIndex + 0]);
        val.max = std::max(val.max, wavThumbAll[dataIndex + 1]);

//        val.minAverage = std::min(val.minAverage, wavThumbAll[dataIndex + 2]);
//        val.maxAverage = std::max(val.maxAverage, wavThumbAll[dataIndex + 3]);

        dataIndex += 2/*4*/;
    }
    if (1) { // TODO:最后一个不足的 添加
        trackThumb.emplace_back(val);
    }

    LOG_INFO("getWavThumb:%d", trackThumb.size());
    return trackThumb;
}
