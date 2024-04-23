#include "Piece.h"
#include "King.h"
#include <SFML/Graphics.hpp>

using namespace sf;

King::King(char colour, int row, int col) : Piece('k', colour, row, col) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(60, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(60, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}