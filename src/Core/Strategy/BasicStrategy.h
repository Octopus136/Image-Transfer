#pragma once

#include "types.h"
#include "Codecs/BasicCodecs.h"

namespace ImgSizer {

enum class StrategyStepResult
{
    Continue = 0,
    Finished = 1,
    Failed = 2,
};

struct TargetParams {
    std::size_t targetBytes = 0;
    double toleranceRatio = 0.01;
};

class BasicStrategy {
private:
    TargetParams m_targetParams;
public:
    BasicStrategy(const TargetParams& targetParams)
        : m_targetParams(targetParams)
    {}
    virtual ~BasicStrategy() = default;

    BasicStrategy(const BasicStrategy&) = delete;
    BasicStrategy& operator=(const BasicStrategy&) = delete;

    BasicStrategy(BasicStrategy&&) = default;
    BasicStrategy& operator=(BasicStrategy&&) = default;

    virtual void SetBaseParams(const EncodeParams& baseParams) = 0;
    virtual StrategyStepResult Next(const CodecsResult& lastAttempt, EncodeParams& nextParams) = 0;

protected:
    const TargetParams& Target() const noexcept { return m_targetParams; }
};

}