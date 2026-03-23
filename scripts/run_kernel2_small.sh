#!/bin/bash
# Run Chess Variant Kernel 2 Small Grid scenario (5x9 wrapped)

set -e

EXECUTABLE="./bin/chess_variant"
SIM_TIME=${1:-60}

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found. Run 'bash build_sim.sh' first."
    exit 1
fi

mkdir -p logs
$EXECUTABLE config/chessVariantKernel2SmallGrid.json $SIM_TIME
