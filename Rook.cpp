#include "Piece.h"
#include "Rook.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Rook::Rook(char colour, Vector2f position) : Piece('r', colour) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(120, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(120, 0, 60, 60));
    }
    // sprite.setOrigin(30, 30);
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}