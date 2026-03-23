#ifndef CHESS_VARIANT_CELL_HPP
#define CHESS_VARIANT_CELL_HPP

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/celldevs/core/cell.hpp>
#include "chessVariantState.hpp"

/**
 * @brief Chess Variant Cell-DEVS cell implementing Fridenfalk's rule.
 *
 * Rule: A cell is set to 1 if it has exactly 2 or 3 live neighbors, else 0.
 * This rule applies regardless of the cell's current state, resulting in
 * higher reproduction rates than Conway's Game of Life.
 *
 * The neighborhood can be configured via JSON (Moore, Bishop, Rook, Knight, etc.)
 */
template<typename T>
class ChessVariantCell : public cadmium::celldevs::Cell<T, ChessVariantState> {
public:
    using cadmium::celldevs::Cell<T, ChessVariantState>::Cell;

    /**
     * @brief Local computation function implementing Fridenfalk's transition rule.
     *
     * @param state Current state of the cell
     * @return New state after applying the transition rule
     */
    [[nodiscard]] ChessVariantState localComputation(ChessVariantState state) const override {
        // Count live neighbors (excluding self)
        int aliveNeighbors = 0;

        for (const auto& [neighborId, neighborState] : this->neighbors) {
            // Skip self (neighbor at relative position (0,0,...))
            bool isSelf = true;
            for (const auto& coord : neighborId) {
                if (coord != 0) {
                    isSelf = false;
                    break;
                }
            }
            if (isSelf) {
                continue;
            }

            // Count if neighbor is alive
            if (neighborState.state == 1) {
                aliveNeighbors++;
            }
        }

        // Apply Fridenfalk's rule: cell is alive if exactly 2 or 3 neighbors
        ChessVariantState newState;
        newState.state = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0;

        return newState;
    }

    /**
     * @brief Output delay function.
     *
     * @param state Current state of the cell
     * @return Time until next state transition (1 time unit)
     */
    [[nodiscard]] double outputDelay(const ChessVariantState& state) const override {
        return 1.0;
    }
};

#endif // CHESS_VARIANT_CELL_HPP
