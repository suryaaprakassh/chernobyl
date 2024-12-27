#include "character.hpp"
#include "iostream"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

Character::Character(sf::RenderWindow *window, const char *texturePath, float x,
                     float y) {
  this->window = window;

  std::filesystem::path fullPath =
      std::filesystem::current_path() / "assests" / texturePath;

  if (!Itexture.loadFromFile((fullPath / "Idle.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
  if (!Rtexture.loadFromFile((fullPath / "Left.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
  if (!Jtexture.loadFromFile((fullPath / "Right.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }

  this->characterRect = sf::IntRect({0, 0}, {128, 128});
  this->sprite = new sf::Sprite(Itexture, this->characterRect);
  this->sprite->setPosition(sf::Vector2{x, y});
}

void Character::Update(CharacterMovement movement) {
  switch (movement) {
  case CharacterMovement::Idle:
    characterAnimationCycle = 6;
    this->sprite->setTexture(this->Itexture);
    this->sprite->setScale({1.f, 1.f});
    this->sprite->setOrigin({0.f, 0.f});
    break;
  case CharacterMovement::Left:
    characterAnimationCycle = 7;
    this->sprite->setTexture(this->Rtexture);
    this->sprite->setScale({1.f, 1.f});
    this->sprite->setOrigin({0.f, 0.f});
    break;
  case CharacterMovement::Right:
    characterAnimationCycle = 7;
    this->sprite->setTexture(this->Rtexture);
    this->sprite->setScale({-1.f, 1.f});
    this->sprite->setOrigin({this->sprite->getGlobalBounds().size.x, 0.f});
    break;
  case CharacterMovement::Jump:
    break;
  }
  if (this->characterRect.position.x >= (characterAnimationCycle * 128)) {
    this->characterRect.position.x = 0;
  } else {
    this->characterRect.position.x += 128;
    this->sprite->setTextureRect(this->characterRect);
  }
}

void Character::Draw() { this->window->draw(*sprite); }

Character::~Character() {}
