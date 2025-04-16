#ifndef MOVESTATUS_H
#define MOVESTATUS_H
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif

/**
 * @file
 *
 * @brief The header containing the @ref MoveStatus
 * @author Felix Fehlauer
 */

/**
 * @enum MoveStatus
 *
 * @brief The status code for replying to a move network message
 *
 * This describes whether the action was ok, what happens next or which error occured
 * @var MoveStatus::PlayerChange
 * they action was ok, the turn ends
 * @var MoveStatus::Wait
 * the action was ok, waiting for opponent to remove a piece
 * @var MoveStatus::OpponentWin
 * the action was ok, the oppenent wins, the game is over
 * @var MoveStatus::NoPiece
 * invalid action, no own piece in the mentioned start position
 * @var MoveStatus::Occupied
 * invalid action, the mention end position is already occupied
 * @var MoveStatus::InvalidMove
 * invalid action, the player is not allowed to move to that position
 * @var MoveStatus::WrongTurn
 * invalid action, it is not the player's turn
 */
enum class MoveStatus : quint8 { PlayerChange=0x00, Wait=0x01, OpponentWin=0x02, NoPiece=0x10, Occupied=0x11, InvalidMove=0x12, WrongTurn=0x13 };

#endif // MOVESTATUS_H
