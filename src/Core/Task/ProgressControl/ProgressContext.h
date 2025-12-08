// BatchProgress.h
#pragma once

#include <vector>
#include <atomic>
#include "BasicProgressControl.h"
#include "utils.h"
#include "types.h"

#include <fstream>

namespace ImgSizer {

class ProgressContext {
private:
    int totalImages = 0;
    ProgressCallback callback = nullptr;
    void* userData = nullptr;

    std::vector<std::atomic<double>> perImageProgress;

    std::atomic<int> lastReportedPercent{ -1 };

public:
    ProgressContext(int n, ProgressCallback cb, void* ud);
    void UpdateImageProgress(int index, double ratio);
};

} // namespace ImgSizer
