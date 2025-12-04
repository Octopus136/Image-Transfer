#pragma once

#include <vcclr.h>

#include "bridgeTypes.h"

namespace ImgSizer
{
    namespace Bridge
    {
        public delegate void ProgressHandler(int progress);

        public ref class SingleConvert abstract sealed
        {
        public:
            static ConvertResult Convert(
                System::String^ inputPath,
                System::String^ outputPath,
                long long targetBytes,
                long long originalBytes,
                ProgressHandler^ progressCallback);
        };
    }
}