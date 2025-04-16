#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @file
 *
 * @brief The header containing the @ref GameState
 * @author Felix Fehlauer
 */

/**
 * @enum GameState
 *
 * @brief The state of the game
 *
 * This describes which action the user currently has to take
 * @var GameState::Opponent
 * no action necessary, it's the opponents turn
 * @var GameState::Set
 * the user has to set one of his pieces on a free position
 * @var GameState::Move
 * the user has to move on of his pieces to a free neighboring position
 * @var GameState::Jump
 * the user has to move on of his pieces to a arbitrary free position
 * @var GameState::Remove
 * the user has to remove an opponent's piece
 * @var GameState::Win
 * the user has won the game
 * @var GameState::Loose
 * the user has lost the game
 * @var GameState::Wait
 * the user has to wait until a client has connected
 */
enum class GameState { Opponent, Set, Move, Jump, Remove, Win, Loose, Wait };

#endif // GAMESTATE_H
