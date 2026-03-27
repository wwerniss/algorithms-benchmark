#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
PROJECT_ROOT="$(dirname "$(dirname "$SCRIPT_DIR")")"

cd "$PROJECT_ROOT"

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Build directory not found. Running build.sh..."
    "$SCRIPT_DIR/build.sh"
    cd "$PROJECT_ROOT"
fi

# Check if executable exists
APP_EXEC="build/app/AlgorithmsApp"

if [ ! -f "$APP_EXEC" ]; then
    echo "Executable not found at $APP_EXEC. Trying to build..."
    "$SCRIPT_DIR/build.sh"
    cd "$PROJECT_ROOT"
    if [ ! -f "$APP_EXEC" ]; then
        echo "Failed to find or build $APP_EXEC."
        exit 1
    fi
fi

echo "Running $APP_EXEC..."
"$APP_EXEC" "$@"
