#pragma once

#include <vcclr.h>

namespace ImageTransfer
{
    namespace Bridge
    {
        public enum class TransferResult
        {
            OK = 0,
            Failed = 1,
            Cancelled = 2
        };
    }
}