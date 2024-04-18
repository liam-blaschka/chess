#include "Piece.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Pawn::Pawn(char colour, sf::Vector2f position) : Piece('p', colour) {
    hasMoved = false;

    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(300, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(300, 0, 60, 60));
    }
    // sprite.setOrigin(30, 30);
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}