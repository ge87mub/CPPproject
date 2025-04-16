#ifndef POSITIONSTATE_H
#define POSITIONSTATE_H

/**
 * @file
 *
 * @brief The header containing the @ref PositionState
 * @author Felix Fehlauer
 */

/**
 * @enum PositionState
 *
 * @brief The state of a position on the board
 *
 * This describes whether there is no piece or all or who ows the piece present
 * @var PositionState::Unset
 * there is no piece
 * @var PositionState::PlayerA
 * there is a piece of the starting player
 * @var PositionState::PlayerB
 * there is a piece of the second player
 */
enum class PositionState { Unset, PlayerA, PlayerB };

#endif // POSITIONSTATE_H
