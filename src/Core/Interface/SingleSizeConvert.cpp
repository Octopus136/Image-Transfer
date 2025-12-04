#include "SingleSizeConvert.h"
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>

#include "Task/Task.h"
#include "utils.h"

namespace ImgSizer
{
    ISExport ConvertResult SingleSizeConvert(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData)
    {
        if (!params || params->inputPath.empty() || params->outputPath.empty())
        {
            return ConvertResult::ErrParams;
        }

        if (params->targetBytes > 10 * params->originalBytes) {
            return ConvertResult::ErrSize;
        }

        try
        {
            Util::BridgeReportProgress(progressCallback, userData, 0);
            Task task(
                std::string(params->inputPath),
                std::string(params->outputPath),
                { params->targetBytes, 0.01 },
                "default",
                "default",
                0);
            ConvertResult result = task.Execute();
            Util::BridgeReportProgress(progressCallback, userData, 100);
            return ConvertResult::OK;
        }
        catch (...)
        {
            return ConvertResult::ErrUnknown;
        }
    }
};