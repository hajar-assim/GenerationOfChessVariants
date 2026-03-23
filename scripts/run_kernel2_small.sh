#!/bin/bash
# run kernel 2 on 5x9 grid with asymmetric seed
SIM_TIME="${1:-60}"
./bin/chess_variant config/chessVariantKernel2SmallGrid.json "$SIM_TIME"
