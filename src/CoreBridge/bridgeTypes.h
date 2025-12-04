#pragma once

#include <vcclr.h>

namespace ImgSizer
{
    namespace Bridge
    {
        public enum class ConvertResult
        {
            OK = 0,
            ErrParams = 1,
            ErrSize = 2,
            ErrCodecs = 3,
            ErrUnknown = 4,
        };
    }
}