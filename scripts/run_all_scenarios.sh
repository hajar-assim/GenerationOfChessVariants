#!/bin/bash
# runs all chess variant scenarios
# output csvs go to simulation_results/

EXE="bin/chess_variant"
SIM_TIME=60

if [ ! -f "$EXE" ]; then
    echo "ERROR: Executable not found at $EXE"
    echo "Please build first:  bash build_sim.sh"
    exit 1
fi

echo "============================================"
echo " Chess Variant Cell-DEVS — Running all scenarios"
echo "============================================"

for CONFIG in config/chessVariantKernel1.json \
              config/chessVariantKernel2.json \
              config/chessVariantKernel1SmallGrid.json \
              config/chessVariantKernel2SmallGrid.json \
              config/chessVariantKernel1_glider.json \
              config/chessVariantKernel1_line.json \
              config/chessVariantKernel1_noWrap.json \
              config/chessVariantKernel1_large.json \
              config/knightNeighborhood_8x8.json \
              config/bishopNeighborhood_8x8.json \
              config/rookNeighborhood_8x8.json \
              config/knightNeighborhood_9x13.json \
              config/bishopNeighborhood_9x13.json \
              config/multiPiece_8x8.json; do
    NAME=$(basename "$CONFIG" .json)
    echo ""
    echo "--- Running: $NAME (sim time = $SIM_TIME) ---"
    "$EXE" "$CONFIG" "$SIM_TIME"
    echo "--- Finished: $NAME ---"
done

echo ""
echo "============================================"
echo " All scenarios complete. Results in simulation_results/"
echo "============================================"
