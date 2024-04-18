#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Rook : public Piece {
    public:
        Rook(char colour, sf::Vector2f position);
};