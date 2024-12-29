#include "character.hpp"
#include <iostream>

Zombie::Zombie(sf::RenderWindow *window, const char *texturePath,
               std::shared_ptr<sf::Vector2u> worldBox, sf::Vector2f pos)
    : Character(window, texturePath, pos), worldBox(worldBox) {

  this->window = window;
  this->characterRect = sf::IntRect({0, 0}, spriteSize);
  this->sprite = std::make_unique<sf::Sprite>(Itexture, this->characterRect);
  this->pos = pos;
  this->sprite->setPosition(pos);
  this->collider.setSize({60, 60});
  this->collider.setPosition({this->pos.x + 25, this->pos.y + 60});
  this->LoadTextures(texturePath);
}

void Zombie::LoadTextures(const char *texturePath) {
  std::filesystem::path fullPath =
      std::filesystem::current_path() / "assests" / texturePath;

  if (!Itexture.loadFromFile((fullPath / "Idle.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
  if (!Rtexture.loadFromFile((fullPath / "Walk.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }

  if (!Stexture.loadFromFile((fullPath / "Attack_1.png").string())) {
    std::cout << "[ERROR] could not load texture\n";
  }
}

void Zombie::Animate() {
  switch (this->state) {
  case CharacterMovement::Idle:
    characterAnimationCycle = 4;
    this->sprite->setTexture(this->Itexture);
    break;
  case CharacterMovement::Run:
    characterAnimationCycle = 7;
    this->sprite->setTexture(this->Rtexture);
    break;
  case CharacterMovement::Shoot:
    characterAnimationCycle = 4;
    this->sprite->setTexture(this->Stexture);
    break;
  }
  this->characterRect.position.x += spriteSize.x;
  if (this->characterRect.position.x >=
      (characterAnimationCycle * spriteSize.x)) {
    this->characterRect.position.x = 0;
  }
  this->sprite->setTextureRect(this->characterRect);
}

void Zombie::Update() {
  switch (this->state) {
  case CharacterMovement::Idle:
    vel = {0, 0};
    break;
  case CharacterMovement::Run:
    if (direction == Direction::Left) {
      vel = {2, 0};
    } else {
      vel = {-2, 0};
    }
    break;
  default:
    break;
  }
  this->makeBounds();
  this->sprite->setPosition(pos);
  this->collider.setPosition({this->pos.x + 25, this->pos.y + 60});
}

void Zombie::makeBounds() {
  if (pos.x + vel.x >= 0 && pos.x + spriteSize.x + vel.x <= worldBox->x) {
		pos+=vel;
  }
}
