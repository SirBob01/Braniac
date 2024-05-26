#pragma once

#include <chrono>

#include "Evaluation.hpp"
#include "History.hpp"
#include "Numeric.hpp"
#include "Position.hpp"
#include "Transpositions.hpp"
#include "Utils.hpp"

namespace Brainiac {
    /**
     * @brief Search result.
     *
     */
    struct Result {
        /**
         * @brief Best move found.
         *
         */
        Move move;

        /**
         * @brief Total search time.
         *
         */
        Seconds time;

        /**
         * @brief Number of nodes visited.
         *
         */
        unsigned visited;
    };

    /**
     * @brief Search engine.
     *
     */
    class Search {
        Position &_position;

        Transpositions _tptable;
        History _htable;

        Seconds _start_time;
        unsigned _visited;

        /**
         * @brief Static exchange evaluation on a target square.
         *
         * @param target
         * @param pos
         * @return Value
         */
        Value see_target(Square target);

        /**
         * @brief Evaluate a capture move.
         *
         * @param move
         * @param pos
         * @return MoveValue
         */
        MoveValue evaluate_capture(Move move);

        /**
         * @brief Compute the move value for ordering
         *
         * @param move
         * @param node
         * @return MoveValue
         */
        MoveValue evaluate_move(Move move, Node node);

        /**
         * @brief Check if a move can be reduced.
         *
         * @param move
         * @param value
         * @return true
         * @return false
         */
        bool can_reduce_move(Move move, MoveValue value);

        /**
         * @brief Recursive negamax algorithm.
         *
         * @param depth
         * @param alpha
         * @param beta
         * @return Value
         */
        Value
        negamax(Depth depth, Value alpha = MIN_VALUE, Value beta = MAX_VALUE);

      public:
        /**
         * @brief Construct a new Search object.
         *
         * @param position
         */
        Search(Position &position) : _position(position){};

        /**
         * @brief Calculate the next viable move for the current turn.
         *
         * @return Result
         */
        Result search();
    };
} // namespace Brainiac