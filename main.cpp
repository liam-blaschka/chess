#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(600, 600), "Chess", Style::Titlebar| Style::Close);
    window.setVerticalSyncEnabled(true);

    Game game(window);
    game.run();

    return 0;
}