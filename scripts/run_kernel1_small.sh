#!/bin/bash
# run kernel 1 on 7x7 grid with plus seed
SIM_TIME="${1:-60}"
./bin/chess_variant config/chessVariantKernel1SmallGrid.json "$SIM_TIME"
