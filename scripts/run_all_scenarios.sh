#!/bin/bash
# Run all 14 Chess Variant Cell-DEVS scenarios
# Output CSV files are written to logs/

set -e

EXECUTABLE="./bin/chess_variant"
SIM_TIME=60

echo "=== Running All Chess Variant Scenarios ==="
echo "Simulation time: $SIM_TIME generations"
echo ""

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE"
    echo "Please run 'bash build_sim.sh' first."
    exit 1
fi

# Create logs directory
mkdir -p logs

echo "--- Group A: Baseline (Original CD++ Model) ---"
echo "Running chessVariantKernel1..."
$EXECUTABLE config/chessVariantKernel1.json $SIM_TIME

echo "Running chessVariantKernel2..."
$EXECUTABLE config/chessVariantKernel2.json $SIM_TIME

echo "Running chessVariantKernel1SmallGrid..."
$EXECUTABLE config/chessVariantKernel1SmallGrid.json $SIM_TIME

echo "Running chessVariantKernel2SmallGrid..."
$EXECUTABLE config/chessVariantKernel2SmallGrid.json $SIM_TIME

echo ""
echo "--- Group B: Moore Neighbourhood Experiments ---"
echo "Running chessVariantKernel1_glider..."
$EXECUTABLE config/chessVariantKernel1_glider.json $SIM_TIME

echo "Running chessVariantKernel1_line..."
$EXECUTABLE config/chessVariantKernel1_line.json $SIM_TIME

echo "Running chessVariantKernel1_noWrap..."
$EXECUTABLE config/chessVariantKernel1_noWrap.json $SIM_TIME

echo "Running chessVariantKernel1_large..."
$EXECUTABLE config/chessVariantKernel1_large.json $SIM_TIME

echo ""
echo "--- Group C: Chess-Piece Neighbourhood Extensions ---"
echo "Running bishopNeighborhood_8x8..."
$EXECUTABLE config/bishopNeighborhood_8x8.json $SIM_TIME

echo "Running bishopNeighborhood_9x13..."
$EXECUTABLE config/bishopNeighborhood_9x13.json $SIM_TIME

echo "Running rookNeighborhood_8x8..."
$EXECUTABLE config/rookNeighborhood_8x8.json $SIM_TIME

echo "Running knightNeighborhood_8x8..."
$EXECUTABLE config/knightNeighborhood_8x8.json $SIM_TIME

echo "Running knightNeighborhood_9x13..."
$EXECUTABLE config/knightNeighborhood_9x13.json $SIM_TIME

echo "Running multiPiece_8x8..."
$EXECUTABLE config/multiPiece_8x8.json $SIM_TIME

echo ""
echo "=== All scenarios completed ==="
echo "Output files in logs/:"
ls -la logs/*.csv 2>/dev/null || echo "No CSV files found"
