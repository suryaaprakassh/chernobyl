#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


enum class CharacterMovement {
	Jump,
	Left,
	Right,
	Idle
};

class Character {
private:
  sf::RenderWindow *window;
  sf::Sprite *sprite;
  sf::Texture Rtexture;
  sf::Texture Itexture;
  sf::Texture Jtexture;
  sf::Texture Ltexture;
	sf::Clock *clock;
	sf::IntRect characterRect;

	uint characterAnimationCycle=7;

  uint x, y;

public:
  Character(sf::RenderWindow *window, const char *texturePath,
            float x = 0, float y = 0);
  void Draw();
	void Update(CharacterMovement movement);
  ~Character();
};
