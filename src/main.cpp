#include "game.hpp"
#include <SFML/Graphics.hpp>
int main()
{
	Game *game = new Game(1080u,580u,30);
	game->setHeros(3);
	game->run();
}

