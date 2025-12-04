#pragma once

#include <string>
#include <algorithm>
#include "types.h"

namespace ImgSizer {
    namespace Util {
        template <typename T>
        const T& clamp(const T& v, const T& lo, const T& hi);

        std::string GetExtension(const std::string& path);

        void BridgeReportProgress(const ProgressCallback& callback, void* userData, int progress);
    }
};