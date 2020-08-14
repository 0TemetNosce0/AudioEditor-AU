#include "WavThumb.h"

#include <QDebug>
#include <algorithm>
#include <fstream>
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

std::vector<MinMaxValue> WavThumb::getWavThumb(Param audioParam)
{
    std::vector<int8_t> wavThumbAll;
    int64_t start = audioParam.trackStartSample*2;
    int64_t duration = audioParam.trackDurationSample;
    int64_t end = start + duration - 1;
    int64_t thumbSampleReadSize = duration*2*1;
    std::ifstream fileopen;
    fileopen.open("F:/TemetNosce-gitee/AudioEditor-AU/wavthumbtest.tmp", std::ios::binary);

    if (!fileopen) { //简析
        qDebug("getWavThumb fileopen fail.");

        //                return s;
    } else {                                       //文件读取
        fileopen.seekg(start, std::ifstream::beg); // go back to the beginning
        wavThumbAll.resize(thumbSampleReadSize);

        char *buff = reinterpret_cast<char *>(wavThumbAll.data()); // reinterpret_cast<char*>(alloca(length));
        fileopen.read(buff, thumbSampleReadSize);

        fileopen.close(); // 关闭文件输入流
    }

    std::vector<MinMaxValue> trackThumb;

    //计算peak
    uint64_t durationSampls = wavThumbAll.size() /2 /*4*/;

    uint64_t intervalTime = 1;
    double interval = durationSampls / double(audioParam.visibleWidth);

    MinMaxValue val;
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
        dataIndex += 2 /*4*/;
    }
    if (1) { // TODO:最后一个不足的 添加
        trackThumb.emplace_back(val);
    }

    qDebug() << "getWavThumb:%d" << trackThumb.size();
    return trackThumb;
}
