#pragma once
#include <SFML/Graphics.hpp>

class Piece : sf::Drawable{
    protected:
        char type;
        char colour;
        sf::Texture chessPieces;
        sf::Sprite sprite;
    public:
        Piece();
        Piece(char type, char colour);
        char getType();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};