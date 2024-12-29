#pragma once
#include "character.hpp"
#include "randomGen.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Game {
private:
  sf::RenderWindow window;
  sf::Clock clock;
  std::vector<std::unique_ptr<Soldier>> heros;
  std::vector<std::vector<std::unique_ptr<Zombie>>> zombies;
  void handleEvents();
  int noHeros = 4;
	int noOfAlive=4;
  int currHero = 0;
  bool gameRunning = true;
	int zombieTimer=5; 
	int currentZombieTime=0;
  Randor randor;

  std::shared_ptr<sf::Vector2u> worldCords;

  void draw();
  void update();
  void animate();

  bool checkCollision();

public:
  Game(uint width, uint height, int framerate);
  void setHeros(int);
	void setZombie();
  void summonZombie();
  void run();
};
