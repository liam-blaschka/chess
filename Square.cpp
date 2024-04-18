#include "Square.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Square::Square(Vector2f position, Color colour) {
    square = RectangleShape(Vector2f(75, 75));
    square.setPosition(position);
    square.setFillColor(colour);

    bounds = FloatRect(position, Vector2f(75, 75));
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(square);
}