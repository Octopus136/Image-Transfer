#pragma once
#include "types.h"

namespace ImgSizer {
    ISExport ConvertResult SingleSizeConvert(
        const SingleSizeConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);
};