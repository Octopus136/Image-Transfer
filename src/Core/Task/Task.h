#pragma once

#include <memory>
#include <string>

#include "types.h"
#include "Codecs/BasicCodecs.h"
#include "Strategy/BasicStrategy.h"
#include "ProgressControl/BasicProgressControl.h"

namespace ImgSizer {

class Task {
public:
    Task(std::string inputPath,
         std::string outputPath,
         TargetParams target,
         AdvancedOptions advancedOptions,
         std::string strategyName,
         std::string codecsName,
         BasicProgressControl* progressCtrl);

    ConvertResult Execute();

private:
    std::string m_inputPath;
    std::string m_outputPath;
    TargetParams m_target;
    EncodeParams m_encodeParams;
    std::string m_strategyName;
    std::string m_codecsName;

    std::unique_ptr<BasicCodecs> m_codecs;
    std::unique_ptr<BasicStrategy> m_strategy;

    BasicProgressControl* m_progressCtrl = nullptr;

private:
    bool CreateCodecs();
    bool CreateStrategy();

    void ReportProgress(double ratio) {
        if (m_progressCtrl) {
            m_progressCtrl->Report(ratio);
        }
    }
};

}
