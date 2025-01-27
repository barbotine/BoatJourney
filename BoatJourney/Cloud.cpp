#include "Cloud.h"
Cloud::Cloud(RenderWindow& window) : sprite(texture)
{
    Texture cloudTex;
    if (!cloudTex.loadFromFile("../assets/texture/cloud.png")) {
        throw runtime_error("Texture not working");
    }
    texture = cloudTex;
    float cloudX = 0.f;
    float cloudY = 0.f;
    Vector2f cloudPosition(cloudX, cloudY);
    sprite = Sprite(cloudTex);
    sprite.setPosition(cloudPosition);
    window.draw(sprite);
}


