#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Pawn : public Piece {
    private:
        bool hasMoved;
    public:
        Pawn(char colour, sf::Vector2f position);
};