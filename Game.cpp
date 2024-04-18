#include "Game.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Game::Game(RenderWindow& window) {
    this->window = &window;
    board.setBoard();
}

void Game::run() {
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                // window closed
                case Event::Closed:
                    window->close();
                    break;

                // mouse clicked
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left) {
                        board.mouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    break;

                default:
                    break;
            }
        }

        window->draw(board);
        window->display();
    }
}