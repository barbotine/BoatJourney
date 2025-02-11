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

void Cloud::update(RenderWindow& window)
{
    bool CloudInsideWindow = cloudIsVisible(window);

    if (!CloudInsideWindow)
    {
        position = Vector2f(0.f, 0.f);
    }
    else
    {
        position += Vector2f(1, 0) * speed;
    }

    sprite.setPosition(position);
}

bool Cloud::cloudIsVisible(RenderWindow& window)
{
    Vector2f position = sprite.getPosition();
    Vector2u windowSize = window.getSize();

    return windowSize.x > position.x;
}