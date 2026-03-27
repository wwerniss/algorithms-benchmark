@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%..\.."

cd /d "%PROJECT_ROOT%"

if not exist build mkdir build
cd build

cmake ..
cmake --build . --config Release

echo Build completed.
