#include "Shark.h"


Shark::Shark(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Shark::update(RenderWindow& window)
{
	position = isInsideWindowFromRight(window) ? position - Vector2f(1, 0) * speed : Vector2f(window.getSize().x + sprite.getGlobalBounds().size.x, position.y);
	sprite.setPosition(position);
}
