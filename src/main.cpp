#include "game.hpp"
#include <SFML/Graphics.hpp>
int main()
{
	Game *game = new Game(1920u,1080u,30);
	game->run();
}

