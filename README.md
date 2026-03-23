# Generation of Chess Variants — Cell-DEVS Model

**Authors:** Hajar Assim 101232456, Hasib Khodayar 101225523

**Course:** SYSC 5104/4906G - Methodologies for Discrete Event Modelling and Simulation

**Instructor:** Dr. Gabriel Wainer

**Due Date:** March 24, 2026

---

## Introduction

This repository contains a Cell-DEVS implementation of the **Generation of Chess Variants**
cellular automaton model, re-implemented in Cadmium v2 for SYSC 5104 Assignment 2.

The model is a variant of Conway's Game of Life using rule **B23/S23** (a cell is alive if
exactly 2 or 3 of its neighbours are alive) applied to a 2D grid. Starting from small seed
configurations, the automaton produces chess-like spatial patterns.

As a two-person team submission, the model extends the original four baseline scenarios
with ten additional configurations: four varying initial conditions and boundary settings
under the standard Moore neighbourhood, and six substituting chess-piece movement patterns
(bishop, rook, knight, multi-piece) as the cell neighbourhood topology.

The full report is available in [`docs/ChessVariants_Report.pdf`](docs/ChessVariants_Report.pdf).

---

## Repository Structure

```
.
├── main/                   # C++ source code (chessVariantCell.hpp, chessVariantState.hpp, main.cpp)
├── config/                 # JSON scenario configuration files (14 scenarios)
├── scripts/                # Shell scripts to run each scenario
├── logs/                   # Simulation output CSV logs (14 files)
├── docs/                   # Report PDF and screenshots
├── videos/                 # Simulation visualization videos
├── CMakeLists.txt          # Top-level CMake configuration
├── build_sim.sh            # Build script
└── README.md               # This file
```

---

## Dependencies

This project is designed to run on a **Linux-based environment (e.g., Ubuntu)** and
requires **Cadmium v2** to be installed and accessible via the `$CADMIUM` environment variable.

This dependency is typically met by default on the DEVSsim servers.

To verify your Cadmium installation:

```bash
echo $CADMIUM
```

If the variable is empty, set it manually:

```bash
export CADMIUM=/path/to/cadmium_v2/include/cadmium
```

---

## Cloning the Repository

```bash
git clone https://github.com/[YOUR_USERNAME]/chess-variants-cell-devs.git
cd chess-variants-cell-devs
```

---

## Building the Project

```bash
bash build_sim.sh
```

This produces the executable at `bin/chess_variant`.

---

## Running Simulations

### Run a single scenario

```bash
./bin/chess_variant config/<scenario_name>.json <simulation_time>
```

Example — run Kernel 1 for 60 generations:

```bash
./bin/chess_variant config/chessVariantKernel1.json 60
```

Output CSV is written to `logs/<scenario_name>_output.csv`.

### Run all 14 scenarios at once

```bash
bash scripts/run_all_scenarios.sh
```

---

## Scenarios

### Group A — Baseline (Original CD++ Model)

| Scenario | Config File | Grid | Seed |
|----------|-------------|------|------|
| Kernel 1 | `chessVariantKernel1.json` | 9×13, wrapped | Plus shape (5 cells) |
| Kernel 2 | `chessVariantKernel2.json` | 9×13, wrapped | Asymmetric cluster (7 cells) |
| Kernel 1 Small Grid | `chessVariantKernel1SmallGrid.json` | 7×7, wrapped | Plus centred (5 cells) |
| Kernel 2 Small Grid | `chessVariantKernel2SmallGrid.json` | 5×9, wrapped | Asymmetric (7 cells) |

### Group B — Moore Neighbourhood Experiments

| Scenario | Config File | Grid | Description |
|----------|-------------|------|-------------|
| Glider Seed | `chessVariantKernel1_glider.json` | 9×13, wrapped | Classic Game of Life glider seed |
| Horizontal Line | `chessVariantKernel1_line.json` | 9×13, wrapped | 7-cell horizontal line seed |
| No-Wrap Boundary | `chessVariantKernel1_noWrap.json` | 9×13, **not** wrapped | Fixed boundary comparison |
| Large Grid | `chessVariantKernel1_large.json` | 20×20, wrapped | Unconstrained free expansion |

### Group C — Chess-Piece Neighbourhood Extensions

| Scenario | Config File | Grid | Neighbourhood |
|----------|-------------|------|---------------|
| Bishop 8×8 | `bishopNeighborhood_8x8.json` | 8×8, not wrapped | Full diagonal movement |
| Bishop 9×13 | `bishopNeighborhood_9x13.json` | 9×13, wrapped | Full diagonal movement |
| Rook 8×8 | `rookNeighborhood_8x8.json` | 8×8, not wrapped | Full orthogonal movement |
| Knight 8×8 | `knightNeighborhood_8x8.json` | 8×8, not wrapped | L-shaped knight moves |
| Knight 9×13 | `knightNeighborhood_9x13.json` | 9×13, wrapped | L-shaped knight moves |
| Multi-piece 8×8 | `multiPiece_8x8.json` | 8×8, not wrapped | Knight default + bishop zones |

---

## Visualizing Results

Upload the output CSV from `logs/` along with the corresponding JSON config from `config/`
to the Cell-DEVS Web Viewer:

**https://devssim.carleton.ca/cell-devs-viewer/**

Cells coloured **black** = alive (state 1). Cells coloured **white** = dead (state 0).

Video recordings of selected scenarios are available in the `videos/` folder.

---

## Key Findings

The B23/S23 rule is calibrated for neighbourhoods of approximately 8 cells:

- **Moore neighbourhood (η=9):** Sustained active patterns across all 60 generations
- **Knight neighbourhood (η=9):** Sustained patterns on wrapped grid; stable fixed point on 8×8
- **Bishop neighbourhood (η≤29):** Near-extinction; collapses to 4 corner cells (8×8) or 2 cells (9×13)
- **Rook neighbourhood (η=29):** Complete extinction by generation 2

Early simulation halting for bishop and rook scenarios is **correct Cell-DEVS behaviour** —
Cadmium stops generating events once all cells reach a globally quiescent (passive) state.

---

## Reference

Wainer, G. (n.d.). *Generation of Chess Variants*. Cell-DEVS Model Samples,
Carleton University. Retrieved March 2026 from
https://www.sce.carleton.ca/faculty/wainer/wbgraf/doku.php?id=model_samples:start
