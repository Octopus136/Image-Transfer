[中文 README](README_zh.md) | [English README](README.md)

# ImgSizer

✨ ImgSizer solves the frustration of uploading high-resolution photos to sites with strict size caps. Modern cameras create multi-megabyte images that exceed common upload limits, and off-the-shelf compressors rarely hit a specific target size. ImgSizer lets you set the exact output size so your photos meet website requirements without guesswork.

## Getting Started

### Prerequisites
- Windows 10 version 17763 or later
- [.NET 8.0 SDK](https://dotnet.microsoft.com/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/) with **.NET desktop development** and **Desktop development with C++** workloads (needed for the native bridge projects)

### Setup
- Clone with submodules: `git clone --recurse-submodules <repo-url>`
- Bootstrap dependencies via `scripts/setup-vcpkg.bat` (no manual vcpkg install needed). The first run can take a while as vcpkg builds toolchains.
- Load `ImgSizer.sln` solution and set `Wpf` project as startup.

## Usage

1. Download the latest version of ImgSizer from the [Releases](https://github.com/Burnside999/ImgSizer/releases) page.
2. ImgSizer requires the .NET 8.0 runtime. Run `setup-doenet.bat` to install it.
3. Launch `ImgSizer.exe` to start the application.

## Roadmap

- 🚀 CUDA acceleration for faster compression.
- 🖥️ Command-line interface for automation.
- 🗂️ Multi-file batch conversion.

## Acknowledgements

Special thanks to the [MAA](https://github.com/MaaAssistantArknights/MaaAssistantArknights) project for inspiring parts of the front-end design.