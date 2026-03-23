#!/bin/bash
# Build script for Chess Variant Cell-DEVS simulation
# Requires Cadmium v2 to be installed and $CADMIUM environment variable to be set

set -e

echo "=== Building Chess Variant Cell-DEVS ==="

# Check for CADMIUM environment variable
if [ -z "$CADMIUM" ]; then
    echo "Error: CADMIUM environment variable is not set."
    echo "Please set it to the path of the Cadmium v2 include directory."
    echo "Example: export CADMIUM=/path/to/cadmium_v2/include/cadmium"
    exit 1
fi

echo "Using Cadmium at: $CADMIUM"

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

# Build
echo "Building..."
make -j$(nproc 2>/dev/null || echo 4)

echo ""
echo "Build successful!"
echo "Executable created at: bin/chess_variant"
echo ""
echo "Usage: ./bin/chess_variant config/<scenario>.json [simulation_time]"
