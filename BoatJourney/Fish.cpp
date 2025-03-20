#include "Fish.h"

Fish::Fish(Vector2f position, Texture& texture, float speed, MovementDirection direction) : Actor(position, texture), speed(speed), direction(direction), wasClicked(false), isActive(true), spriteRespawnTime(0.0f), respawnTimer(0.0f)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Fish::update(RenderWindow& window, float currentTime)
{
	if (!isActive)
	{

		cout << respawnTimer << endl;

		if (currentTime - respawnTimer >= spriteRespawnTime)
		{
			makeFishAppear();
		}
	}
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

void Fish::makeFishDisappear(float currentTime)
{
	this->isActive = false;
	respawnTimer = currentTime;
	spriteRespawnTime = static_cast<float>(5 + rand() % 10);
	sprite.setColor(sf::Color::Transparent);
}

void Fish::makeFishAppear()
{
	this->isActive = true;
	sprite.setColor(sf::Color::White);
}

void Fish::draw(RenderWindow& window)
{
	window.draw(sprite);	
}

bool Fish::GetIsActive()
{
	return isActive;
}
