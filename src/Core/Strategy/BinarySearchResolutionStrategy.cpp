#include "BinarySearchResolutionStrategy.h"

namespace ImgSizer {

void BinarySearchResolutionStrategy::SetBaseParams(const EncodeParams& baseParams) {
	m_baseParams = baseParams;
}

StrategyStepResult BinarySearchResolutionStrategy::Next(const CodecsResult& lastAttempt, EncodeParams& nextParams) {
	if (m_iteration != 0 && !lastAttempt.fileSizeBytes) return StrategyStepResult::Failed;
	if (m_iteration >= m_maxIterations) return StrategyStepResult::Failed;

	const auto& target = Target();
	const uint64_t targetBytes = target.targetBytes;
    const double tolerance = targetBytes * target.toleranceRatio;

	if (m_iteration != 0) {
		if (std::llabs(lastAttempt.fileSizeBytes - targetBytes) < tolerance) {
			return StrategyStepResult::Finished;
		}

		if (lastAttempt.fileSizeBytes < targetBytes) {
			m_low = m_scale;
		}
		else if (lastAttempt.fileSizeBytes > targetBytes) {
			m_high = m_scale;
		}
	}

	m_scale = (m_low + m_high) / 2;

	nextParams = m_baseParams;
	nextParams.height = static_cast<int>(1.0 * m_baseParams.height * m_scale);
	nextParams.width = static_cast<int>(1.0 * m_baseParams.width * m_scale);

	m_iteration++;

	return StrategyStepResult::Continue;
}

}