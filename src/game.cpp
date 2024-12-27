#include "game.hpp"
#include <sys/types.h>

void Game::handleEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }
}

Game::Game(uint width, uint height, int framerate) {
  this->window = sf::RenderWindow(sf::VideoMode({width, height}), "CHERNOBYL");
  this->window.setFramerateLimit(framerate);
}

void Game::run() {
  Character hero(&this->window, "soldier");
  while (window.isOpen()) {
    this->handleEvents();
    this->window.clear(sf::Color::White);
    hero.Draw();
    this->window.display();
		if(this->clock.getElapsedTime().asSeconds()>=(1.0/(20.0))){
			hero.Update(CharacterMovement::Right);
			this->clock.restart();
		}
  }
}
