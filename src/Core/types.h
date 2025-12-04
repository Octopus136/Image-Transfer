#pragma once
#include "common.h"
#include <string>

extern "C" {

enum class ConvertResult
{
    OK = 0,
    ErrParams = 1,
    ErrSize = 2,
    ErrCodecs = 3,
    ErrUnknown = 4,
};

typedef void(__stdcall* ProgressCallback)(int progress, void* userData);

struct ConvertParams
{
    std::string inputPath;
    std::string outputPath;
    std::size_t targetBytes;
    std::size_t originalBytes;
};

struct EncodeParams {
    int jpgQuality;
    int pngCompression;
    int width;
    int height;
    std::string extension;
};

}