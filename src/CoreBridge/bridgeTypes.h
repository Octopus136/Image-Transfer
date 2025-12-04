#pragma once

#include <vcclr.h>

namespace ImageTransfer
{
    namespace Bridge
    {
        public enum class TransferResult
        {
            OK = 0,
            ErrParams = 1,
            ErrSize = 2,
            ErrCodecs = 3,
            ErrUnknown = 4,
        };
    }
}