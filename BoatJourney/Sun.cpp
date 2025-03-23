#include "Sun.h"
Sun::Sun(Vector2f position, string actorTex, Texture& texture, float speed) : Actor(position, actorTex), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->isVisible = true;
}

Sun::Sun(Vector2f position, Texture& texture, float speed) : Actor(position, texture), speed(speed)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->isVisible = true;
}

float Sun::generateRandomTime()
{
    return 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (5.0f - 1.0f)));
}

void Sun::update(RenderWindow& window, float deltaTime)
{
    float invisibleDuration;
    srand(static_cast<unsigned>(time(0)));
    invisibleDuration = generateRandomTime();
   
    if (!isInsideWindowFromLeft(window))
    {
        position = Vector2f(0.f, 0.f);
        makeSunInvisible(window);
    }
    else
    {
        position += Vector2f(1, 0) * speed * deltaTime;
        makeSunVisible(window, invisibleDuration);
    }

    sprite.setPosition(position);
}

void Sun::makeSunInvisible(RenderWindow& windowr)
{
    bool timerStarted = false;
   
    if (!timerStarted)
    {
        timer.restart();
        timerStarted = true;
    }
    sprite.setColor(Color(255, 255, 255, 0));
    position = Vector2f(0.f, 0.f);
    this->isVisible = false;
}

void Sun::makeSunVisible(RenderWindow& window, float sunAppearingTime)
{  
    if (timer.getElapsedTime().asSeconds() >= sunAppearingTime) {
        sprite.setColor(sf::Color(255, 255, 255, 255));
        this->isVisible = true;
    }
}

bool Sun::getIsVisible()
{
    return this->isVisible;
}