#include "character.hpp"
#include <SFML/Graphics.hpp>

class Game {
private:
  sf::RenderWindow window;
  sf::Clock clock;
	std::vector<std::unique_ptr<Soldier>> heros;
  void handleEvents();
	int noHeros=4;
	int currHero=0;

  void draw();
  void update();
  void animate();

public:
  Game(uint width, uint height, int framerate);
  void run();
};
