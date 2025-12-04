#include "SingleConvertBridge.h"

#include <msclr/marshal_cppstd.h>
#include <array>
#include <string>

#include "types.h"
#include "Interface/SingleSizeConvert.h"

using namespace System;
using namespace msclr::interop;

namespace ImgSizer
{
    namespace Bridge
    {
        namespace
        {
            void __stdcall ProgressThunk(int progress, void* userData)
            {
                auto handlerRoot = reinterpret_cast<gcroot<ProgressHandler^>*>(userData);
                if (handlerRoot)
                {
                    ProgressHandler^ handler = *handlerRoot;
                    if (handler != nullptr)
                    {
                        handler->Invoke(progress);
                    }
                }
            }
        }

        ConvertResult SingleConvert::Convert(
            String^ inputPath,
            String^ outputPath,
            long long targetBytes,
            long long originalBytes,
            ProgressHandler^ progressCallback)
        {
            if (String::IsNullOrWhiteSpace(inputPath) || String::IsNullOrWhiteSpace(outputPath))
            {
                return ConvertResult::ErrParams;
            }

            std::string inputNative  = marshal_as<std::string>(inputPath);
            std::string outputNative = marshal_as<std::string>(outputPath);

            ConvertParams params{};
            params.inputPath   = inputNative;
            params.outputPath  = outputNative;
            params.targetBytes = static_cast<std::int64_t>(targetBytes);
            params.originalBytes = static_cast<std::int64_t>(originalBytes);

            gcroot<ProgressHandler^>* handlerRoot = nullptr;
            ProgressCallback nativeCallback = nullptr;
            void* userData = nullptr;

            if (progressCallback != nullptr)
            {
                handlerRoot   = new gcroot<ProgressHandler^>(progressCallback);
                nativeCallback = ProgressThunk;
                userData       = handlerRoot;
            }

            try
            {
                const auto result = SingleSizeConvert(&params, nativeCallback, userData);

                if (handlerRoot)
                {
                    delete handlerRoot;
                    handlerRoot = nullptr;
                }

                return static_cast<ConvertResult>(static_cast<int>(result));
            }
            catch (...)
            {
                if (handlerRoot)
                {
                    delete handlerRoot;
                    handlerRoot = nullptr;
                }
                return ConvertResult::ErrUnknown;
            }
        }
    }
}
