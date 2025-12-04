#pragma once
#include "types.h"

namespace ImgSizer {
    ISExport TransferResult ConvertSingleImage(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);
};