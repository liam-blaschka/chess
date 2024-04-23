#include "Piece.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

Pawn::Pawn(char colour, int row, int col) : Piece('p', colour, row, col) {
    hasMoved = false;

    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(300, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(300, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void Pawn::findMoves(Piece* board[8][8], bool validMoves[8][8]) {
    int direction;
    if (colour == 'w') {
        direction = -1;
    } else {
        direction = 1;
    }

    // one space forward
    if (board[row + direction][col] == nullptr) {
        validMoves[row + direction][col] = true;

        // two spaces forward
        if (!hasMoved && board[row + (2 * direction)][col] == nullptr) {
            validMoves[row + (2 * direction)][col] = true;
        }
    }

    // attack left
    if (col - 1 >= 0) {
        Piece* piece = board[row + direction][col - 1];
        if (piece != nullptr && colour != piece->getColour()) {
            validMoves[row + direction][col - 1] = true;
        }
    }

    // attack right
    if (col + 1 <= 7) {
        Piece* piece = board[row + direction][col + 1];
        if (piece != nullptr && colour != piece->getColour()) {
            validMoves[row + direction][col + 1] = true;
        }
    }
}

void Pawn::makeMove(int row, int col) {
    Piece::makeMove(row, col);
    if (!hasMoved) {
        hasMoved = true;
    }
}