#pragma once
#include "types.h"

namespace ImgSizer {
    ISExport ConvertResult SingleSizeConvert(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);
};