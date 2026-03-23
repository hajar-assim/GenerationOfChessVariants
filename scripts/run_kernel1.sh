#!/bin/bash
# Run Chess Variant Kernel 1 scenario (9x13 wrapped, plus-shaped seed)

set -e

EXECUTABLE="./bin/chess_variant"
SIM_TIME=${1:-60}

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found. Run 'bash build_sim.sh' first."
    exit 1
fi

mkdir -p logs
$EXECUTABLE config/chessVariantKernel1.json $SIM_TIME
