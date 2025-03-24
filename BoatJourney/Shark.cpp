#include "Shark.h"


Shark::Shark(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed), isActive(true), spriteRespawnTime(0.0f), respawnTimer(0.0f)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Shark::makeSharkDisappear(float currentTime)
{
	respawnTimer = currentTime;
	spriteRespawnTime = static_cast<float>(5 + rand() % 10);
	spriteRespawnTime = 5;
	this->isActive = false;
}

void Shark::makeSharkAppear(float currentTime)
{
	if (!isActive) {
		if (currentTime - respawnTimer >= spriteRespawnTime)
		{
  			this->isActive = true;
		}
	}
}

void Shark::update(RenderWindow& window, float deltaTime)
{
	position = isInsideWindowFromRight(window) ? position - Vector2f(1, 0) * speed * deltaTime : Vector2f(window.getSize().x + sprite.getGlobalBounds().size.x, position.y);
	sprite.setPosition(position);
}

bool Shark::getIsActive()
{
	return isActive;
}
