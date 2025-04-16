#include "game.h"
#include "position.h"
#include "moveorientation.h"
#include <QDebug>

void Game::initializeBoard()
{
    pieces.insert(position::NW_Q1, PositionState::Unset);
    pieces.insert(position::N_Q1, PositionState::Unset);
    pieces.insert(position::NO_Q1, PositionState::Unset);
    pieces.insert(position::NW_Q2, PositionState::Unset);
    pieces.insert(position::N_Q2, PositionState::Unset);
    pieces.insert(position::NO_Q2, PositionState::Unset);
    pieces.insert(position::NW_Q3, PositionState::Unset);
    pieces.insert(position::N_Q3, PositionState::Unset);
    pieces.insert(position::NO_Q3, PositionState::Unset);
    pieces.insert(position::W_Q1, PositionState::Unset);
    pieces.insert(position::W_Q2, PositionState::Unset);
    pieces.insert(position::W_Q3, PositionState::Unset);
    pieces.insert(position::O_Q3, PositionState::Unset);
    pieces.insert(position::O_Q2, PositionState::Unset);
    pieces.insert(position::O_Q1, PositionState::Unset);
    pieces.insert(position::SW_Q3, PositionState::Unset);
    pieces.insert(position::S_Q3, PositionState::Unset);
    pieces.insert(position::SO_Q3, PositionState::Unset);
    pieces.insert(position::SW_Q2, PositionState::Unset);
    pieces.insert(position::S_Q2, PositionState::Unset);
    pieces.insert(position::SO_Q2, PositionState::Unset);
    pieces.insert(position::SW_Q1, PositionState::Unset);
    pieces.insert(position::S_Q1, PositionState::Unset);
    pieces.insert(position::SO_Q1, PositionState::Unset);
}

Game::Game() {
    validMoves.reserve(64);
    validMoves.insert(position::NW_Q1, position::N_Q1);
    validMoves.insert(position::NW_Q1, position::W_Q1);
    validMoves.insert(position::N_Q1, position::N_Q2);
    validMoves.insert(position::N_Q1, position::NW_Q1);
    validMoves.insert(position::N_Q1, position::NO_Q1);
    validMoves.insert(position::NO_Q1, position::N_Q1);
    validMoves.insert(position::NO_Q1, position::O_Q1);
    validMoves.insert(position::NW_Q2, position::N_Q2);
    validMoves.insert(position::NW_Q2, position::W_Q2);
    validMoves.insert(position::N_Q2, position::N_Q1);
    validMoves.insert(position::N_Q2, position::N_Q3);
    validMoves.insert(position::N_Q2, position::NW_Q2);
    validMoves.insert(position::N_Q2, position::NO_Q2);
    validMoves.insert(position::NO_Q2, position::N_Q2);
    validMoves.insert(position::NO_Q2, position::O_Q2);
    validMoves.insert(position::NW_Q3, position::N_Q3);
    validMoves.insert(position::NW_Q3, position::W_Q3);
    validMoves.insert(position::N_Q3, position::NW_Q3);
    validMoves.insert(position::N_Q3, position::N_Q2);
    validMoves.insert(position::N_Q3, position::NO_Q3);
    validMoves.insert(position::NO_Q3, position::N_Q3);
    validMoves.insert(position::NO_Q3, position::O_Q3);
    validMoves.insert(position::W_Q1, position::NW_Q1);
    validMoves.insert(position::W_Q1, position::W_Q2);
    validMoves.insert(position::W_Q1, position::SW_Q1);
    validMoves.insert(position::W_Q2, position::W_Q1);
    validMoves.insert(position::W_Q2, position::NW_Q2);
    validMoves.insert(position::W_Q2, position::W_Q3);
    validMoves.insert(position::W_Q2, position::SW_Q2);
    validMoves.insert(position::W_Q3, position::NW_Q3);
    validMoves.insert(position::W_Q3, position::W_Q2);
    validMoves.insert(position::W_Q3, position::SW_Q3);
    validMoves.insert(position::O_Q3, position::NO_Q3);
    validMoves.insert(position::O_Q3, position::O_Q2);
    validMoves.insert(position::O_Q3, position::SO_Q3);
    validMoves.insert(position::O_Q2, position::NO_Q2);
    validMoves.insert(position::O_Q2, position::O_Q3);
    validMoves.insert(position::O_Q2, position::O_Q1);
    validMoves.insert(position::O_Q2, position::SO_Q2);
    validMoves.insert(position::O_Q1, position::NO_Q1);
    validMoves.insert(position::O_Q1, position::O_Q2);
    validMoves.insert(position::O_Q1, position::SO_Q1);
    validMoves.insert(position::SW_Q3, position::W_Q3);
    validMoves.insert(position::SW_Q3, position::S_Q3);
    validMoves.insert(position::S_Q3, position::SW_Q3);
    validMoves.insert(position::S_Q3, position::S_Q2);
    validMoves.insert(position::S_Q3, position::SO_Q3);
    validMoves.insert(position::SO_Q3, position::S_Q3);
    validMoves.insert(position::SO_Q3, position::O_Q3);
    validMoves.insert(position::SW_Q2, position::W_Q2);
    validMoves.insert(position::SW_Q2, position::S_Q2);
    validMoves.insert(position::S_Q2, position::SW_Q2);
    validMoves.insert(position::S_Q2, position::S_Q3);
    validMoves.insert(position::S_Q2, position::S_Q1);
    validMoves.insert(position::S_Q2, position::SO_Q2);
    validMoves.insert(position::SO_Q2, position::S_Q2);
    validMoves.insert(position::SO_Q2, position::O_Q2);
    validMoves.insert(position::SW_Q1, position::W_Q1);
    validMoves.insert(position::SW_Q1, position::S_Q1);
    validMoves.insert(position::S_Q1, position::S_Q2);
    validMoves.insert(position::S_Q1, position::SW_Q1);
    validMoves.insert(position::S_Q1, position::SO_Q1);
    validMoves.insert(position::SO_Q1, position::S_Q1);
    validMoves.insert(position::SO_Q1, position::O_Q1);
    initializeBoard();
}

bool Game::confirmMuehle(QPair<Orientation,Square> pos)
{
    bool muehleVertical = false;
    bool muehleHorizontal = false;
    switch (pos.first) {
    case Orientation::West:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::Suedwest, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordwest, pos.second));
        muehleHorizontal = pieces.value(position::W_Q1) == pieces.value(position::W_Q2) && pieces.value(position::W_Q2) == pieces.value(position::W_Q3);
        break;
    case Orientation::Ost:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::Suedost, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordost, pos.second));
        muehleHorizontal = pieces.value(position::O_Q1) == pieces.value(position::O_Q2) && pieces.value(position::O_Q2) == pieces.value(position::O_Q3);
        break;
    case Orientation::Nord:
        muehleVertical = pieces.value(position::N_Q1) == pieces.value(position::N_Q2) && pieces.value(position::N_Q2) == pieces.value(position::N_Q3);
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Nordwest, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordost, pos.second));
        break;
    case Orientation::Sued:
        muehleVertical = pieces.value(position::S_Q1) == pieces.value(position::S_Q2) && pieces.value(position::S_Q2) == pieces.value(position::S_Q3);
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Suedwest, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Suedost, pos.second));
        break;
    case Orientation::Nordwest:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::West, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Suedwest, pos.second));
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Nord, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordost, pos.second));
        break;
    case Orientation::Nordost:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::Ost, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Suedost, pos.second));
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Nord, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordwest, pos.second));
        break;
    case Orientation::Suedost:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::Ost, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordost, pos.second));
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Sued, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Suedwest, pos.second));
        break;
    case Orientation::Suedwest:
        muehleVertical = pieces.value(pos) == pieces.value(QPair(Orientation::West, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Nordwest, pos.second));
        muehleHorizontal = pieces.value(pos) == pieces.value(QPair(Orientation::Sued, pos.second)) &&  pieces.value(pos) == pieces.value(QPair(Orientation::Suedost, pos.second));
        break;
    }
    return muehleVertical || muehleHorizontal;
}

void Game::playerChange()
{
    myMove = !myMove;
    if (!myMove) {
        gameState = GameState::Opponent;
    } else {
        if (remainingSetMe > 0) {
            gameState = GameState::Set;
        } else if (removedByRemote < 6) {
            gameState = GameState::Move;
        } else {
            gameState = GameState::Jump;
        }
    }
    emit stateChange(gameState);
}

bool Game::canMove()
{
    if (removedByRemote >= 6 || remainingSetMe > 0) {
        return true;
    } else {
        for (QPair<Orientation,Square> piece : pieces.keys(myPlayer)) {
            for (QPair<Orientation,Square> target : validMoves.values(piece)) {
                if (pieces.value(target) == PositionState::Unset) {
                    return true;
                }
            }
        }
        return false;
    }
}

// Client only
void Game::startGame(quint8 startPlayer, quint8 groupNo)
{
    switch (startPlayer) {
    case 0x00:
        myPlayer = PositionState::PlayerB;
        remotePlayer = PositionState::PlayerA;
        myMove = false;
        gameState = GameState::Opponent;
        emit stateChange(gameState);
        break;
    case 0x01:
        myPlayer = PositionState::PlayerA;
        remotePlayer = PositionState::PlayerB;
        myMove = true;
        gameState = GameState::Set;
        emit stateChange(gameState);
        break;
    default:
        // unsupported start player
        return;
    }
    groupNo = 5;
    emit confirmGame(groupNo);
}

void Game::set(Orientation newH, Square newQ, quint8 remaining, bool muehle)
{
    if (myMove) {
        emit confirmMove(MoveStatus::WrongTurn);
    } else if (remaining != remainingSetRemote - 1) {
        emit confirmMove(MoveStatus::InvalidMove);
        emit confirm("Error: opponent has adifferent state!");
    } else {
        QPair<Orientation,Square> pos = {newH, newQ};
        if (pieces.value(pos) == PositionState::Unset) {
            pieces.insert(pos, remotePlayer);
            if (muehle) {
                if (confirmMuehle(pos)) {
                    muehleRemote = true;
                    emit confirmMove(MoveStatus::Wait);
                    emit setGUI(newH, newQ, remotePlayer);
                    remainingSetRemote--;
                    emit piecesToSetRemoteChanged(remainingSetRemote);
                } else {
                    muehleRemote = false;
                    // cannot confirm opponent has closed Mühle
                    pieces.insert(pos, PositionState::Unset);
                    emit confirmMove(MoveStatus::InvalidMove);
                }
            } else {
                emit setGUI(newH, newQ, remotePlayer);
                remainingSetRemote--;
                emit piecesToSetRemoteChanged(remainingSetRemote);
                if (canMove()) {
                    emit confirmMove(MoveStatus::PlayerChange);
                    playerChange();
                } else {
                    emit confirmMove(MoveStatus::OpponentWin);
                    gameState = GameState::Loose;
                    emit stateChange(gameState);
                }
            }
        } else {
            emit confirmMove(MoveStatus::Occupied);
        }
    }
}

void Game::move(Orientation oldH, Square oldQ, Orientation newH, bool muehle)
{
    if (myMove) {
        emit confirmMove(MoveStatus::WrongTurn);
    } else if (newH != Orientation::Nord && newH != Orientation::Ost && newH != Orientation::Sued && newH != Orientation::West){
        emit confirmMove(MoveStatus::InvalidMove);
    } else {
        QPair<Orientation,Square> oldPos = {oldH, oldQ};
        QPair<Orientation,Square> newPos = getNew(oldH, oldQ, newH);
        if (pieces.value(oldPos) != remotePlayer) {
            emit confirmMove(MoveStatus::NoPiece);
        } else if (pieces.value(newPos) != PositionState::Unset) {
            emit confirmMove(MoveStatus::Occupied);
        } else if (!validMoves.contains(oldPos, newPos)) {
            // no path between nodes
            emit confirmMove(MoveStatus::InvalidMove);
        } else {
            pieces.insert(oldPos, PositionState::Unset);
            pieces.insert(newPos, remotePlayer);
            if (muehle) {
                if (confirmMuehle(newPos)) {
                    muehleRemote = true;
                    emit confirmMove(MoveStatus::Wait);
                    emit setGUI(oldH, oldQ, PositionState::Unset);
                    emit setGUI(newPos.first, newPos.second, remotePlayer);
                } else {
                    muehleRemote = false;
                    // cannot confirm opponent has closed Mühle
                    pieces.insert(newPos, PositionState::Unset);
                    pieces.insert(oldPos, remotePlayer);
                    emit confirmMove(MoveStatus::InvalidMove);
                }
            } else {
                emit setGUI(oldH, oldQ, PositionState::Unset);
                emit setGUI(newPos.first, newPos.second, remotePlayer);
                if (canMove()) {
                    emit confirmMove(MoveStatus::PlayerChange);
                    playerChange();
                } else {
                    emit confirmMove(MoveStatus::OpponentWin);
                    gameState = GameState::Loose;
                    emit stateChange(gameState);
                }
            }
        }
    }
}

void Game::jump(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle)
{
    if (myMove) {
        emit confirmMove(MoveStatus::WrongTurn);
    } else if (removedByMe < 6) {
        // not in jump phase yet
        emit confirmMove(MoveStatus::InvalidMove);
    } else {
        QPair<Orientation,Square> oldPos = {oldH, oldQ};
        QPair<Orientation,Square> newPos = {newH, newQ};
        if (pieces.value(oldPos) != remotePlayer) {
            emit confirmMove(MoveStatus::NoPiece);
        } else if (pieces.value(newPos) != PositionState::Unset) {
            emit confirmMove(MoveStatus::Occupied);
        } else {
            pieces.insert(oldPos, PositionState::Unset);
            pieces.insert(newPos, remotePlayer);
            if (muehle) {
                if (confirmMuehle(newPos)) {
                    muehleRemote = true;
                    emit confirmMove(MoveStatus::Wait);
                    emit setGUI(oldH, oldQ, PositionState::Unset);
                    emit setGUI(newH, newQ, remotePlayer);
                } else {
                    muehleRemote = false;
                    // cannot confirm opponent has closed Mühle
                    pieces.insert(newPos, PositionState::Unset);
                    pieces.insert(oldPos, remotePlayer);
                    emit confirmMove(MoveStatus::InvalidMove);
                }
            } else {
                emit setGUI(oldH, oldQ, PositionState::Unset);
                emit setGUI(newH, newQ, remotePlayer);
                if (canMove()) {
                    emit confirmMove(MoveStatus::PlayerChange);
                    playerChange();
                } else {
                    emit confirmMove(MoveStatus::OpponentWin);
                    gameState = GameState::Loose;
                    emit stateChange(gameState);
                }
            }
        }
    }
}

void Game::doRemove(QPair<Orientation,Square> pos)
{
    pieces.insert(pos, PositionState::Unset);
    emit setGUI(pos.first, pos.second, PositionState::Unset);
    if (++removedByRemote <= 6) {
        emit confirmRemove(RemoveStatus::PlayerChange, removedByRemote);
        playerChange();
    } else {
        emit confirmRemove(RemoveStatus::OpponentWin, removedByRemote);
        gameState = GameState::Loose;
        emit stateChange(gameState);
    }
    emit piecesRemovedByRemoteChanged(removedByRemote);
}

QPair<Orientation, Square> Game::getNew(Orientation oldH, Square oldQ, Orientation moveOrientation)
{
    MoveOrientation moveH = static_cast<MoveOrientation>(moveOrientation);
    Square newQ = oldQ; // default to itself (invalid move) to silence compiler
    Orientation newH = oldH; // default to itself (invalid move) to silence compiler
    switch (oldH) {
    case Orientation::Nordost:
        switch (moveH) {
        case MoveOrientation::Sued:
            newH = Orientation::Ost;
            break;
        case MoveOrientation::West:
            newH = Orientation::Nord;
            break;
        default:
            // invalid direction
            newH = Orientation::Nordost;
            break;
        }
        break;
    case Orientation::Nordwest:
        switch (moveH) {
        case MoveOrientation::Sued:
            newH = Orientation::West;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::Nord;
            break;
        default:
            // invalid direction
            newH = Orientation::Nordwest;
            break;
        }
        break;
    case Orientation::Suedost:
        switch (moveH) {
        case MoveOrientation::West:
            newH = Orientation::Sued;
            break;
        case MoveOrientation::Nord:
            newH = Orientation::Ost;
            break;
        default:
            // invalid direction
            newH = Orientation::Suedost;
            break;
        }
        break;
    case Orientation::Suedwest:
        switch (moveH) {
        case MoveOrientation::Nord:
            newH = Orientation::West;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::Sued;
            break;
        default:
            // invalid direction
            newH = Orientation::Suedwest;
            break;
        }
        break;
    case Orientation::Nord:
        switch (moveH) {
        case MoveOrientation::West:
            newH = Orientation::Nordwest;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::Nordost;
            break;
        case MoveOrientation::Nord:
            newH = Orientation::Nord;
            newQ = oldQ == Square::Innen ? Square::Mitte : Square::Aussen;
            break;
        case MoveOrientation::Sued:
            newH = Orientation::Nord;
            newQ = oldQ == Square::Aussen ? Square::Mitte : Square::Innen;
            break;
        }
        break;
    case Orientation::Sued:
        switch (moveH) {
        case MoveOrientation::West:
            newH = Orientation::Suedwest;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::Suedost;
            break;
        case MoveOrientation::Nord:
            newH = Orientation::Sued;
            newQ = oldQ == Square::Aussen ? Square::Mitte : Square::Innen;
            break;
        case MoveOrientation::Sued:
            newH = Orientation::Sued;
            newQ = oldQ == Square::Innen ? Square::Mitte : Square::Aussen;
            break;
        }
        break;
    case Orientation::Ost:
        switch (moveH) {
        case MoveOrientation::Nord:
            newH = Orientation::Nordost;
            break;
        case MoveOrientation::Sued:
            newH = Orientation::Suedost;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::Ost;
            newQ = oldQ == Square::Innen ? Square::Mitte : Square::Aussen;
            break;
        case MoveOrientation::West:
            newH = Orientation::Ost;
            newQ = oldQ == Square::Aussen ? Square::Mitte : Square::Innen;
            break;
        }
        break;
    case Orientation::West:
        switch (moveH) {
        case MoveOrientation::Nord:
            newH = Orientation::Nordwest;
            break;
        case MoveOrientation::Sued:
            newH = Orientation::Suedwest;
            break;
        case MoveOrientation::Ost:
            newH = Orientation::West;
            newQ = oldQ == Square::Aussen ? Square::Mitte : Square::Innen;
            break;
        case MoveOrientation::West:
            newH = Orientation::West;
            newQ = oldQ == Square::Innen ? Square::Mitte : Square::Aussen;
            break;
        }
        break;
    }
    return {newH, newQ};
}

Orientation Game::getMove(Orientation oldH, Square oldQ, Orientation newH, Square newQ)
{
    Orientation moveH = newH; // default to potentially invalid move to silence compiler
    switch (oldH) {
    case Orientation::Nordost:
        switch (newH) {
        case Orientation::Ost:
            moveH = Orientation::Sued;
            break;
        case Orientation::Nord:
            moveH = Orientation::West;
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Nordwest:
        switch (newH) {
        case Orientation::West:
            moveH = Orientation::Sued;
            break;
        case Orientation::Nord:
            moveH = Orientation::Ost;
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Suedost:
        switch (newH) {
        case Orientation::Sued:
            moveH = Orientation::West;
            break;
        case Orientation::Ost:
            moveH = Orientation::Nord;
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Suedwest:
        switch (newH) {
        case Orientation::West:
            moveH = Orientation::Nord;
            break;
        case Orientation::Sued:
            moveH = Orientation::Ost;
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Nord:
        switch (newH) {
        case Orientation::Nordost:
            moveH = Orientation::Ost;
            break;
        case Orientation::Nordwest:
            moveH = Orientation::West;
            break;
        case Orientation::Nord:
            switch (oldQ) {
            case Square::Aussen:
                moveH = Orientation::Sued;
                break;
            case Square::Innen:
                moveH = Orientation::Nord;
                break;
            case Square::Mitte:
                moveH = newQ == Square::Innen ? Orientation::Sued : Orientation::Nord;
                break;
            }
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Sued:
        switch (newH) {
        case Orientation::Suedost:
            moveH = Orientation::Ost;
            break;
        case Orientation::Suedwest:
            moveH = Orientation::West;
            break;
        case Orientation::Sued:
            switch (oldQ) {
            case Square::Aussen:
                moveH = Orientation::Nord;
                break;
            case Square::Innen:
                moveH = Orientation::Sued;
                break;
            case Square::Mitte:
                moveH = newQ == Square::Innen ? Orientation::Nord : Orientation::Sued;
                break;
            }
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::Ost:
        switch (newH) {
        case Orientation::Suedost:
            moveH = Orientation::Sued;
            break;
        case Orientation::Nordost:
            moveH = Orientation::Nord;
            break;
        case Orientation::Ost:
            switch (oldQ) {
            case Square::Aussen:
                moveH = Orientation::West;
                break;
            case Square::Innen:
                moveH = Orientation::Ost;
                break;
            case Square::Mitte:
                moveH = newQ == Square::Innen ? Orientation::West : Orientation::Ost;
                break;
            }
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    case Orientation::West:
        switch (newH) {
        case Orientation::Suedwest:
            moveH = Orientation::Sued;
            break;
        case Orientation::Nordwest:
            moveH = Orientation::Nord;
            break;
        case Orientation::West:
            switch (oldQ) {
            case Square::Aussen:
                moveH = Orientation::Ost;
                break;
            case Square::Innen:
                moveH = Orientation::West;
                break;
            case Square::Mitte:
                moveH = newQ == Square::Innen ? Orientation::Ost : Orientation::West;
                break;
            }
            break;
        default:
            // this should be impossible: invalid move
            break;
        }
        break;
    }
    return moveH;
}

void Game::remove(Orientation oldH, Square oldQ)
{
    if (!muehleRemote) {
        emit confirmRemove(RemoveStatus::NoMuehle, removedByRemote);
    } else {
        QPair<Orientation,Square> pos = {oldH, oldQ};
        if (pieces.value(pos) != myPlayer) {
            emit confirmRemove(RemoveStatus::NoPiece, removedByRemote);
        } else if (!confirmMuehle(pos)) {
            doRemove(pos);
        } else {
            bool onlyMuehle = true;
            for (QPair<Orientation,Square> piece : pieces.keys(myPlayer)) {
                if (!confirmMuehle(piece)) {
                    onlyMuehle = false;
                    break;
                }
            }
            if (onlyMuehle) {
                doRemove(pos);
            } else {
                emit confirmRemove(RemoveStatus::PartOfMuehle, removedByRemote);
            }
        }
    }
}

void Game::buttonClicked(Orientation h, Square q, PositionState state)
{
    if (!network) {
        return;
    }
    QPair<Orientation,Square> pos = {h, q};
    if (pieces.value(pos) != state) {
        emit confirm("Error: GUI and logic are in different state!");
    } else if (myMove) {
        if (waitConfirm != WaitConfirm::None) {
            emit confirm("Waiting for network reply from opponent - please wait");
        } else {
            switch (gameState) {
            case GameState::Set:
                if (state == PositionState::Unset) {
                    pieces.insert(pos, myPlayer);
                    emit setGUI(h, q, myPlayer);
                    if (confirmMuehle(pos)) {
                        muehle = true;
                        emit sendSet(h, q, --remainingSetMe, true);
                    } else {
                        muehle = false;
                        emit sendSet(h, q, --remainingSetMe, false);
                    }
                    waitConfirm = WaitConfirm::Set;
                } else {
                    emit confirm("Position already occupied");
                }
                break;
            case GameState::Move:
                if (!userSelected) {
                    selected = {h, q};
                    emit confirm("Please select position to move to.");
                    userSelected = true;
                } else {
                    QPair<Orientation,Square> newPos = {h, q};
                    if (pieces.value(selected) != myPlayer) {
                        emit confirm("Please select an own piece!");
                    } else if (pieces.value(newPos) != PositionState::Unset) {
                        emit confirm("Please select an unoccupied position!");
                    } else if (!validMoves.contains(selected, newPos)) {
                        emit confirm("Jumping is not yet allowed!");
                    } else {
                        pieces.insert(selected, PositionState::Unset);
                        pieces.insert(newPos, myPlayer);
                        if (confirmMuehle(newPos)) {
                            muehle = true;
                            emit sendMove(selected.first, selected.second, getMove(selected.first, selected.second, h, q), true);
                            emit setGUI(selected.first, selected.second, PositionState::Unset);
                            emit setGUI(h, q, myPlayer);
                        } else {
                            muehle = false;
                            emit sendMove(selected.first, selected.second, getMove(selected.first, selected.second, h, q), false);
                            emit setGUI(selected.first, selected.second, PositionState::Unset);
                            emit setGUI(h, q, myPlayer);
                        }
                        waitConfirm = WaitConfirm::Move;
                    }
                    userSelected = false;
                }
                break;
            case GameState::Jump:
                if (!userSelected) {
                    selected = {h, q};
                    emit confirm("Please select position to move to.");
                    userSelected = true;
                } else {
                    QPair<Orientation,Square> newPos = {h, q};
                    if (pieces.value(selected) != myPlayer) {
                        emit confirm("Please select an own piece!");
                    } else if (pieces.value(newPos) != PositionState::Unset) {
                        emit confirm("Please select an unoccupied position!");
                    } else {
                        pieces.insert(selected, PositionState::Unset);
                        pieces.insert(newPos, myPlayer);
                        if (confirmMuehle(newPos)) {
                            muehle = true;
                            emit sendJump(selected.first, selected.second, h, q, true);
                            emit setGUI(selected.first, selected.second, PositionState::Unset);
                            emit setGUI(h, q, myPlayer);
                        } else {
                            muehle = false;
                            emit sendJump(selected.first, selected.second, h, q, false);
                            emit setGUI(selected.first, selected.second, PositionState::Unset);
                            emit setGUI(h, q, myPlayer);
                        }
                        waitConfirm = WaitConfirm::Jump;
                    }
                    userSelected = false;
                }
                break;
            case GameState::Remove:
                if (pieces.value(pos) != remotePlayer) {
                    emit confirm("Please select an opponent's piece!");
                } else if (!confirmMuehle(pos)) {
                    pieces.insert(pos, PositionState::Unset);
                    removedByMe++;
                    emit setGUI(h, q, PositionState::Unset);
                    emit sendRemove(h, q);
                    waitConfirm = WaitConfirm::Remove;
                } else {
                    bool onlyMuehle = true;
                    for (QPair<Orientation,Square> piece : pieces.keys(remotePlayer)) {
                        if (!confirmMuehle(piece)) {
                            onlyMuehle = false;
                            break;
                        }
                    }
                    if (onlyMuehle) {
                        pieces.insert(pos, PositionState::Unset);
                        removedByMe++;
                        emit setGUI(h, q, PositionState::Unset);
                        emit sendRemove(h, q);
                        waitConfirm = WaitConfirm::Remove;
                    } else {
                        emit confirm("Please select an opponent's piece,\nthat is not part of a Mühle!");
                    }
                }
                break;
            default:
                // do nothing as the user should not do anything
                break;
            }
        }
    } else {
        if (gameState != GameState::Wait) {
            // don't show this message, if there is no client yet
            emit confirm("Opponent's turn - please wait");
        }
    }
}

// Server only
void Game::handleConfirmGame(quint8 groupNo)
{
    qDebug() << groupNo;
    if (waitConfirm == WaitConfirm::GameStart) {
        if (myMove) {
            gameState = GameState::Set;
        } else {
            gameState = GameState::Opponent;
        }
        emit stateChange(gameState);
        waitConfirm = WaitConfirm::None;
    }
}

void Game::handleConfirmMove(MoveStatus statusCode)
{
    qDebug() << "handleConfirmMove called mit status: " << static_cast<quint8>(statusCode) << "und mühle: " << muehle;
    switch (waitConfirm) {
    case WaitConfirm::Set:
    case WaitConfirm::Move:
    case WaitConfirm::Jump:
        switch(statusCode) {
        case MoveStatus::PlayerChange:
            if (muehle) {
                emit confirm("Error: opponent ignored Mühle!");
            } else {
                playerChange();
            }
            break;
        case MoveStatus::OpponentWin:
            gameState = GameState::Win;
            emit stateChange(gameState);
            break;
        case MoveStatus::Wait:
            gameState = GameState::Remove;
            emit stateChange(gameState);
            break;
        default:
            emit confirm("Error: opponent rejected the change!");
            break;
        }
        emit piecesToSetMeChanged(remainingSetMe);
        waitConfirm = WaitConfirm::None;
        break;
    default:
        // not awaiting a move/set/jump confirmation: do nothing
        break;
    }
}

void Game::handleConfirmRemove(RemoveStatus statusCode, quint8 count)
{
    if (waitConfirm == WaitConfirm::Remove) {
        if (count == removedByMe) {
            switch (statusCode) {
            case RemoveStatus::PlayerChange:
                playerChange();
                break;
            case RemoveStatus::OpponentWin:
                gameState = GameState::Win;
                emit stateChange(gameState);
                break;
            default:
                emit confirm("Error: opponent rejected the change!");
                break;
            }
            emit piecesToSetMeChanged(removedByMe);
        } else {
            emit confirm("Error: opponent has a different state!");
        }
        waitConfirm = WaitConfirm::None;
    }
}

// Server only
void Game::handleConnectionRequest()
{
    if (network) {
        switch (startPlayer) {
        case 0x00: // server - me
            myPlayer = PositionState::PlayerA;
            remotePlayer = PositionState::PlayerB;
            myMove = true;
            waitConfirm = WaitConfirm::GameStart;
            break;
        case 0x01: // client - remote
            myPlayer = PositionState::PlayerB;
            remotePlayer = PositionState::PlayerA;
            myMove = false;
            waitConfirm = WaitConfirm::GameStart;
            break;
        default:
            // unsupported start player
            return;
        }
        quint8 groupNo = 5;
        emit sendStartGame(startPlayer, groupNo);
    } else {
        qDebug() << "Client connected after network loss, but as we can't be sure they have the same state, we reject them!";
    }
}

void Game::saveWhoStarts(quint8 startingPlayer)
{
    this->startPlayer = startingPlayer;
    emit stateChange(gameState);
}

void Game::handleNetworkLoss()
{
    emit confirm("Lost connection to opponent!");
    network = false;
}

void Game::resetGame()
{
    initializeBoard();
    remainingSetMe = 9;
    remainingSetRemote = 9;
    removedByMe = 0;
    removedByRemote = 0;
    muehle = false;
    muehleRemote = false;
    gameState = GameState::Wait;
    emit stateChange(gameState);
    userSelected = false;
    waitConfirm = WaitConfirm::None;
    network = true;
    emit setGUI(Orientation::Nordwest, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Nord, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Nordost, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Ost, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Suedost, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Sued, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Suedwest, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::West, Square::Aussen, PositionState::Unset);
    emit setGUI(Orientation::Nordwest, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Nord, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Nordost, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Ost, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Suedost, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Sued, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Suedwest, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::West, Square::Mitte, PositionState::Unset);
    emit setGUI(Orientation::Nordwest, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Nord, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Nordost, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Ost, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Suedost, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Sued, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::Suedwest, Square::Innen, PositionState::Unset);
    emit setGUI(Orientation::West, Square::Innen, PositionState::Unset);
}

void Game::handleNetworkRestore()
{
    network = true;
}
