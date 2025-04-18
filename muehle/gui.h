#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QWidget>
#include "orientation.h"
#include "square.h"
#include "positionstate.h"
#include "gamestate.h"
#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif
#include <QHash>
#include <QPair>
#include "server.h"
#include "game.h"
#include "client.h"

namespace Ui {
class gui;
}

/**
 * @class gui
 * @brief GUI encompasses the Game menu, Server finder and Game
 */
class gui : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the gui class.
     * @param parent Parent widget pointer.
     */
    explicit gui(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the gui class.
     */
    ~gui();

private slots:
    /**
     * @brief Updates the visual state of a game board cell.
     */
    void setCellState(Orientation heading, Square distance, PositionState state); //Receives an order to change a Cellstate (Player A,B unset)
    /**
     * @brief Updates the status message in the UI based on the game state.
     */
    void updateStatus(GameState state); // receives a Game state (Win lose move set opponent)
    /**
     * @brief Displays error messages related to the game.
     */
    void setErrorGame(QString error);
    /**
     * @brief Displays error messages related to server creation.
     */
    void setErrorServer(QString error);
    /**
     * @brief Sets the success flag after successful connection/creation.
     */
    void success();
    /**
     * @brief Handles errors encountered by the client.
     */
    void handleClientError(QString error); //Client side error, disables join game in FindAServer
    /**
     * @brief Initiates server creation process.
     */
    void on_start_btn_clicked(); //hosts game as server (opens Create a server popup)
    /**
     * @brief Opens the server finder view.
     */
    void on_server_btn_clicked(); //open server finder
    /**
     * @brief Exits the application.
     */
    void on_exit_btn_clicked(); //exits game
    /**
     * @brief Handles mid-game exit with confirmation dialog.
     */
    void on_exit_btn_midgame_clicked(); //exits game midgame

    /**
     * @brief Returns to main menu from server creation view.
     */
    void on_return_btn_servercreator_clicked();
    /**
     * @brief Returns to main menu from the game view.
     */
    void on_return_btn_game_clicked(); //returns to menu during game
    /**
     * @brief Returns to main menu from the client/server finder view.
     */
    void on_return_btn_client_clicked(); //returns to menu from server finder
    /**
     * @brief Initiates client connection process to join a game.
     */
    void on_connectBtn_clicked(); // join a game as a client
    /**
     * @brief UDP TCP chooser.
     */
    void on_comboBox_activated(int index);

signals:
    /**
     * @brief Emitted when the user clicks a game board cell.
     * @param heading Orientation of the cell.
     * @param distance Square type (outer/middle/inner).
     * @param state Current state of the cell.
     */
    void buttonClicked(Orientation heading, Square distance, PositionState state); //when the user clicks a position on the playing field
    /**
     * @brief Emitted to request starting a server.
     * @param port Port number to start the server on.
     */
    void startServerRequested(quint16 port); //To create a server with port
    /**
     * @brief Emitted to request joining a server.
     * @param host Host address of the server.
     * @param port Port of the server.
     */
    void joinServerRequested(const QString &host, quint16 port); // to notify network stack to try to connect to server
    /**
     * @brief Emitted to request disconnecting from a server. currently unused placeholder for future updates
     */
    void disconnectRequested(); //Signal to disconnect
    /**
     * @brief Placeholder
     */
    void endRequested(const QString &host, quint16 port); //Place holder
    /**
     * @brief Emitted when the user selects who starts the game in the dropdown menu, default is server.
     * @param startindex Index of the starting player.
     */
    void whostarts(quint8 startindex);//who should start the game (dropdown in serverdialog)
    /**
     * @brief signal for udp discovery
     * @param port Port of the server.
     */
    void connectViaUdpSignal(quint16 port); //signal for udp discovery

private slots:



private:
    /**
     * @brief UI pointer generated by Qt Designer.
     */
    Ui::gui *ui;
    /**
     * @brief Converts an Orientation enum to string.
     */
    QString orientationToString(Orientation o) const; //Orientation to string helper
    /**
     * @brief Converts a Square enum to string.
     */
    QString squareToString(Square s) const; //Square to string helper
    /**
     * @brief Stores the state of each board cell.
     */
    QHash<QPair<Orientation, Square>, PositionState> cellStates; //cellStates stores the color of each button in a map
    /**
     * @brief Pointer to the server instance.
     */
    server* srv1;
    /**
     * @brief Pointer to the game logic instance.
     */
    Game* logicPtr;
    /**
     * @brief Pointer to the client instance.
     */
    client* player;
    /**
     * @brief Error message from server operations.
     */
    QString m_serverError;
    /**
     * @brief Error message from client operations.
     */
    QString m_clientError;
    /**
     * @brief Indicates if the last action (connection, etc.) was successful.
     */
    bool suc = false;
    /**
     * @brief UDP discovery activation bool
     */
    bool udpDiscoveryActivated;
};

#endif // GUI_H
