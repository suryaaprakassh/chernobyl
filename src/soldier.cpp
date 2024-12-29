#include "character.hpp"

Soldier::Soldier(sf::RenderWindow *window, const char *texturePath,
                 std::shared_ptr<sf::Vector2u> worldBox, sf::Vector2f pos)
    : Character(window, texturePath, pos), worldBox{worldBox} {
  this->collider.setSize({40, 128});
  this->collider.setPosition({this->pos.x + 40, this->pos.y});
  this->LoadTextures(texturePath);
}

void Soldier::Animate() {
  switch (this->state) {
  case CharacterMovement::Idle:
    characterAnimationCycle = 5;
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

void Soldier::Update() {
  switch (this->state) {
  case CharacterMovement::Idle:
    vel = {0, 0};
    break;
  case CharacterMovement::Run:
    if (direction == Direction::Left) {
      vel = {5, 0};
    } else {
      vel = {-5, 0};
    }
    break;
  case CharacterMovement::Shoot:
    vel = {0, 0};
    break;
  default:
    break;
  }
  this->makeBounds();
  this->sprite->setPosition(pos);
  this->collider.setPosition({this->pos.x + 40, this->pos.y});
}

void Soldier::makeBounds() {
  if (pos.x + vel.x >= 0 && pos.x + spriteSize.x + vel.x <= worldBox->x) {
    pos += vel;
  }
}
