#include "SingleTransfer.h"
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>

#include "opencv2/opencv.hpp"

namespace ImageTransfer
{
    std::wstring g_lastError;

    const int MAX_TRIES = 20;

    static void SetLastError(const wchar_t* msg)
    {
        g_lastError = msg ? msg : L"";
    }

    std::string GetExtension(const std::string& path)
    {
        size_t pos = path.find_last_of('.');
        if (pos == std::string::npos) return "";
        return path.substr(pos);
    }

    ITExport TransferResult ConvertSingleImage(
        const ConvertParams* params,
        ProgressCallback progressCallback,
        void* userData)
    {
        if (!params || params->inputPath.empty() || params->outputPath.empty())
        {
            SetLastError(L"Invalid parameters");
            return TransferResult::Failed;
        }

        try
        {
            int progress = 0;
            auto reportProgress = [&](int p)
                {
                    if (p < 0) p = 0;
                    if (p > 100) p = 100;
                    progress = p;
                    if (progressCallback)
                    {
                        progressCallback(progress, userData);
                    }
                };

            reportProgress(0);

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
                SetLastError(L"Too Large to Convert");
                return TransferResult::Failed;
	        }
	        std::vector<uchar> encoded_data;
            std::string ext = GetExtension(params->outputPath);
	        while (l <= r) {
		        transfer_count++;
		        if (transfer_count > MAX_TRIES) {
			        break;
		        }
		        double mid = (l + r) / 2;
		        cv::resize(input_img, resize_img, cv::Size(int(1.0 * mid * width), int(1.0 * mid * height)));
		        bool success = cv::imencode(ext, resize_img, encoded_data);
		        if (!success) {
                    SetLastError(L"Encode Failed");
			        return TransferResult::Failed;
		        }
		        std::int64_t nowBytes = encoded_data.size();
                progressCallback(transfer_count * 100 / MAX_TRIES, userData);
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

            reportProgress(100);
            SetLastError(nullptr);
            return TransferResult::OK;
        }
        catch (...)
        {
            SetLastError(L"Unknown error in ConvertImage");
            return TransferResult::Failed;
        }
    }

    ITExport void GetLastErrorMessage(wchar_t* buffer, int bufferLen)
    {
        if (!buffer || bufferLen <= 0)
            return;

        if (g_lastError.empty())
        {
            buffer[0] = L'\0';
            return;
        }

        wcsncpy_s(buffer, bufferLen, g_lastError.c_str(), _TRUNCATE);
    }

};