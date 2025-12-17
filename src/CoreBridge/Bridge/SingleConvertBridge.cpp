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
            AdvancedOptions advancedOptions,
            ProgressHandler^ progressCallback)
        {
            if (String::IsNullOrWhiteSpace(inputPath) || String::IsNullOrWhiteSpace(outputPath))
            {
                return ConvertResult::ErrParams;
            }

            std::string inputNative  = marshal_as<std::string>(inputPath);
            std::string outputNative = marshal_as<std::string>(outputPath);

            SingleSizeConvertParams params{};
            params.convertParams.inputPath   = inputNative;
            params.convertParams.outputPath  = outputNative;
            params.convertParams.targetBytes = static_cast<std::int64_t>(targetBytes);
            params.convertParams.originalBytes = static_cast<std::int64_t>(originalBytes);

            params.advancedOptions.useExperimentalStrategy = advancedOptions.useExperimentalStrategy;
            params.advancedOptions.useCUDA = advancedOptions.useCUDA;
            params.advancedOptions.jpegQuality = advancedOptions.jpegQuality;
            params.advancedOptions.pngCompression = advancedOptions.pngCompression;
            params.advancedOptions.toleranceRatio = advancedOptions.toleranceRatio;

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
