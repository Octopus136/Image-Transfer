[English README](README.md) | [中文 README](README_zh.md)

# ImgSizer

✨ ImgSizer 解决了上传高清照片时的烦恼：很多网站限制图片大小，而现代设备拍摄的照片动辄数十兆，常规压缩软件又难以精准压到指定大小，导致上传屡屡失败。ImgSizer 允许你设置目标体积，确保图片一次达标，无需反复试错。

## 开发指南

### 前置条件
- Windows 10 version 17763 或更高版本
- [.NET 8.0 SDK](https://dotnet.microsoft.com/)
- 安装了 **.NET 桌面开发** 和 **C++ 桌面开发** 工作负载的 [Visual Studio 2022](https://visualstudio.microsoft.com/) （需要用于本地桥接项目）

### 配置环境
- 使用子模块拉取代码：`git clone --recurse-submodules <repo-url>`。
- 运行 `scripts/setup-vcpkg.bat` 即可完成依赖准备（无需自行安装 vcpkg）。首次执行可能较慢，因为 vcpkg 需要构建工具链。
- 加载 `ImgSizer.sln` 解决方案，并将 `Wpf` 项目设置为启动项目。

## 使用指南

1. 在 [Releases](https://github.com/Burnside999/ImgSizer/releases) 页面下载最新版本的 ImgSizer。
2. ImgSizer 的运行需要 .NET 8.0 运行时，请执行 `setup-doenet.bat` 安装。
3. 运行 `ImgSizer.exe` 启动应用。

## 未来计划

- 🚀 支持 CUDA 加速以提升压缩速度。
- 🖥️ 提供命令行接口便于自动化。
- 🗂️ 支持多文件批量转换。

## 致谢

特别感谢 [MAA](https://github.com/MaaAssistantArknights/MaaAssistantArknights) 项目，在前端设计上给予了灵感和借鉴。