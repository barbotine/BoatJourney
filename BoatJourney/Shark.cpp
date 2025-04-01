#include "Shark.h"

Shark::Shark(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed), isActive(true), spriteRespawnTime(0.0f), respawnTimer(0.0f), isRushing(false), elaspsedTime(0.f), SharkBoatCollisionDetected(false), sharkClicks(0), sharkMaxClicks(5), isSharkAlive(true), wasSharkPressed(false)
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
            float respawnX = 1900.0f;

            float minY = 700.0f;
            float maxY = 900.0f;
            float randomY = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));

            sprite.setPosition(Vector2f(1900.f, randomY));
            this->isActive = true;
        }
    }
}


void Shark::update(sf::RenderWindow& window, float deltaTime, Actor& actor /* C'est le bateau ici */)
{
    if (!isActive) return;

    sf::Vector2f currentPosition = sprite.getPosition();
    elaspsedTime += deltaTime;

    if (!isRushing)
    {
        if (elaspsedTime > 6.0f)
        {
            isRushing = true;
            elaspsedTime = 0.0f;
        }
    }

    FloatRect targetBounds = actor.getSprite().getGlobalBounds();
    float targetRightEdge = targetBounds.position.x + targetBounds.size.x;
    bool shouldPerformRush = isRushing && (currentPosition.x > targetRightEdge);

    if (shouldPerformRush)
    {
        rushingOnActor(actor, deltaTime);
        collidesWith(actor);
    }
    else
    {
        if (currentPosition.x > -sprite.getGlobalBounds().size.x)
        {
            currentPosition.x -= speed * deltaTime;
        }
        else
        {
            currentPosition.x = static_cast<float>(window.getSize().x) + sprite.getGlobalBounds().size.x / 2.0f;
        }
        sprite.setPosition(currentPosition);
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


bool Shark::getSharkBoatCollisionDetected() { return SharkBoatCollisionDetected; }
void Shark::setSharkBoatCollisionDetected(bool value) { SharkBoatCollisionDetected = value; }

int Shark::getSharkClicks() const { return sharkClicks; }
void Shark::setSharkClicks(int value) { sharkClicks = value; }

int Shark::getSharkMaxClicks() const { return sharkMaxClicks; }

bool Shark::getIsSharkAlive() const { return isSharkAlive; }
void Shark::setIsSharkAlive(bool value) { isSharkAlive = value; }

bool Shark::getWasSharkPressed() const { return wasSharkPressed; }
void Shark::setWasSharkPressed(bool value) { wasSharkPressed = value; }