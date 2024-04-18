#pragma once
#include "Square.h"
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
    private:
        Square board[8][8];
        Piece* pieces[8][8];
    public:
        void setBoard();
        void mouseClick(sf::Vector2i position);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};