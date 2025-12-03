@echo off
setlocal enabledelayedexpansion

REM vcpkg will be placed under external/vcpkg relative to repo root
set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..\") do set "REPO_ROOT=%%~fI"
set "VCPKG_ROOT=%REPO_ROOT%external\vcpkg"

pushd "%VCPKG_ROOT%"
if exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo [vcpkg] bootstrap already completed.
) else (
    echo [vcpkg] bootstrapping...
    call .\bootstrap-vcpkg.bat
    if errorlevel 1 (
        echo Failed to bootstrap vcpkg.
        popd
        exit /b 1
    )
)

set "TRIPLET=x64-windows"
if not "%1"=="" set "TRIPLET=%~1"

REM Install dependencies in manifest mode (repo root contains vcpkg.json)
echo [vcpkg] installing manifest dependencies for triplet %TRIPLET% ...
"%VCPKG_ROOT%\vcpkg.exe" install --triplet "%TRIPLET%" --host-triplet "%TRIPLET%" --feature-flags=manifests --binarycaching
if errorlevel 1 (
    echo vcpkg install failed.
    popd
    exit /b 1
)

REM Surface environment hint for MSBuild
setx VCPKG_ROOT "%VCPKG_ROOT%"

popd
echo.
echo vcpkg is ready. You can now open ImageTransfer.sln and build with OpenCV available.