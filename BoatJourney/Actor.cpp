#include "Actor.h"
#include <SFML/Graphics.hpp>

Actor::Actor(Vector2f position, string &actorTex) : sprite(texture), texture()
{
    if (!texture.loadFromFile(actorTex))
    {
        throw runtime_error("Texture not working");
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

Actor::Actor(Vector2f position, Texture& actorTex) : sprite(actorTex), texture(actorTex)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Actor::update(float deltaTime)
{
}

void Actor::draw(RenderWindow& window)
{
    window.draw(sprite);
}

void Actor::setPosition(Vector2f position)
{
    sprite.setPosition(position);
}

void Actor::setOriginToCenterSpriteOrigin()
{
    sprite.setOrigin(sprite.getLocalBounds().size / 2.0f);
}

void Actor::setOriginToBottomCenter()
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sf::Vector2f newOrigin(bounds.size.x / 2.f, bounds.size.y);
    sprite.setOrigin(newOrigin); 
}

bool Actor::isInsideWindowFromRight(RenderWindow& window)
{
    Vector2f position = sprite.getPosition();
    return position.x + sprite.getGlobalBounds().size.x > 0;
}

bool Actor::isInsideWindowFromLeft(RenderWindow& window)
{
    Vector2f position = sprite.getPosition();
    Vector2u windowSize = window.getSize();
    return position.x < windowSize.x;
}

Sprite& Actor::getSprite()
{
    return sprite;
}

Vector2f Actor::getPosition()
{
    return sprite.getPosition();
}
