#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
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

            board[row][col] = Square(Vector2f((row * 75), (col * 75)), colour);
        }
    }


    // set pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieces[row][col] = new Piece();
        }
    }

    // black
    delete pieces[0][0];
    pieces[0][0] = new Rook('b', Vector2f(0, 0));
    delete pieces[0][7];
    pieces[0][7] = new Rook('b', Vector2f(7 * 75, 0));
    for (int i = 0; i < 8; i++) {
        delete pieces[1][i];
        pieces[1][i] = new Pawn('b', Vector2f(i * 75, 75));
    }

    // white
    delete pieces[7][0];
    pieces[7][0] = new Rook('w', Vector2f(0, 7 * 75));
    delete pieces[7][7];
    pieces[7][7] = new Rook('w', Vector2f(7 * 75, 7 * 75));
    for (int i = 0; i < 8; i++) {
        delete pieces[6][i];
        pieces[6][i] = new Pawn('w', Vector2f(i * 75, 6 * 75));
    }
}

void Board::mouseClick(Vector2i position) {

}

void Board::draw(RenderTarget& target, RenderStates states) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            target.draw(board[row][col]);
        }
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col]->getType() != ' ') {
                pieces[row][col]->draw(target, states);
            }
        }
    }
}
