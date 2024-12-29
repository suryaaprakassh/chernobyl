#include "character.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Game {
private:
  sf::RenderWindow window;
  sf::Clock clock;
	std::vector<std::unique_ptr<Soldier>> heros;
  void handleEvents();
	int noHeros=4;
	int currHero=0;
	bool gameRunning = true;

	std::shared_ptr<sf::Vector2u> worldCords;

  void draw();
  void update();
  void animate();

public:
  Game(uint width, uint height, int framerate);
	void setHeros(int);
  void run();
};
