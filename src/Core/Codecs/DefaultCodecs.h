#pragma once

#include "BasicCodecs.h"

namespace ImgSizer {

class DefaultCodecs: public BasicCodecs {
private:
	cv::Mat m_src;
public:
	explicit DefaultCodecs(cv::Mat&& mat) : m_src(std::move(mat)) {}
	~DefaultCodecs() { m_src.release(); }
	CodecsResult Run(const EncodeParams& params) override;
};

}