#include "Fish.h"

Fish::Fish(Vector2f position, Texture& texture, float speed, MovementDirection direction) : Actor(position, texture), speed(speed), direction(direction), wasClicked(false)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Fish::update(RenderWindow& window)
{
	if (direction == MovementDirection::LEFT)
	{
		position = isInsideWindowFromLeft(window) ? position + Vector2f(1, 0) * speed : Vector2f(-sprite.getGlobalBounds().size.x, position.y);
	}
	else
	{
		position = isInsideWindowFromRight(window) ? position - Vector2f(1, 0) * speed : Vector2f(window.getSize().x + sprite.getGlobalBounds().size.x, position.y);
	}
	
	sprite.setPosition(position);
}

Sprite& Fish::getSprite() 
{
	return sprite;
}

bool& Fish::getWasClicked()
{
	return wasClicked;
}