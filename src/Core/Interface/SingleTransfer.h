#pragma once
#include "types.h"

namespace ImageTransfer {
    ITExport TransferResult ConvertSingleImage(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData);

    ITExport void GetLastErrorMessage(wchar_t* buffer, int bufferLen);
};