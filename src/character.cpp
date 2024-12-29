#include "character.hpp"
#include "iostream"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

Character::Character(sf::RenderWindow *window, const char *texturePath,
                     sf::Vector2f pos) {
  this->window = window;
  this->characterRect = sf::IntRect({0, 0}, spriteSize);
  this->sprite = std::make_unique<sf::Sprite>(Itexture, this->characterRect);
  this->pos = pos;
  this->sprite->setPosition(pos);
  this->collider.setFillColor(sf::Color::White);
  this->collider.setOutlineThickness(2.0f);
  this->collider.setOutlineColor(sf::Color::Black);
}

void Character::LoadTextures(const char *texturePath) {
  std::filesystem::path fullPath =
      std::filesystem::current_path() / "assests" / texturePath;

  if (!Itexture.loadFromFile((fullPath / "Idle.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
  if (!Rtexture.loadFromFile((fullPath / "Left.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }

  if (!Stexture.loadFromFile((fullPath / "Shot_1.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
}

void Character::Draw() const {
  if (!this->alive)
    return;
  this->window->draw(collider);
  this->window->draw(*sprite);
}

void Character::setDirection(Direction direction) {
  if (direction == Direction::Left) {
    this->direction = Direction::Left;
    this->sprite->setScale({1.f, 1.f});
    this->sprite->setOrigin({0.f, 0.f});
  } else if (direction == Direction::Right) {
    this->direction = Direction::Right;
    this->sprite->setScale({-1.f, 1.f});
    this->sprite->setOrigin({this->sprite->getGlobalBounds().size.x, 0.f});
  }
}

void Character::setState(CharacterMovement movement) {
  if (movement == this->state) {
    this->state = CharacterMovement::Idle;
  } else {
    this->state = movement;
  }
}

bool Character::checkCollision(sf::RectangleShape &collider) {
  if (this->collider.getGlobalBounds().findIntersection(
          collider.getGlobalBounds())) {
    return true;
  }
  return false;
}
