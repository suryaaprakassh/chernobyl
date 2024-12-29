#include "game.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <sys/types.h>

void Game::handleEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::W) {
        heros[currHero]->setState(CharacterMovement::Idle);
        currHero = (currHero - 1 + noHeros) % noHeros;
      } else if (key->scancode == sf::Keyboard::Scancode::S) {
        heros[currHero]->setState(CharacterMovement::Idle);
        currHero = (currHero + 1) % noHeros;
      } else if (key->scancode == sf::Keyboard::Scancode::A) {
        heros[currHero]->setState(CharacterMovement::Right);
      } else if (key->scancode == sf::Keyboard::Scancode::D) {
        heros[currHero]->setState(CharacterMovement::Left);
      } else if (key->scancode == sf::Keyboard::Scancode::Space) {
        heros[currHero]->setState(CharacterMovement::Shoot);
      }
    }
  }
}

Game::Game(uint width, uint height, int framerate) {
  this->worldCords = std::make_shared<sf::Vector2u>(width, height);
  this->window = sf::RenderWindow(sf::VideoMode(*worldCords), "CHERNOBYL");
  this->window.setFramerateLimit(framerate);
  for (float x = 0; x < noHeros; x++) {
    heros.push_back(std::make_unique<Soldier>(&window, "soldier", worldCords,
                                              sf::Vector2f{0.0, 200 * x}));
  }
}

void Game::setHeros(int x) { 
	this->noHeros = x;
	heros.clear();
  for (float x = 0; x < noHeros; x++) {
    heros.push_back(std::make_unique<Soldier>(&window, "soldier", worldCords,
                                              sf::Vector2f{0.0, 200 * x}));
  }
}
void Game::draw() {
  for (const auto &h : heros) {
    h->Draw();
  }
}

void Game::update() {
  for (const auto &h : heros) {
    h->Update();
  }
}

void Game::animate() {
  for (const auto &h : heros) {
    h->Animate();
  }
}

void Game::run() {
  while (gameRunning && window.isOpen()) {
    this->handleEvents();
    this->update();
    this->window.clear(sf::Color::White);
    this->draw();
    this->window.display();
    if (this->clock.getElapsedTime().asSeconds() >= (1.0 / (30.0))) {
      this->animate();
      this->clock.restart();
    }
  }
}
