#include "character.hpp"
#include "iostream"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

Character::Character(sf::RenderWindow *window, const char *texturePath,
                     sf::Vector2f pos) {
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

  if (!Stexture.loadFromFile((fullPath / "Shot_1.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }

  this->characterRect = sf::IntRect({0, 0}, {128, 128});
  this->sprite = std::make_unique<sf::Sprite>(Itexture, this->characterRect);
  this->pos = pos;
  this->sprite->setPosition(pos);
}

void Character::Draw() const { this->window->draw(*sprite); }

void Character::setState(CharacterMovement movement) {
  if (this->state == CharacterMovement::Left &&
      movement == CharacterMovement::Right) {
    this->state = CharacterMovement::Idle;
  } else if (this->state == CharacterMovement::Right &&
             movement == CharacterMovement::Left) {
    this->state = CharacterMovement::Idle;
  } else if (this->state == CharacterMovement::Shoot &&
             movement == CharacterMovement::Shoot) {
    this->state = CharacterMovement::Idle;
  } else {
    this->state = movement;
  }
}

void Soldier::Animate() {
  switch (this->state) {
  case CharacterMovement::Idle:
    characterAnimationCycle = 5;
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
  case CharacterMovement::Shoot:
    characterAnimationCycle = 4;
    this->sprite->setTexture(this->Stexture);
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
  this->characterRect.position.x += 128;
  if (this->characterRect.position.x >= (characterAnimationCycle * 128)) {
    this->characterRect.position.x = 0;
  }
  this->sprite->setTextureRect(this->characterRect);
}

void Soldier::Update() {
  switch (this->state) {
  case CharacterMovement::Idle:
    vel = {0, 0};
    break;
  case CharacterMovement::Left:
    vel = {10, 0};
    break;
  case CharacterMovement::Right:
    vel = {-10, 0};
    break;
  case CharacterMovement::Shoot:
    vel = {0, 0};
    break;
  default:
    break;
  }
  this->makeBounds();
  this->sprite->setPosition(pos);
}

Soldier::Soldier(sf::RenderWindow *window, const char *texturePath,
                 std::shared_ptr<sf::Vector2u> worldBox, sf::Vector2f pos)
    : Character(window, texturePath, pos), worldBox{worldBox} {}

void Soldier::makeBounds() {
  if (pos.x + vel.x >= 0 && pos.x + 128 + vel.x <= worldBox->x) {
    pos += vel;
  }
}
