#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

void Board::setBoard() {
    // set squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color colour;
            if ((row + col) % 2 == 0) {
                colour = Color(235, 212, 175);
            } else {
                colour = Color(185, 135, 97);
            }

            board[row][col] = Square(colour, row, col);
        }
    }

    // set pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieces[row][col] = nullptr;
        }
    }

    // black
    for (int i = 0; i < 8; i++) {
        pieces[1][i] = new Pawn('b', 1, i);
    }
    pieces[0][0] = new Rook('b', 0, 0);
    pieces[0][7] = new Rook('b', 0, 7);
    pieces[0][1] = new Knight('b', 0, 1);
    pieces[0][6] = new Knight('b', 0, 6);
    pieces[0][2] = new Bishop('b', 0, 2);
    pieces[0][5] = new Bishop('b', 0, 5);
    pieces[0][3] = new Queen('b', 0, 3);
    pieces[0][4] = new King('b', 0, 4);
    kings[1] = pieces[0][4];

    // white
    for (int i = 0; i < 8; i++) {
        pieces[6][i] = new Pawn('w', 6, i);
    }
    pieces[7][0] = new Rook('w', 7, 0);
    pieces[7][7] = new Rook('w', 7, 7);
    pieces[7][1] = new Knight('w', 7, 1);
    pieces[7][6] = new Knight('w', 7, 6);
    pieces[7][2] = new Bishop('w', 7, 2);
    pieces[7][5] = new Bishop('w', 7, 5);
    pieces[7][3] = new Queen('w', 7, 3);
    pieces[7][4] = new King('w', 7, 4);
    kings[0] = pieces[7][4];


    // set variables
    selectedPiece = nullptr;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            validMoves[row][col] = false;
        }
    }
    turn = 'w';
    lastMovedPiece = nullptr;
    check = false;
    checkmate = false;
    stalemate = false;
}

void Board::mouseClick(Vector2f point) {
    Square square;
    for (int row = 0; row < 8; row ++) {
        for (int col = 0; col < 8; col++) {
            square = board[row][col];
            if (square.contains(point)) {
                if (selectedPiece != nullptr && validMoves[row][col] == true) {
                    // remove any piece occupying destination
                    if (pieces[row][col] != nullptr) {
                        delete pieces[row][col];
                    }

                    // move piece
                    selectedPiece->makeMove(pieces, row, col);
                    selectedPiece = nullptr;
                    resetValidMoves();

                    // update last moved piece
                    if (lastMovedPiece != nullptr) {
                        lastMovedPiece->lastMoved();
                    }
                    lastMovedPiece = pieces[row][col];

                    alternateTurn();

                    // see if check
                    check = isCheck(turn);

                    // see if checkmate/stalemate
                    bool result = true;
                    // loop through each piece
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (pieces[i][j] != nullptr && pieces[i][j]->getColour() == turn) {
                                // loop through each move piece can make
                                pieces[i][j]->findMoves(pieces, validMoves, check);
                                for (int k = 0; k < 8; k++) {
                                    for (int l = 0; l < 8; l++) {
                                        if (validMoves[k][l]) {
                                            // if the move can be made (doesnt cause check of own king), it is neither checkmate or stalemate
                                            if (!tryMove(pieces[i][j], k, l)) {
                                                result = false;
                                                break;
                                            }
                                        }
                                    }
                                    if (!result) {
                                        break;
                                    }
                                }
                                resetValidMoves();
                            }
                            if (!result) {
                                break;
                            }
                        }
                        if (!result) {
                            break;
                        }
                    }

                    // if game is over
                    if (result) {
                        if (check) {
                            std::cout << "Checkmate!" << std::endl;
                            checkmate = true;
                        } else {
                            std::cout << "Stalemate!" << std::endl;
                            stalemate = true;
                        }
                    } else if (check) {
                        std::cout << "Check!" << std::endl;
                    } 

                } else if (pieces[row][col] != nullptr && pieces[row][col]->getColour() == turn) {
                    selectedPiece = pieces[row][col];
                    resetValidMoves();
                    selectedPiece->findMoves(pieces, validMoves, check);
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (validMoves[i][j]) {
                                if (tryMove(selectedPiece, i, j)) {
                                    validMoves[i][j] = false;
                                } else {
                                    board[i][j].activate(true);
                                }
                            }
                        }
                    }

                    // implement castling rules
                    if (selectedPiece->getType() == 'k' && !selectedPiece->getHasMoved()) {
                        // kingside
                        if (validMoves[row][col + 2]) {
                            if (tryMove(selectedPiece, row, col + 1)) {
                                validMoves[row][col + 2] = false;
                                board[row][col + 2].activate(false);
                            }
                        }

                        // queenside
                        if (validMoves[row][col - 2]) {
                            if (tryMove(selectedPiece, row, col - 1)) {
                                validMoves[row][col - 2] = false;
                                board[row][col - 2].activate(false);
                            }
                        }
                    }
                    
                } else {
                    selectedPiece = nullptr;
                    resetValidMoves();
                }

                break;
            }
        }
        if (square.contains(point)) {
            break;
        }
    }
}

void Board::resetValidMoves() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            validMoves[row][col] = false;
            board[row][col].activate(false);
        }
    }
}

bool Board::isCheck(char colour) {
    Piece* playerKing;
    Piece* opponentKing;
    if (colour == 'w') {
        playerKing = kings[0]; // white king
        opponentKing = kings[1]; // black king
    } else {
        playerKing = kings[1]; // black king
        opponentKing = kings[0]; // white king
    }

    bool moves[8][8];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col] != nullptr && pieces[row][col]->getColour() != colour) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        moves[i][j] = false;
                    }
                }

                pieces[row][col]->findMoves(pieces, moves, check);

                if (moves[playerKing->getRow()][playerKing->getCol()]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::alternateTurn() {
    if (turn == 'w') {
        turn = 'b';
    } else {
        turn = 'w';
    }
}

bool Board::tryMove(Piece* piece, int row, int col) {
    bool result;

    // simulate move on board
    int originalRow = piece->getRow();
    int originalCol = piece->getCol();
    Piece* temp = pieces[row][col];
    pieces[row][col] = piece;
    pieces[row][col]->setIndexes(row, col);
    pieces[originalRow][originalCol] = nullptr;

    // see if there is check
    result = isCheck(turn);

    // return board to original state
    pieces[originalRow][originalCol] = pieces[row][col];
    pieces[originalRow][originalCol]->setIndexes(originalRow, originalCol);
    pieces[row][col] = temp;

    return result;
}

void Board::draw(RenderTarget& target, RenderStates states) const {
    // draw squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            target.draw(board[row][col]);
        }
    }

    // draw pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col] != nullptr) {
                pieces[row][col]->draw(target, states);
            }
        }
    }
}

Board::~Board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            delete pieces[row][col];
        }
    }
}