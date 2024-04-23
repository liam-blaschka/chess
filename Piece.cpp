#include "Piece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Piece::Piece(char type, char colour, int row, int col) {
    this->type = type;
    this->colour = colour;
    this->row = row;
    this->col = col;

    setPosition(row, col);

    chessPieces.loadFromFile("./ChessPieces.png");
    chessPieces.setSmooth(true);
}

Piece::Piece() : Piece('e', ' ', -1, -1) {}

char Piece::getType() {
    return type;
}

char Piece::getColour() {
    return colour;
}

void Piece::makeMove(int row, int col) {
    this->row = row;
    this->col = col;
    setPosition(row, col);
}

int Piece::getRow() {
    return row;
}

int Piece::getCol() {
    return col;
}

void Piece::setPosition(int row, int col) {
    position = Vector2f(col * 75, row * 75);
    sprite.setPosition(position);
}

void Piece::draw(sf::RenderTarget& target, RenderStates states) const {
    target.draw(sprite);
}
