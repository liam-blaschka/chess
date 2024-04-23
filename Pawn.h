#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Pawn : public Piece {
    private:
        bool hasMoved;
    public:
        Pawn(char colour, int row, int col);
        void findMoves(Piece* board[8][8], bool validMoves[8][8]) override;
        void makeMove(int row, int col) override;
};