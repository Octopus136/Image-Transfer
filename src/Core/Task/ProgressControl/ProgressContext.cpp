#include "ProgressContext.h"

namespace ImgSizer {

ProgressContext::ProgressContext(int n, ProgressCallback cb, void* ud) 
    : totalImages(n)
    , callback(cb)
    , userData(ud)
    , perImageProgress(n)
{
    for (int i = 0; i < n; ++i) {
        perImageProgress[i].store(0.0, std::memory_order_relaxed);
    }
}

void ProgressContext::UpdateImageProgress(int index, double ratio) {

    if (index < 0 || index >= totalImages) return;
    if (!callback) return;

    if (ratio < 0.0) ratio = 0.0;
    if (ratio > 1.0) ratio = 1.0;

    perImageProgress[index].store(ratio, std::memory_order_relaxed);

    double sum = 0.0;
    for (int i = 0; i < totalImages; ++i) {
        sum += perImageProgress[i].load(std::memory_order_relaxed);
    }

    double totalRatio = sum / static_cast<double>(totalImages);

    int percent = static_cast<int>(totalRatio * 100.0 + 0.5);
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    int prev = lastReportedPercent.load(std::memory_order_relaxed);
    if (percent == prev) {
        return;
    }

    if (!lastReportedPercent.compare_exchange_strong(prev, percent, std::memory_order_relaxed)) {
        return;
    }

    Util::BridgeReportProgress(callback, userData, percent);
}

}