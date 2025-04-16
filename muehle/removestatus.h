#ifndef REMOVESTATUS_H
#define REMOVESTATUS_H
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif

/**
 * @file
 *
 * @brief The header containing the @ref RemoveStatus
 * @author Felix Fehlauer
 */

/**
 * @enum RemoveStatus
 *
 * @brief The status code for replying to a remove network message
 *
 * This describes whether the action was ok, what happens next or which error occured
 * @var RemoveStatus::PlayerChange
 * they action was ok, the turn ends
 * @var RemoveStatus::OpponentWin
 * the action was ok, the oppenent wins, the game is over
 * @var RemoveStatus::PartOfMuehle
 * invalid action, one cannot remove the piece as it is part of a Mühle
 * @var RemoveStatus::NoPiece
 * invalid action, there is no matching piece at the mentioned position
 * @var RemoveStatus::NoMuehle
 * invalid action, the player is not allowed to remove a piece
 */
enum class RemoveStatus : quint8 { PlayerChange=0x00, OpponentWin=0x01, PartOfMuehle=0x10, NoPiece=0x11, NoMuehle=0x12 };

#endif // REMOVESTATUS_H
