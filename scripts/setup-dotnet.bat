@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: =============================================================================
:: setup-dotnet.bat
:: 自动安装 .NET Desktop Runtime 8.0 (x64)
:: Automatically install .NET Desktop Runtime 8.0 (x64)
:: =============================================================================

:: 定义 ANSI 颜色
for /f %%a in ('echo prompt $E^| cmd') do set "ESC=%%a"
set "RESET=%ESC%[0m"
set "GREEN=%ESC%[32m"
set "RED=%ESC%[31m"
set "YELLOW=%ESC%[33m"
set "BLUE=%ESC%[34m"
set "CYAN=%ESC%[36m"
set "WHITE=%ESC%[37m"
set "BOLD=%ESC%[1m"

:: 初始化错误标志
set "ErrorOccurred=0"

:: 检查管理员权限
openfiles >nul 2>&1
if %errorlevel% neq 0 (
    echo %YELLOW%正在请求管理员权限...%RESET%
    echo %YELLOW%Requesting administrator privileges...%RESET%
    powershell -Command "Start-Process cmd.exe -ArgumentList '/c \"\"%~f0\"\"' -Verb RunAs"
    exit /b
)

echo.
echo %BLUE%====================================================================================================%RESET%
echo %BOLD%%CYAN%正在安装 .NET Desktop Runtime 8.0 (x64)%RESET%
echo %BOLD%%CYAN%Installing .NET Desktop Runtime 8.0 (x64)%RESET%
echo.

echo %YELLOW%如果是第一次使用 winget，可能会提示接受协议，请输入 Y 并按回车继续。%RESET%
echo %YELLOW%If this is your first time using winget, you may be prompted to accept the terms.%RESET%
echo %YELLOW%Please enter Y and press Enter to continue.%RESET%
echo.

:: 检查 winget 是否存在（避免老系统直接报错一大堆）
where winget >nul 2>&1
if %errorlevel% neq 0 (
    set "ErrorOccurred=1"
    goto :NOWINGET
)

:: 使用 winget 安装 .NET Desktop Runtime 8.0
winget install "Microsoft.DotNet.DesktopRuntime.8" ^
    --override "/repair /passive /norestart" ^
    --uninstall-previous ^
    --accept-package-agreements ^
    --force

if %errorlevel% neq 0 (
    set "ErrorOccurred=1"
)

echo %BLUE%====================================================================================================%RESET%
echo.

if %ErrorOccurred% equ 0 (
    echo %BOLD%%GREEN%.NET Desktop Runtime 8.0 安装/修复完成！%RESET%
    echo %BOLD%%GREEN%The .NET Desktop Runtime 8.0 installation/repair is complete!%RESET%
    echo.
    echo %CYAN%现在可以直接运行本程序（基于 .NET 8 桌面运行时）。%RESET%
    echo %CYAN%You can now run this application (which depends on .NET 8 Desktop Runtime).%RESET%
    echo.
    goto :END
)

:NOWINGET
echo %RED%====================================================================================================%RESET%
echo %BOLD%%RED%安装 .NET Desktop Runtime 8.0 时出现错误%RESET%
echo %BOLD%%RED%Errors occurred while installing .NET Desktop Runtime 8.0%RESET%
echo.

echo %YELLOW%如果提示%RESET% %WHITE%'winget' is not recognized...%RESET% %YELLOW%说明系统过旧或未安装 winget。%RESET%
echo %YELLOW%If you see%RESET% %WHITE%'winget' is not recognized...%RESET% %YELLOW%your system is too old or winget is not installed.%RESET%
echo.
echo %YELLOW%你可以手动复制以下链接到浏览器中打开，下载并安装 .NET Desktop Runtime 8.0 (x64)：%RESET%
echo %YELLOW%You can manually copy the following link into your browser to download and install .NET Desktop Runtime 8.0 (x64):%RESET%
echo.
echo %WHITE%.NET Desktop Runtime 8.0 (x64):%RESET%
echo %CYAN%https://aka.ms/dotnet/8.0/windowsdesktop-runtime-win-x64.exe%RESET%
echo.
echo %YELLOW%安装完成后，无需再次运行本脚本，直接启动程序即可。%RESET%
echo %YELLOW%After installation, you don't need to run this script again. Just start the application.%RESET%
echo %RED%====================================================================================================%RESET%

:END
echo.
pause
