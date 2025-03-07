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

void Character::makingSolarEnergy(Sun &sun, RenderWindow& window)
{
    if (sun.getIsVisible() && isMaxRessourceNotReach(solarRessource))
    {
        cout << "Adding solar ressource" << endl;
        ++solarRessource;
    }
}

bool Character::isMaxRessourceNotReach(int ressource)
{
    return ressource <= 9;
}



