#pragma once
#include <SFML/Graphics.hpp>

class Square : public sf::Drawable {
    private:
        sf::RectangleShape square;
        sf::FloatRect bounds;
    public:
        Square() {}
        Square(sf::Vector2f position, sf::Color colour);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};