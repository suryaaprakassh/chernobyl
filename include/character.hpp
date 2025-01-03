#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

enum class CharacterMovement { Run, Idle, Shoot };

enum class Direction {Left, Right};

class Character {
public:
  sf::RenderWindow *window;
  std::unique_ptr<sf::Sprite> sprite;
  sf::Texture Rtexture, Itexture, Stexture;
  sf::Clock *clock;
  sf::IntRect characterRect;
	Direction direction = Direction::Left;
  CharacterMovement state = CharacterMovement::Idle;
  sf::Vector2i spriteSize = {128, 128};
  bool alive = true;

  uint characterAnimationCycle = 7;
  sf::Vector2f pos, vel;
  sf::RectangleShape collider;

  Character(sf::RenderWindow *, const char *, sf::Vector2f = {0.0f, 0.0f});
  void Draw() const;
  void setState(CharacterMovement);
	void setDirection(Direction);
  bool checkCollision(sf::RectangleShape &);
  virtual void Update() = 0;
  virtual void Animate() = 0;
  virtual void makeBounds() = 0;
  virtual void LoadTextures(const char *);
  virtual ~Character() = default;
};

class Soldier : public Character {
private:
  std::shared_ptr<sf::Vector2u> worldBox;

public:
  Soldier(sf::RenderWindow *, const char *, std::shared_ptr<sf::Vector2u>,
          sf::Vector2f = {0.0f, 0.0f});
  void makeBounds() override;
  void Update() override;
  void Animate() override;
};

class Zombie : public Character {
private:
  std::shared_ptr<sf::Vector2u> worldBox;

public:
  Zombie(sf::RenderWindow *window, const char *texturePath,
         std::shared_ptr<sf::Vector2u> worldBox,
         sf::Vector2f pos = {0.0f, 0.0f});
  sf::Vector2i spriteSize = {96, 96};

  void LoadTextures(const char *) override;
  void makeBounds() override;
  void Update() override;
  void Animate() override;
};
