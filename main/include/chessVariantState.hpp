#ifndef CHESS_VARIANT_STATE_HPP
#define CHESS_VARIANT_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

/**
 * @brief State structure for the Chess Variant Cell-DEVS model.
 *
 * Each cell has a binary state: alive (1) or dead (0).
 * This implements the B23/S23 rule (similar to Conway's Game of Life).
 */
struct ChessVariantState {
    int state;  // 0 = dead, 1 = alive

    ChessVariantState() : state(0) {}
    explicit ChessVariantState(int s) : state(s) {}
};

/**
 * @brief Equality operator for state comparison.
 * Used by Cadmium to detect state changes.
 */
inline bool operator==(const ChessVariantState& lhs, const ChessVariantState& rhs) {
    return lhs.state == rhs.state;
}

/**
 * @brief Inequality operator for state comparison.
 */
inline bool operator!=(const ChessVariantState& lhs, const ChessVariantState& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Output stream operator for logging.
 */
inline std::ostream& operator<<(std::ostream& os, const ChessVariantState& s) {
    os << s.state;
    return os;
}

/**
 * @brief JSON serialization for Cadmium configuration.
 */
inline void from_json(const nlohmann::json& j, ChessVariantState& s) {
    s.state = j.at("state").get<int>();
}

/**
 * @brief JSON deserialization for output logging.
 */
inline void to_json(nlohmann::json& j, const ChessVariantState& s) {
    j = nlohmann::json{{"state", s.state}};
}

#endif // CHESS_VARIANT_STATE_HPP
