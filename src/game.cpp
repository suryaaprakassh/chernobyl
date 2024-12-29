#include "game.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <sys/types.h>

Game::Game(uint width, uint height, int framerate) {
  this->worldCords = std::make_shared<sf::Vector2u>(width, height);
  this->window = sf::RenderWindow(sf::VideoMode(*worldCords), "CHERNOBYL");
  this->window.setFramerateLimit(framerate);
  this->randor.setX(this->noHeros - 1);
}

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
        heros[currHero]->setDirection(Direction::Right);
        heros[currHero]->setState(CharacterMovement::Run);
      } else if (key->scancode == sf::Keyboard::Scancode::D) {
        heros[currHero]->setDirection(Direction::Left);
        heros[currHero]->setState(CharacterMovement::Run);
      } else if (key->scancode == sf::Keyboard::Scancode::Space) {
        heros[currHero]->setState(CharacterMovement::Shoot);
      }
    }
  }
}

void Game::setHeros(int x) {
  this->noHeros = x;
  this->noOfAlive = x;
	this->randor.setX(x-1);
  heros.clear();
  for (float x = 0; x < noHeros; x++) {
    heros.push_back(std::make_unique<Soldier>(&window, "soldier", worldCords,
                                              sf::Vector2f{400.0, 200 * x}));
  }
}

void Game::setZombie() {
  zombies.clear();
  zombies.resize(this->noHeros);

  // init zombie
  auto idx = this->randor.getRandom();
  if (idx < 0 || idx >= noHeros) {
    std::cerr << "Randor Fucked\n" << idx;
    return;
  }
  auto z = std::make_unique<Zombie>(&window, "zombie", worldCords,
                                    sf::Vector2f{0.0f, idx * 200.f});
  z->setState(CharacterMovement::Run);
  zombies[idx].push_back(std::move(z));
}

void Game::draw() {
  for (const auto &h : heros) {
    h->Draw();
  }
  for (const auto &zz : zombies) {
    for (const auto &z : zz) {
      z->Draw();
    }
  }
}

void Game::update() {
  for (const auto &h : heros) {
    h->Update();
  }
  std::stack<int> clearLevel;
  for (int zIdx = 0; zIdx < noHeros; zIdx++) {
    for (const auto &z : zombies[zIdx]) {
      if (z->checkCollision(heros[zIdx]->collider)) {
        heros[zIdx]->alive = false;
        clearLevel.push(zIdx);
      }
      z->Update();
    }
  }

  while (clearLevel.size()) {
    zombies[clearLevel.top()].clear();
    clearLevel.pop();
  }
}

void Game::animate() {
  for (const auto &h : heros) {
    h->Animate();
  }
  for (const auto &zz : zombies) {
    for (const auto &z : zz) {
      z->Animate();
    }
  }
}

void Game::run() {
  this->setZombie();
  while (gameRunning && window.isOpen()) {
    this->handleEvents();
    this->update();
    this->window.clear(sf::Color::White);
    this->draw();
    this->window.display();
    if (this->clock.getElapsedTime().asSeconds() >= (1.0 / (20.0))) {
      this->animate();
      this->clock.restart();
			this->currentZombieTime++;
			if(currentZombieTime==zombieTimer){
				this->summonZombie();
				currentZombieTime=0;
			}
    }
  }
}

void Game::summonZombie() {
  auto idx = this->randor.getRandom();
  if (idx < 0 || idx >= noHeros) {
    std::cerr << "Randor Fucked\n" << idx;
    return;
  }
  if (this->randor.getRandom() % 2 == 0) {
    auto z = std::make_unique<Zombie>(&window, "zombie", worldCords,
                                      sf::Vector2f{0.0f, idx * 200.f});
		z->setState(CharacterMovement::Run);
		zombies[idx].push_back(std::move(z));
  } else {
    auto z = std::make_unique<Zombie>(&window, "zombie", worldCords,
                                      sf::Vector2f{900.0f, idx * 200.f});
		z->setState(CharacterMovement::Run);
		z->setDirection(Direction::Right);
		zombies[idx].push_back(std::move(z));
  }
}
