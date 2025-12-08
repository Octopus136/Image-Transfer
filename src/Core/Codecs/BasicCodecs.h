#pragma once

#include <vector>
#include "types.h"

#include "opencv2/opencv.hpp"

namespace ImgSizer {

struct EncodeParams {
    int jpgQuality;
    int pngCompression;
    int width;
    int height;
    std::string extension;
};

struct CodecsResult {
	std::size_t fileSizeBytes = 0;
	std::vector<std::uint8_t> buffer;
};

class BasicCodecs {
public:
	virtual ~BasicCodecs() = default;
	virtual CodecsResult Run(const EncodeParams& params) = 0;
};

}