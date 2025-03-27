#include "Cloud.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Cloud::Cloud(Vector2f position, string actorTex, Texture& texture, float speed) : Actor(position, actorTex), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

Cloud::Cloud(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

// changer en move 
// comprendre ce que j'ai fait
void Cloud::update(RenderWindow& window, float deltaTime)
{
    Vector2f position = sprite.getPosition();
    position = isInsideWindowFromLeft(window) ? position + Vector2f(1, 0) * speed * deltaTime : Vector2f(sprite.getGlobalBounds().size.x, position.y);
    sprite.setPosition(position);
}

