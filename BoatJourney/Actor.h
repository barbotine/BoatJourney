#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Actor
{

protected:
	Texture texture;
	Sprite sprite;

public:
	Actor(Vector2f position, string textureFile);

	virtual void update(float deltaTime) = 0;
	void draw(RenderWindow& window);
	void centerSpriteOrigin(Sprite& sprite);
};

