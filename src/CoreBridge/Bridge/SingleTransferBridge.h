#pragma once

#include <vcclr.h>

#include "bridgeTypes.h"

namespace ImgSizer
{
    namespace Bridge
    {
        public delegate void ProgressHandler(int progress);

        public ref class SingleTransfer abstract sealed
        {
        public:
            static TransferResult Convert(
                System::String^ inputPath,
                System::String^ outputPath,
                long long targetBytes,
                long long originalBytes,
                ProgressHandler^ progressCallback);
        };
    }
}