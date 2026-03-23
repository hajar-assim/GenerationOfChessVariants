# Generation of Chess Variants — Cell-DEVS Model

**Authors:** Hajar Assim 101232456, Hasib Khodayar 101225523

**Course:** SYSC 5104/4906G - Methodologies for Discrete Event Modelling and Simulation

**Instructor:** Dr. Gabriel Wainer

**Due Date:** March 24, 2026

---

## Introduction

This repository presents a Cell-DEVS model that simulates the Generation of Chess Variants cellular automaton, re-implemented in Cadmium v2.

The model is based on the original CD++ implementation by Mikael Fridenfalk (Uppsala University), which uses a modified Game of Life rule: a cell is set to 1 if it has exactly 2 or 3 neighbours, otherwise it is set to 0. This high-reproduction rule, combined with small modular grids, generates patterns suitable for chess variant board configurations.

The system extends the original four baseline scenarios with ten additional configurations exploring different initial conditions, boundary settings, and chess-piece movement patterns (bishop, rook, knight) as alternative neighbourhood topologies.

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

## Prerequisites

- **C++17 compatible compiler** (g++ 8+ recommended)
- **Cadmium v2 framework**
- **Linux-based environment** (e.g., Ubuntu) or compatible system

---

## Setup

### Clone this repository

```bash
git clone https://github.com/hajar-assim/GenerationOfChessVariants.git
cd GenerationOfChessVariants
```

### Clone Cadmium v2 (if not already installed)

Target the `dev-rt` branch:

```bash
cd ~
git clone https://github.com/SimulationEverywhere/cadmium_v2 -b dev-rt
```

### Configure Cadmium Path

The build script defaults to `~/cadmium_v2`. If your Cadmium is installed elsewhere, set the `CADMIUM_HOME` environment variable:

```bash
export CADMIUM_HOME=/path/to/your/cadmium_v2
```

Or edit the makefile/build script directly:

```
CADMIUM_HOME ?= /your/custom/path
```

**Note:** On the DEVSsim servers, Cadmium v2 is typically pre-installed and accessible via the `$CADMIUM` environment variable.

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

The 2-3 neighbour rule is calibrated for neighbourhoods of approximately 8 cells:

- **Moore neighbourhood (8 neighbours):** Sustained active patterns across all 60 generations
- **Knight neighbourhood (8 neighbours):** Sustained patterns on wrapped grid; stable fixed point on 8×8
- **Bishop neighbourhood (up to 28 neighbours):** Rapid extinction due to oversaturation
- **Rook neighbourhood (up to 28 neighbours):** Complete extinction by generation 2

Early simulation halting for bishop and rook scenarios is **correct Cell-DEVS behaviour** —
Cadmium stops generating events once all cells reach a globally quiescent (passive) state.

---

## Reference

Fridenfalk, M. (2013). Application of Cellular Automata for Generation of Chess Variants.
*Uppsala University, Department of Game Design*. CD++ model available at
https://www.sce.carleton.ca/faculty/wainer/wbgraf/doku.php?id=model_samples:start
