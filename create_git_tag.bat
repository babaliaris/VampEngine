@echo off
setlocal EnableDelayedExpansion

:: Colors (ANSI escape codes – works in Windows 10+ with virtual terminal processing)
for /f "delims=" %%a in ('"prompt $E & for %%b in (1) do rem"') do set "ESC=%%a"
set "BOLD=%ESC%[1m"
set "YELLOW=%ESC%[33m"
set "GREEN=%ESC%[32m"
set "RED=%ESC%[31m"
set "CYAN=%ESC%[36m"
set "RESET=%ESC%[0m"

:: Enable colors (only needed in some versions of Windows)
reg query HKCU\Console 1>nul 2>nul || reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1 /f >nul

:: Show help
if "%1"=="help" (
    echo.
    echo %BOLD%%CYAN%Tag the current Git commit with a video episode marker.%RESET%
    echo.
    echo %BOLD%Usage:%RESET%
    echo   create_git_tag.bat %YELLOW%^<episode-number^>%RESET% [%YELLOW%-f%RESET%]
    echo.
    echo %BOLD%Examples:%RESET%
    echo   create_git_tag.bat %YELLOW%3%RESET%       %GREEN%# → Tags as video-ep3 (fails if tag exists)%RESET%
    echo   create_git_tag.bat %YELLOW%3 -f%RESET%    %GREEN%# → Force-overwrites video-ep3%RESET%
    echo.
    exit /b 0
)

:: Check episode number
if "%1"=="" (
    echo %RED%❌ Error: No episode number provided.%RESET%
    echo Run %YELLOW%"create_git_tag.bat help"%RESET% for usage info.
    exit /b 1
)

set "EP_NUM=%1"
set "FORCE_FLAG=%2"
set "TAG_NAME=video-ep%EP_NUM%"

:: Check if tag exists
git rev-parse --verify "%TAG_NAME%" >nul 2>&1
if "%ERRORLEVEL%"=="0" (
    if /i not "%FORCE_FLAG%"=="-f" (
        echo %RED%❌ Tag "%TAG_NAME%" already exists.%RESET%
        echo Use %YELLOW%-f%RESET% to force overwrite.
        exit /b 1
    ) else (
        echo %YELLOW%⚠️  Forcing overwrite of tag "%TAG_NAME%"%RESET%
    )
)

:: Tag and push
if /i "%FORCE_FLAG%"=="-f" (
    git tag -f "%TAG_NAME%"
    git push origin -f "%TAG_NAME%"
) else (
    git tag "%TAG_NAME%"
    git push origin "%TAG_NAME%"
)

echo %GREEN%✅ Tagged current commit as "%TAG_NAME%"%RESET%
