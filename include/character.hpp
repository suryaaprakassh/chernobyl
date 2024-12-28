#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

enum class CharacterMovement { Jump, Left, Right, Idle ,Shoot};

class Character {
public:
  sf::RenderWindow *window;
  std::unique_ptr<sf::Sprite> sprite;
  sf::Texture Rtexture, Itexture, Jtexture,Stexture;
  sf::Clock *clock;
  sf::IntRect characterRect;
  CharacterMovement state;

  uint characterAnimationCycle = 7;
  sf::Vector2f pos, vel;

  Character(sf::RenderWindow *window, const char *texturePath,
            sf::Vector2f = {0.0f, 0.0f});
  void Draw() const;
  void setState(CharacterMovement movement);
  virtual void Update() = 0;
  virtual void Animate() = 0;
  virtual ~Character() = default;
};

class Soldier : public Character {
public:
  Soldier(sf::RenderWindow *window, const char *texturePath,
          sf::Vector2f = {0.0f, 0.0f});
  void Update();
  void Animate();
};
