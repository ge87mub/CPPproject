#ifndef WAITCORNFIRM_H
#define WAITCORNFIRM_H

/**
 * @file
 *
 * @brief The header containing the possible actions awaiting confirmation
 * @author Felix Fehlauer
 */

/**
 * @enum WaitConfirm
 *
 * @brief The action awaiting confirmation
 *
 * This describes which kind of action the user just did and we are now awaiting confirmation for from the network
 * @var WaitConfirm::None
 * not waiting for a confirmation
 * @var WaitConfirm::GameStart
 * waiting for confirmation of the game start
 * @var WaitConfirm::Set
 * waiting for confirmation after setting a piece
 * @var WaitConfirm::Move
 * waiting for confirmation after moving a piece
 * @var WaitConfirm::Jump
 * waiting for confirmation after jumping with a piece
 * @var WaitConfirm::Remove
 * waiting for confirmation after removing an opponent's piece
 */
enum class WaitConfirm { None, GameStart, Set, Move, Jump, Remove };

#endif // WAITCORNFIRM_H
