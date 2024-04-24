#pragma once
#include "Square.h"
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
    private:
        Square board[8][8];
        Piece* pieces[8][8];
        bool validMoves[8][8];
        Piece* selectedPiece;
        char turn;
        Piece* kings[2];
        Piece* lastMovedPiece;
        bool check;
        bool checkmate;
        bool stalemate;
    public:
        void setBoard();
        void mouseClick(sf::Vector2f point);
        void resetValidMoves();
        bool isCheck(char colour);
        bool tryMove(Piece* piece, int row, int col);
        void alternateTurn();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        ~Board();
};