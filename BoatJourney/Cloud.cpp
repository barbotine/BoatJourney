#include "Cloud.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Cloud::Cloud(Vector2f position, string actorTex, Texture& texture, int speed) : Actor(position, actorTex), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);

    centerSpriteOrigin(sprite);
}

Cloud::Cloud(Vector2f position, Texture& texture, int speed) : Actor(position, texture), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Cloud::update()
{
    position += Vector2f(1, 0) * 0.3f;
    sprite.setPosition(position);
}
