#pragma once
#include <functional>
#include <vector>

struct MinMaxValue {
    int8_t max;
    int8_t min;
};

class WavThumb
{
public:
    struct Param {
        int64_t trackStartSample = 0;
        int64_t trackDurationSample = 0;
        int visibleWidth = 0; // pix
    };
    WavThumb();
    ~WavThumb();
    std::vector<MinMaxValue> getWavThumb(Param audioParam);

private:
    Param audioParam;
    const int sampleSize = sizeof(float);
    //确保rms不大于波形的min/max //DrawMinMaxRMS
};
