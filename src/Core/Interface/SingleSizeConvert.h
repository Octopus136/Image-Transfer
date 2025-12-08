#pragma once
#include "types.h"
#include "Task/ProgressControl/ProgressContext.h"
#include "Task/ProgressControl/DefaultProgressControl.h"

namespace ImgSizer {
    ISExport ConvertResult SingleSizeConvert(
        const SingleSizeConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);
};