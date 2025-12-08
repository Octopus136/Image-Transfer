#include "DefaultCodecs.h"

namespace ImgSizer {

CodecsResult DefaultCodecs::Run(const EncodeParams& params) {
	cv::Mat resized;
    cv::resize(m_src, resized, cv::Size(params.width, params.height));

    std::vector<uint8_t> buffer;
    bool success = false;

    if (params.extension == ".png") {
        success = cv::imencode(
            params.extension, resized, buffer,
            {cv::IMWRITE_PNG_COMPRESSION, params.pngCompression}
        );
    } else if (params.extension == ".jpg" || params.extension == ".jpeg") {
        success = cv::imencode(
            params.extension, resized, buffer,
            {cv::IMWRITE_JPEG_QUALITY, params.jpgQuality}
        );
    } else {
        return {};
    }

    if (!success) {
        return {};
    }

    CodecsResult result;
    result.fileSizeBytes = buffer.size();
    result.buffer = std::move(buffer);
    return result;
}

}