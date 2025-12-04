#pragma once
#include "types.h"

namespace ImageTransfer {
    ITExport TransferResult ConvertSingleImage(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);
};