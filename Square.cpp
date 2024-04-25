#include "Square.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

Square::Square(Color colour, int row, int col) {
    this->row = row;
    this->col = col;
    isActivated = false;
    isSelected = false;

    square = RectangleShape(Vector2f(75, 75));
    square.setPosition(Vector2f((col * 75), (row * 75)));
    square.setFillColor(colour);
    square.setOutlineColor(Color::White);

    bounds = FloatRect(square.getPosition(), Vector2f(75, 75));
}

bool Square::contains(Vector2f point) {
    return bounds.contains(point);
}

void Square::activate(bool isActivated) {
    Color colour = square.getFillColor();
    if (!isActivated && this->isActivated) {
        // colour.r -= 10;
        colour.g -= 40;
        // colour.b += 20;
    } else if (isActivated && !this->isActivated) {
        // colour.r += 10;
        colour.g += 40;
        // colour.b -= 20;
    } 
    square.setFillColor(colour);

    this->isActivated = isActivated;
}

void Square::select(bool isSelected) {
    this->isSelected = isSelected;
    if (isSelected) {
        square.setOutlineThickness(-4);
    } else {
        square.setOutlineThickness(0);
    }
}

int Square::getRow() {
    return row;
}

int Square::getCol() {
    return col;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(square);
}