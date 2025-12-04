#include "utils.h"

namespace ImgSizer {
    namespace Util {
        template <typename T>
        const T& clamp(const T& v, const T& lo, const T& hi)
        {
            return (v < lo) ? lo : (v > hi ? hi : v);
        }

        std::string GetExtension(const std::string& path)
        {
            size_t pos = path.find_last_of('.');
            if (pos == std::string::npos) return "";
            return path.substr(pos);
        }

        void BridgeReportProgress(const ProgressCallback& callback, void* userData, int progress)
        {
            if (!callback) return;
            progress = clamp(progress, 0, 100);
            callback(progress, userData);
        };
    }
};