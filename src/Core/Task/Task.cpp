#include "Task.h"

#include <fstream>
#include <opencv2/opencv.hpp>

#include "Codecs/Codecs.h"
#include "Strategy/Strategy.h"
#include "utils.h"

namespace ImgSizer {

Task::Task(std::string inputPath,
           std::string outputPath,
           TargetParams target,
           AdvancedOptions advancedOptions,
           std::string strategyName,
           std::string codecsName)
    : m_inputPath(std::move(inputPath))
    , m_outputPath(std::move(outputPath))
    , m_target(std::move(target))
    , m_strategyName(std::move(strategyName))
    , m_codecsName(std::move(codecsName))
{
    m_encodeParams.jpgQuality = 95;
    m_encodeParams.pngCompression = 1;
    m_encodeParams.extension = Util::GetExtension(m_inputPath);

    if (m_encodeParams.extension == ".jpg" || m_encodeParams.extension == ".jpeg")
    {
        m_encodeParams.jpgQuality = Util::clamp(advancedOptions.jpegQuality, 1, 100);
    }
    else if (m_encodeParams.extension == ".png") {
        m_encodeParams.pngCompression = Util::clamp(advancedOptions.pngCompression, 0, 9);
    }
}

ConvertResult Task::Execute()
{
    if (!CreateCodecs()) {
        return ConvertResult::ErrParams;
    }

    if (!CreateStrategy()) {
        return ConvertResult::ErrParams;
    }

    m_strategy->SetBaseParams(m_encodeParams);

    CodecsResult lastAttempt{};
    EncodeParams nextParams{};

    while (true)
    {
        StrategyStepResult step = m_strategy->Next(lastAttempt, nextParams);

        if (step == StrategyStepResult::Finished) {
            break;
        }

        if (step == StrategyStepResult::Failed) {
            return ConvertResult::ErrCodecs;
        }

        lastAttempt = m_codecs->Run(nextParams);
    }

    std::ofstream ofs(m_outputPath, std::ios::binary);
    if (!ofs) {
        return ConvertResult::ErrUnknown;
    }

    ofs.write(reinterpret_cast<const char*>(lastAttempt.buffer.data()),
              static_cast<std::streamsize>(lastAttempt.buffer.size()));

    if (!ofs.good()) {
        return ConvertResult::ErrUnknown;
    }

    return ConvertResult::OK;
}

bool Task::CreateCodecs()
{
    cv::Mat image = cv::imread(m_inputPath, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        return false;
    }

    m_encodeParams.width = image.cols;
    m_encodeParams.height = image.rows;

    if (m_codecsName == "OpenCV") {
        m_codecs = std::make_unique<DefaultCodecs>(std::move(image));
    }
    else {
        m_codecs = std::make_unique<DefaultCodecs>(std::move(image));
    }

    return m_codecs != nullptr;
}

bool Task::CreateStrategy()
{
    if (m_strategyName == "BinarySearchResolution") {
        m_strategy = std::make_unique<BinarySearchResolutionStrategy>(m_target);
    }
    else {
        m_strategy = std::make_unique<BinarySearchResolutionStrategy>(m_target);
    }

    return m_strategy != nullptr;
}

}
