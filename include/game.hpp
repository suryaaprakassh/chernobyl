#include <SFML/Graphics.hpp>
#include "character.hpp"

class Game {
	private:
		sf::RenderWindow window;
		sf::Clock clock;
		void handleEvents();

	public:
		Game(uint width, uint height, int framerate);
		void run();

};
