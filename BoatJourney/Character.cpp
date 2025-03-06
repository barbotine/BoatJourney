#include "Character.h"

Character::Character(Vector2f position, Texture& texture) : Actor(position, texture)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->solarRessource = 0;
    this->life = 10;
    this->food = 10;
    this->water = 10;
}

bool Character::isSunVisible(Sun& sun, RenderWindow& window)
{
    cout << "Sun is visible" << endl;
    if(sun.sunIsVisible(window))
    {
        cout << "Sun is visible" << endl;
    }
    else 
    {
        cout << "Sun is not visible" << endl;
    }
    return sun.sunIsVisible(window);
}

void Character::makingSolarEnergy(Sun& sun, RenderWindow& window)
{
    if (isSunVisible(sun, window) && isMaxRessourceNotReach(solarRessource))
    {
        cout << "Adding solar ressource" << endl;
        ++solarRessource;
    }
}

bool Character::isMaxRessourceNotReach(int ressource)
{
    return ressource <= 9;
}


