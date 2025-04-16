#ifndef GAME_H
#define GAME_H
#include <QObject>
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif
#include <QHash>
#include "orientation.h"
#include "square.h"
#include "positionstate.h"
#include <QMultiHash>
#include "movestatus.h"
#include "removestatus.h"
#include "gamestate.h"
#include "waitcornfirm.h"

/**
 * @file
 *
 * @brief The header containing the @ref Game logic class
 * @author Felix Fehlauer
 */

/**
 * @class Game
 *
 * @brief The Game class contains all the game logic
 */
class Game : public QObject
{
    Q_OBJECT

public:
    Game();

private:
    quint8 remainingSetMe = 9;
    quint8 remainingSetRemote = 9;
    quint8 removedByMe = 0;
    quint8 removedByRemote = 0;
    QHash<QPair<Orientation,Square>, PositionState> pieces;
    QMultiHash<QPair<Orientation,Square>,QPair<Orientation,Square>> validMoves;
    bool myMove;
    PositionState myPlayer;
    PositionState remotePlayer;
    bool muehle = false;
    bool muehleRemote = false;
    bool confirmMuehle(QPair<Orientation,Square> pos);
    void playerChange();
    bool canMove();
    void doRemove(QPair<Orientation,Square> pos);
    QPair<Orientation,Square> getNew(Orientation oldH, Square oldQ, Orientation moveOrientation);
    GameState gameState = GameState::Wait;
    QPair<Orientation,Square> selected;
    bool userSelected = false;
    WaitConfirm waitConfirm = WaitConfirm::None;
    Orientation getMove(Orientation oldH, Square oldQ, Orientation newH, Square newQ);
    quint8 startPlayer;
    bool network = true;
    void initializeBoard();

signals:
    /**
     * @brief Emitted to confirm a game start from the remote application
     * @param groupNo the group number of the current application
     */
    void confirmGame(quint8 groupNo);
    /**
     * @brief Emitted to confirm a set, move or jump action from the remote player
     * @param statusCode the @ref MoveStatus representing success or failure
     */
    void confirmMove(MoveStatus statusCode);
    /**
     * @brief Emitted to confirm a piece removal of the remote player
     * @param statusCode the @ref RemoveStatus representing success or failure
     * @param count the number of removed pieces
     */
    void confirmRemove(RemoveStatus statusCode, quint8 count);
    /**
     * @brief Emitted to set or remove a piece in the GUI
     * @param h the orientation of the position on the board to be edited
     * @param q the square of which the position on the board to be edited is part of
     * @param state the @ref PositionState in which the position shall now be in
     */
    void setGUI(Orientation h, Square q, PositionState state);
    /**
     * @brief Emitted to confirm an action of the user in the GUI or notify the user
     * @param error the message to be shown to the user
     */
    void confirm(QString error);
    /**
     * @brief Emitted to notify the GUI of a @ref GameState change
     * @param state the new game state
     */
    void stateChange(GameState state);
    /**
     * @brief Emitted to notify the network stack to send the game start message
     *
     * This is only send from the server to the client.
     * @param startPlayer which player has the first turn
     * @param groupNo the group number of the server
     */
    void sendStartGame(quint8 startPlayer, quint8 groupNo);
    /**
     * @brief Emitted to notify the network stack to send the message for setting a piece
     * @param newH the orientation of the position where the piece was set
     * @param newQ the square of the position where the piece was set
     * @param remaining the number of pieces remaining to set
     * @param muehle whether a Mühle was closed
     */
    void sendSet(Orientation newH, Square newQ, quint8 remaining, bool muehle);
    /**
     * @brief Emitted to notify the network stack to send the message for moving a piece
     * @param oldH the orientation of the position of the piece moved
     * @param oldQ the square of the position of the piece moved
     * @param newH the orientation of the position where the piece was moved to
     * @param muehle whether a Mühle was closed
     */
    void sendMove(Orientation oldH, Square oldQ, Orientation newH, bool muehle);
    /**
     * @brief Emitted to notify the network stack to send the message for jumping with a piece
     * @param oldH the orientation of the position of piece before the jump
     * @param oldQ the square of the position of the piece before the jump
     * @param newH the orientation of the position of piece after the jump
     * @param newQ the square of the position of the piece after the jump
     * @param muehle whether a Mühle was closed
     */
    void sendJump(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle);
    /**
     * @brief Emitted to notify the network stack to send the message for removing a piece
     * @param oldH the orientation of the position of the removed piece
     * @param oldQ the square of the position of the removed piece
     */
    void sendRemove(Orientation oldH, Square oldQ);
    /**
     * @brief Emitted to notify the GUI of how many pieces the user can still set
     * @param newValue the number of remaining pieces
     */
    void piecesToSetMeChanged(quint8 newValue);
    /**
     * @brief Emitted to notify the GUI of how many pieces the opponent can still set
     * @param newValue the number of remaining pieces
     */
    void piecesToSetRemoteChanged(quint8 newValue);
    /**
     * @brief Emitted to notify the GUI how many pieces of the opponent where removed
     * @param newValue the number of removed pieces
     */
    void piecesRemovedByMeChanged(quint8 newValue);
    /**
     * @brief Emitted to notify the GUI how many pieces of the user where removed
     * @param newValue the number of removed pieces
     */
    void piecesRemovedByRemoteChanged(quint8 newValue);

public slots:
    /**
     * @brief Handle message that a game start was requested
     * @param startPlayer the player that has the first turn
     * @param groupNo the group number of the server
     */
    void startGame(quint8 startPlayer, quint8 groupNo);
    /**
     * @brief Handle a message that the opponent set a piece
     * @param newH the orientation of the position where the piece was set
     * @param newQ the square of the position where the piece was set
     * @param remaining the number of pieces remaining to set
     * @param muehle whether a Mühle was closed
     */
    void set(Orientation newH, Square newQ, quint8 remaining, bool muehle);
    /**
     * @brief Handle a message that the opponent moved a piece
     * @param oldH the orientation of the position of the piece moved
     * @param oldQ the square of the position of the piece moved
     * @param newH the orientation of the position where the piece was moved to
     * @param muehle whether a Mühle was closed
     */
    void move(Orientation oldH, Square oldQ, Orientation newH, bool muehle);
    /**
     * @brief Handle a message that the opponent jumped with a piece
     * @param oldH the orientation of the position of piece before the jump
     * @param oldQ the square of the position of the piece before the jump
     * @param newH the orientation of the position of piece after the jump
     * @param newQ the square of the position of the piece after the jump
     * @param muehle whether a Mühle was closed
     */
    void jump(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle);
    /**
     * @brief Handle a message that the opponent removed a piece
     * @param oldH the orientation of the position of the removed piece
     * @param oldQ the square of the position of the removed piece
     */
    void remove(Orientation oldH, Square oldQ);
    /**
     * @brief Handle a board position/piece button click from GUI
     * @param h the orientation of the clicked position
     * @param q the square of the clicked position
     * @param state the state the button is in
     */
    void buttonClicked(Orientation h, Square q, PositionState state);
    /**
     * @brief Handle a confirmation message from the network for starting a game
     * @param groupNo the group number
     */
    void handleConfirmGame(quint8 groupNo);
    /**
     * @brief Handle a confirmation message from the network for a move
     * @param statusCode the status code
     */
    void handleConfirmMove(MoveStatus statusCode);
    /**
     * @brief Handle a confirmation message from the network for a piece removal
     * @param statusCode the status code
     * @param count the number of pieces that where removed by the recieving player
     */
    void handleConfirmRemove(RemoveStatus statusCode, quint8 count);
    /**
     * @brief Handle a connection request message from the network
     */
    void handleConnectionRequest();
    /**
     * @brief Save what the user of the server has input who shall start
     * @param startingPlayer the starting player
     */
    void saveWhoStarts(quint8 startingPlayer);
    /**
     * @brief Handle a loss of network connnection
     */
    void handleNetworkLoss();
    /**
     * @brief Reset the game as if the program was just started
     */
    void resetGame();
    /**
     * @brief Handle the restore of a network connection
     */
    void handleNetworkRestore();
};

#endif // GAME_H
