#pragma once
#include <SFML/Graphics.hpp>

class Square : public sf::Drawable {
    private:
        sf::RectangleShape square;
        sf::FloatRect bounds;
        bool isActivated;
        int row;
        int col;
    public:
        Square() {}
        Square(sf::Color colour, int row, int col);
        bool contains(sf::Vector2f point);
        void activate(bool isActivated);
        int getRow();
        int getCol();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};