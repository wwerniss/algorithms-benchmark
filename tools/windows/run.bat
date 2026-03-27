@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%..\.."
set "APP_EXEC=%PROJECT_ROOT%\build\app\Release\AlgorithmsApp.exe"

cd /d "%PROJECT_ROOT%"

if not exist build (
    echo Build directory not found. Running build.bat...
    call "%SCRIPT_DIR%build.bat"
    cd /d "%PROJECT_ROOT%"
)

if not exist "%APP_EXEC%" (
    echo Executable not found. Running build.bat...
    call "%SCRIPT_DIR%build.bat"
    cd /d "%PROJECT_ROOT%"
    if not exist "%APP_EXEC%" (
        echo Failed to find or build %APP_EXEC%.
        exit /b 1
    )
)

echo Running %APP_EXEC%...
"%APP_EXEC%" %*
