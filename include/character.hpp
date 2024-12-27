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
	sf::Clock *clock;
	sf::IntRect characterRect;

	uint characterAnimationCycle=7;


public:
	sf::Vector2f pos;
	
  Character(sf::RenderWindow *window, const char *texturePath,
            sf::Vector2f = {0.f,0.f});
  void Draw();
	void Update(CharacterMovement movement);
	void Animate(CharacterMovement movement);
  ~Character();
};
