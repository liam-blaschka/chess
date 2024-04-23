#pragma once
#include <SFML/Graphics.hpp>

class Piece : public sf::Drawable {
    protected:
        char type;
        char colour;
        sf::Texture chessPieces;
        sf::Sprite sprite;
        sf::Vector2f position;
        int row;
        int col;
    public:
        Piece();
        Piece(char type, char colour, int row, int col);
        char getType();
        char getColour();
        virtual void findMoves(Piece* board[8][8], bool validMoves[8][8]) = 0;
        virtual void makeMove(int row, int col);
        int getRow();
        int getCol();
        void setPosition(int row, int col);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};