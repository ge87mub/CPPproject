#include "gui.h"
#include "ui_gui.h"

#include <QPushButton>
#include "position.h"
#include <QApplication>
#include "disconnectdialog.h"
#include <QDialog>
#include "serverdialog.h"
#include <QTimer>
#include <QIntValidator>

/**
 * @file
 *
 * @brief
 * @author Shihang Li
 */
gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    logicPtr = new Game();

    srv1 = new server();

    player = new client();

    //game specific connects
    connect(logicPtr, &Game::stateChange, this, &gui::updateStatus);//Game to UI

    connect(logicPtr, &Game::confirm, this, &gui::setErrorGame);//Game to UI

    connect(logicPtr, &Game::setGUI, this, &gui::setCellState);//Game to UI

    connect(this, &gui::buttonClicked, logicPtr, &Game::buttonClicked);//Ui to Game

    connect(this, &gui::whostarts, logicPtr, &Game::saveWhoStarts);

    connect(this, &gui::disconnectRequested, logicPtr, &Game::resetGame);

    //client specific connects
    connect(this, &gui::joinServerRequested, player, &client::on_connectButton_clicked); //UI ask to join server
    connect(this, &gui::connectViaUdpSignal, player, &client::udpBroadcast); //NEW for udp discovery
    connect(this, &gui::disconnectRequested, player, &client::stopClient); //STOP SIGNAL
    connect(logicPtr, &Game::confirmGame, player, &client::confirmGameSlot);

    connect(player, &client::startGameSignal, logicPtr, &Game::startGame);
    connect(player, &client::socketErrorOccurred, this, &gui::handleClientError); // Display client side error
    connect(player, &client::clientConnected, this, &gui::success);
    connect(player, &client::clientConnected, logicPtr, &Game::handleNetworkRestore);
    connect(player, &client::serverDisconnected, logicPtr, &Game::handleNetworkLoss);

    //server specific connects
    connect(srv1, &server::serverErrorOccurred, this, &gui::setErrorServer);
    connect(this, &gui::startServerRequested, srv1, &server::startServer); //Ui ask to start server
    connect(this, &gui::disconnectRequested, srv1, &server::stopServer); //STOP SIGNAL
    connect(logicPtr, &Game::sendStartGame, srv1, &server::sendStartGameSlot);

    connect(srv1, &server::responseConnectionRequest, logicPtr, &Game::handleConnectionRequest);
    connect(srv1, &server::receivedStartGameConfirm, logicPtr, &Game::handleConfirmGame);
    connect(srv1, &server::clientDisconnected, logicPtr, &Game::handleNetworkLoss);
    connect(srv1, &server::serverStarted, logicPtr, &Game::handleNetworkRestore);
    connect(srv1, &server::serverStarted, this, &gui::success);

    //logic signals to networkManager slots
    //for server|client each on their own because they are used as seperate objects here
    connect(logicPtr, &Game::confirmMove, srv1, &server::confirmSetMoveJumpSlot);
    connect(logicPtr, &Game::confirmMove, player, &client::confirmSetMoveJumpSlot);

    connect(logicPtr, &Game::confirmRemove, srv1, &server::confirmRemoveSlot);
    connect(logicPtr, &Game::confirmRemove, player, &client::confirmRemoveSlot);

    connect(logicPtr, &Game::sendSet, srv1, &server::sendSetSlot);
    connect(logicPtr, &Game::sendSet, player, &client::sendSetSlot);

    connect(logicPtr, &Game::sendMove, srv1, &server::sendMoveSlot);
    connect(logicPtr, &Game::sendMove, player, &client::sendMoveSlot);

    connect(logicPtr, &Game::sendJump, srv1, &server::sendJumpSlot);
    connect(logicPtr, &Game::sendJump, player, &client::sendJumpSlot);

    connect(logicPtr, &Game::sendRemove, srv1, &server::sendRemoveSlot);
    connect(logicPtr, &Game::sendRemove, player, &client::sendRemoveSlot);

    //networkManager signals to logic slots
    //for server|client each on their own because they are used as seperate objects here
    connect(player, &client::setSignal, logicPtr, &Game::set);
    connect(srv1, &server::setSignal, logicPtr, &Game::set);

    connect(player, &client::moveSignal, logicPtr, &Game::move);
    connect(srv1, &server::moveSignal, logicPtr, &Game::move);

    connect(player, &client::jumpSignal, logicPtr, &Game::jump);
    connect(srv1, &server::jumpSignal, logicPtr, &Game::jump);

    connect(player, &client::removeSignal, logicPtr, &Game::remove);
    connect(srv1, &server::removeSignal, logicPtr, &Game::remove);

    connect(player, &client::confirmSetMoveJumpSignal, logicPtr, &Game::handleConfirmMove);
    connect(srv1, &server::confirmSetMoveJumpSignal, logicPtr, &Game::handleConfirmMove);

    connect(player, &client::confirmRemoveSignal, logicPtr, &Game::handleConfirmRemove);
    connect(srv1, &server::confirmRemoveSignal, logicPtr, &Game::handleConfirmRemove);

    auto playerClicked = [&](QPushButton* btn, Orientation o, Square sq) {
        connect(btn, &QPushButton::clicked, this, [this, o, sq]() {
            PositionState st = cellStates.value({o, sq}, PositionState::Unset);
            emit buttonClicked(o, sq, st);
        });
    };

    playerClicked(ui->btn_NW_Aussen, Orientation::Nordwest, Square::Aussen);
    playerClicked(ui->btn_NW_Mitte, Orientation::Nordwest, Square::Mitte);
    playerClicked(ui->btn_NW_Innen, Orientation::Nordwest, Square::Innen);

    playerClicked(ui->btn_N_Aussen, Orientation::Nord, Square::Aussen);
    playerClicked(ui->btn_N_Mitte, Orientation::Nord, Square::Mitte);
    playerClicked(ui->btn_N_Innen, Orientation::Nord, Square::Innen);

    playerClicked(ui->btn_NO_Aussen, Orientation::Nordost, Square::Aussen);
    playerClicked(ui->btn_NO_Mitte, Orientation::Nordost, Square::Mitte);
    playerClicked(ui->btn_NO_Innen, Orientation::Nordost, Square::Innen);

    playerClicked(ui->btn_O_Aussen, Orientation::Ost, Square::Aussen);
    playerClicked(ui->btn_O_Mitte, Orientation::Ost, Square::Mitte);
    playerClicked(ui->btn_O_Innen, Orientation::Ost, Square::Innen);

    playerClicked(ui->btn_SO_Aussen, Orientation::Suedost, Square::Aussen);
    playerClicked(ui->btn_SO_Mitte, Orientation::Suedost, Square::Mitte);
    playerClicked(ui->btn_SO_Innen, Orientation::Suedost, Square::Innen);

    playerClicked(ui->btn_S_Aussen, Orientation::Sued, Square::Aussen);
    playerClicked(ui->btn_S_Mitte, Orientation::Sued, Square::Mitte);
    playerClicked(ui->btn_S_Innen, Orientation::Sued, Square::Innen);

    playerClicked(ui->btn_SW_Aussen, Orientation::Suedwest, Square::Aussen);
    playerClicked(ui->btn_SW_Mitte, Orientation::Suedwest, Square::Mitte);
    playerClicked(ui->btn_SW_Innen, Orientation::Suedwest, Square::Innen);

    playerClicked(ui->btn_W_Aussen, Orientation::West, Square::Aussen);
    playerClicked(ui->btn_W_Mitte, Orientation::West, Square::Mitte);
    playerClicked(ui->btn_W_Innen, Orientation::West, Square::Innen);
}


gui::~gui()
{
    delete ui;
    delete player;
    delete srv1;
    delete logicPtr;
}

QString gui::orientationToString(Orientation o) const
{
    switch (o) {
    case Orientation::Nordwest: return "NW";
    case Orientation::Nord: return "N";
    case Orientation::Nordost: return "NO";
    case Orientation::Suedwest: return "SW";
    case Orientation::Sued: return "S";
    case Orientation::Suedost: return "SO";
    case Orientation::West: return "W";
    case Orientation::Ost: return "O";
    }
    return "";
}

QString gui::squareToString(Square s) const
{
    switch (s) {
    case Square::Aussen: return "Aussen";
    case Square::Mitte: return "Mitte";
    case Square::Innen: return "Innen";
    }
    return "";
}

void gui::on_exit_btn_clicked()
{
    QApplication::quit();
}

void gui::on_exit_btn_midgame_clicked()
{
    DisconnectDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        emit disconnectRequested();
        QApplication::quit();
    } else {
        return;
    }
}

void gui::on_server_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->c_errorLabel->clear();
    ui->portLineEdit->clear();
    ui->hostLineEdit->clear();
}

void gui::on_return_btn_game_clicked()
{
    DisconnectDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        emit disconnectRequested();
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        return;
    }
}

void gui::on_return_btn_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gui::on_start_btn_clicked()
{
    qint16 port;
    qint8 who;
    suc = false;
    m_serverError = "";
    ui->ServerStatus->setText("Creating Server ... ");

    ServerDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        port = dlg.port();
        who = dlg.whostarts();
        if (port != 0) {
            emit startServerRequested(port);
        } else {
           m_serverError = "Invalid Port number!";
        }
        ui->stackedWidget->setCurrentIndex(3);
    } else {
        return;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, timer, port, who]() {
        if (suc == false && m_serverError.isEmpty()) {
            ui->ServerStatus->setText("Creating Server ... ");
        } else if (suc == true) {
            emit whostarts(who);
            ui->stackedWidget->setCurrentIndex(2); //switch to game widget
            ui->serverPortLabel->setText(QString("Server Port: %1").arg(port));
            timer->stop();
            timer->deleteLater();
        } else {
            ui->ServerStatus->setText(m_serverError);
            timer->stop();
            timer->deleteLater();
        }
    });
    // Start the timer with a 1-second interval.
    timer->start(1000);
}

void gui::on_return_btn_servercreator_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// error message during game
void gui::setErrorGame(QString error)
{
    ui->statusLabel->setText(error);
}
// error message when creating server
void gui::setErrorServer(QString error)
{
    m_serverError = error;
}
// error message when finding a server
void gui::handleClientError(QString error)
{
    m_clientError = error;
}

void gui::updateStatus(GameState state)
{
    switch (state) {
    case GameState::Opponent:
        ui->statusLabel->setText("Opponent's turn — please wait");
        break;
    case GameState::Set:
        ui->statusLabel->setText("Set one of your pieces");
        break;
    case GameState::Move:
        ui->statusLabel->setText("Move one of your pieces");
        break;
    case GameState::Jump:
        ui->statusLabel->setText("Jump one of your pieces anywhere");
        break;
    case GameState::Remove:
        ui->statusLabel->setText("Remove an opponent’s piece");
        break;
    case GameState::Win:
        ui->statusLabel->setText("Victory");
        break;
    case GameState::Loose:
        ui->statusLabel->setText("Defeat");
        break;
    case GameState::Wait:
        ui->statusLabel->setText("Waiting for Client");
        break;
    }
}

void gui::setCellState(Orientation o, Square s, PositionState st)
{

    QString name = QString("btn_%1_%2").arg(orientationToString(o)).arg(squareToString(s));
    QPushButton *btn = findChild<QPushButton*>(name);
    if (!btn) return;
    if (st == PositionState::PlayerA) {
        btn->setStyleSheet("background-color:red;");
    } else if (st == PositionState::PlayerB) {
        btn->setStyleSheet("background-color:blue;");
    } else {
        btn->setStyleSheet("");
    }
    cellStates[{o, s}] = st;
    return;
}

void gui::on_connectBtn_clicked()
{
    suc = false;
    ui->c_errorLabel->clear();
    m_clientError = "";

    ui->portLineEdit->setValidator(new QIntValidator(1024, 65535, this));

    if (!udpDiscoveryActivated) {
        emit joinServerRequested(ui->hostLineEdit->text(), ui->portLineEdit->text().toShort());
    }
    else {
        emit connectViaUdpSignal(ui->portLineEdit->text().toShort());
    }

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [this, timer]() {
        if (suc == false && m_clientError.isEmpty()) {
            ui->c_errorLabel->setText("Connecting to server...");

        } else if (suc == true) {
            ui->stackedWidget->setCurrentIndex(2); //switch to game widget
            timer->stop();
            timer->deleteLater();
        } else {
            ui->c_errorLabel->setText(m_clientError); //failed to connect
            timer->stop();
            timer->deleteLater();
        }
    });
    timer->start(1000);
}

void gui::success()
{
    suc = true;
}

void gui::on_comboBox_activated(int index)
{
    udpDiscoveryActivated = static_cast<bool>(index); //use this to know which signal to emit

    ui->label_hostname->setVisible(!udpDiscoveryActivated);
    ui->hostLineEdit->setVisible(!udpDiscoveryActivated);
}

