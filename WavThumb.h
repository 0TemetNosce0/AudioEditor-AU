#pragma once
#include <functional>

#include "AudioBasic/AudioGlobal.h"
#include "AudioEditor/MinMaxRmsValue.h"
#include "WavTrack.h"
//生成原始thumb
//获取计算后的thumb

class WavThumb
{
public:
    struct Param {
        int64_t trackStartSample = 0;
        int64_t trackDurationSample = 0;
        int visibleWidth = 0;  // pix
    };
    WavThumb();
    ~WavThumb();
    std::vector<MinMaxRmsValue> getWavThumb(WavTrack *trcak, Param audioParam);
    std::vector<MinMaxRmsValue> getWavThumbFromWav(WavTrack *trcak, Param audioParam);

private:
    Param audioParam;
    const int originalSamplesPerThumbnailSample = THUMBNAIL_SAMPLE;
    const int sampleSize = sizeof(float);
    //确保rms不大于波形的min/max //DrawMinMaxRMS
};
