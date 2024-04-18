#include "Piece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Piece::Piece(char type, char colour) {
    this->type = type;
    this->colour = colour;

    chessPieces.loadFromFile("./ChessPieces.png");
    chessPieces.setSmooth(true);
}

Piece::Piece() : Piece(' ', ' ') {}

char Piece::getType() {
    return type;
}

void Piece::draw(sf::RenderTarget& target, RenderStates states) const {
    target.draw(sprite);
}
