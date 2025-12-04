#pragma once
#include "common.hpp"
#include <string>

extern "C" {

enum class TransferResult
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
    std::int64_t targetBytes;
    std::int64_t originalBytes;
};

}