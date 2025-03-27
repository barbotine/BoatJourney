#include "Shark.h"

Shark::Shark(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed), isActive(true), spriteRespawnTime(0.0f), respawnTimer(0.0f), isRushing(false), elaspsedTime(0.f)
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

void Shark::update(RenderWindow& window, float deltaTime, Actor& actor)
{
	Vector2f position = sprite.getPosition();
	elaspsedTime += deltaTime;
	if (!isRushing)
	{
		if (elaspsedTime > 6)
		{
			isRushing = true;
			elaspsedTime = 0;
		}
	}

	if (isRushing)
	{
		rushingOnActor(actor, deltaTime);
		collidesWith(actor);
	}
	else
	{
		position = isInsideWindowFromRight(window) ? position - Vector2f(1, 0) * speed * deltaTime : Vector2f(window.getSize().x + sprite.getGlobalBounds().size.x, position.y);
		sprite.setPosition(position);
	}
}

bool Shark::getIsActive()
{
	return isActive;
}

void Shark::rushingOnActor(Actor& actor, float deltaTime)
{
	Vector2f direction = Utils::normalize(actor.getPosition() - sprite.getPosition());

	sprite.move(direction * 400.f * deltaTime);
}

void Shark::collidesWith(Actor& actor)
{
	if (sprite.getGlobalBounds().findIntersection(actor.getSprite().getGlobalBounds()))
	{
		isRushing = false;
	}
}