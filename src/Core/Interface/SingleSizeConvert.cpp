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
        const SingleSizeConvertParams* params,
        ProgressCallback progressCallback,
        void* userData)
    {
        if (!params || params->convertParams.inputPath.empty() || params->convertParams.outputPath.empty())
        {
            return ConvertResult::ErrParams;
        }

        if (params->convertParams.targetBytes > 10 * params->convertParams.originalBytes) {
            return ConvertResult::ErrSize;
        }

        try
        {
            Util::BridgeReportProgress(progressCallback, userData, 0);
            Task task(
                std::string(params->convertParams.inputPath),
                std::string(params->convertParams.outputPath),
                { params->convertParams.targetBytes, 0.01 },
                params->advancedOptions,
                "default",
                "default");
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