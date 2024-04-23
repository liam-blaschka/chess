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

                    //test
                    if (findCheck()) {
                        std::cout << "Check!" << std::endl;
                    }


                } else if (pieces[row][col] != nullptr && pieces[row][col]->getColour() == turn) {
                    resetValidMoves();
                    pieces[row][col]->findMoves(pieces, validMoves);
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (validMoves[i][j]) {
                                // simulate move on board
                                Piece* temp = pieces[i][j];
                                pieces[i][j] = pieces[row][col];
                                pieces[i][j]->setIndexes(i, j);
                                pieces[row][col] = nullptr;
                                alternateTurn();

                                // see if there is check
                                if (!findCheck()) {
                                    board[i][j].activate(validMoves[i][j]);
                                } else {
                                    validMoves[i][j] = false;
                                }

                                // return board to original state
                                pieces[row][col] = pieces[i][j];
                                pieces[row][col]->setIndexes(row, col);
                                pieces[i][j] = temp;
                                alternateTurn();
                            }
                        }
                    }
                    selectedPiece = pieces[row][col];
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

bool Board::findCheck() {
    Piece* king;
    if (turn == 'w') {
        king = kings[1]; // black king
    } else {
        king = kings[0]; // white king
    }

    bool moves[8][8];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col] != nullptr && pieces[row][col]->getColour() == turn) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        moves[i][j] = false;
                    }
                }

                pieces[row][col]->findMoves(pieces, moves);

                if (moves[king->getRow()][king->getCol()]) {
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