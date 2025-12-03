#pragma once
#include "common.hpp"
#include <string>

extern "C" {

enum class TransferResult
{
    OK = 0,
    Failed = 1,
    Cancelled = 2
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