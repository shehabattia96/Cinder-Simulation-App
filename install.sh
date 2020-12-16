#!/bin/bash

## Script clones submodules and attempts to build them using CMAKE.
## Run with -e to build examples. -v Release|Debug to build variants.

SCRIPT_DIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )" # copypasta from https://stackoverflow.com/a/4774063/

# Options
BUILD_VARIANT=Debug #or Release
BUILD_EXAMPLES=0

# Parse args - references https://stackoverflow.com/a/33826763/9824103
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -v|--variant) BUILD_VARIANT="$2"; shift ;;
        -e|--examples) BUILD_EXAMPLES=1 ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done
echo "BUILD_VARIANT is $BUILD_VARIANT. Set with the -v flag (Debug|Release)."


# Clone submodules
git submodule update --init --recursive


# Build Cinder -- assumes it's under externals/Cinder and assumes you have CMAKE installed and configured.
CINDER_DIR="$SCRIPT_DIR/externals/Cinder/"
cmake "$CINDER_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -H$CINDER_DIR -B$CINDER_DIR/build
cmake --build "$CINDER_DIR/build" --config $BUILD_VARIANT -- /maxcpucount:18


# Build CinderSimulationApp
cmake -DBUILD_EXAMPLES=$BUILD_EXAMPLES "$SCRIPT_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -H$SCRIPT_DIR -B$SCRIPT_DIR/build
cmake --build ./build --config $BUILD_VARIANT --target ALL_BUILD -- /maxcpucount:18

if (($BUILD_EXAMPLES != 1)); then
    echo "Build examples is off. Build examples with the -e flag."
fi

