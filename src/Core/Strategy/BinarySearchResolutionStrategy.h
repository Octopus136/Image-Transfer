#pragma once

#include "BasicStrategy.h"

namespace ImgSizer {

class BinarySearchResolutionStrategy : public BasicStrategy
{
public:
	BinarySearchResolutionStrategy(const TargetParams& targetParams)
        : BasicStrategy(targetParams)
    {}

	void SetBaseParams(const EncodeParams& baseParams) override;
	StrategyStepResult Next(const CodecsResult& lastAttempt, EncodeParams& nextParams) override;
private:
	double m_low = 0.0;
	double m_high = 5.0;
	double m_scale = 0.0;
	int m_iteration = 0;
	const int m_maxIterations = 16;
	EncodeParams m_baseParams{};
};


}

