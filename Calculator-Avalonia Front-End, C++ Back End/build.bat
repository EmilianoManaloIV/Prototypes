@echo off
REM Build script for BigNumber Calculator - Windows

echo Building BigNumber Calculator...

REM Create directories if they don't exist
if not exist "obj" mkdir obj
if not exist "bin" mkdir bin

REM Set compiler flags
set COMMON_FLAGS=-Wall -Wextra -std=c++11
set DEBUG_FLAGS=-g -O0 -DDEBUG
set RELEASE_FLAGS=-O3 -DNDEBUG

REM Determine build type
set BUILD_TYPE=release
if "%1"=="debug" set BUILD_TYPE=debug
if "%1"=="clean" goto clean

if "%BUILD_TYPE%"=="debug" (
    echo Building debug version...
    set FLAGS=%COMMON_FLAGS% %DEBUG_FLAGS%
    set EXE_NAME=bin\calculator_debug.exe
) else (
    echo Building release version...
    set FLAGS=%COMMON_FLAGS% %RELEASE_FLAGS%
    set EXE_NAME=bin\calculator.exe
)

REM Compile source files
echo Compiling source files...
g++ %FLAGS% -c -o obj\BigNumber.o BigNumber.cpp
if %errorlevel% neq 0 goto error

g++ %FLAGS% -c -o obj\StringCalculator.o StringCalculator.cpp
if %errorlevel% neq 0 goto error

g++ %FLAGS% -c -o obj\main.o main.cpp
if %errorlevel% neq 0 goto error

REM Link object files
echo Linking...
g++ %FLAGS% -o %EXE_NAME% obj\main.o obj\BigNumber.o obj\StringCalculator.o
if %errorlevel% neq 0 goto error

echo Build completed successfully!
echo Executable: %EXE_NAME%

REM Run if requested
if "%1"=="run" (
    echo Running program...
    %EXE_NAME%
)
goto end

:clean
echo Cleaning build files...
if exist "obj" rmdir /s /q obj
if exist "bin" rmdir /s /q bin
echo Clean completed.
goto end

:error
echo Build failed with error %errorlevel%!
exit /b %errorlevel%

:end 