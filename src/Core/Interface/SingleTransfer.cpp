#include "SingleTransfer.h"
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>

#include "opencv2/opencv.hpp"
#include "Utils.hpp"

namespace ImgSizer
{
    const int MAX_TRIES = 20;

    ISExport TransferResult ConvertSingleImage(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData)
    {
        if (!params || params->inputPath.empty() || params->outputPath.empty())
        {
            return TransferResult::ErrParams;
        }

        try
        {
            int progress = 0;
            Util::ReportProgress(progressCallback, userData, 0);

            // core logic begin
            cv::Mat input_img = cv::imread(params->inputPath, cv::IMREAD_UNCHANGED);
	        int height = input_img.rows;
	        int width = input_img.cols;
	        cv::Mat resize_img;
	        int transfer_count = 0;
	        double l = 0, r = 10;
            std::int64_t targetBytes = params->targetBytes;
            std::int64_t originalBytes = params->originalBytes;
	        if (targetBytes > 10 * originalBytes) {
                return TransferResult::ErrSize;
	        }
	        std::vector<uchar> encoded_data;
            std::string ext = Util::GetExtension(params->outputPath);
	        while (l <= r) {
		        transfer_count++;
		        if (transfer_count > MAX_TRIES) {
			        break;
		        }
		        double mid = (l + r) / 2;
		        cv::resize(input_img, resize_img, cv::Size(int(1.0 * mid * width), int(1.0 * mid * height)));
		        bool success = cv::imencode(ext, resize_img, encoded_data);
		        if (!success) {
			        return TransferResult::ErrCodecs;
		        }
		        std::int64_t nowBytes = encoded_data.size();
                Util::ReportProgress(progressCallback, userData, transfer_count * 100 / MAX_TRIES);
		        if (1.0 * std::abs(nowBytes - targetBytes) / targetBytes < 0.01) {
			        break;
		        }
		        else if (nowBytes > targetBytes) r = mid;
		        else if (nowBytes < targetBytes) l = mid;
	        }

		    std::ofstream file(params->outputPath, std::ios::binary);
		    file.write(reinterpret_cast<const char*>(encoded_data.data()), encoded_data.size());
		    file.close();
            // core logic end

            Util::ReportProgress(progressCallback, userData, 100);
            return TransferResult::OK;
        }
        catch (...)
        {
            return TransferResult::ErrUnknown;
        }
    }
};