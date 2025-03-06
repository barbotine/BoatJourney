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

void Character::setSolarRessources(bool isGeneratedSolarEnergy)
{
    if (isGeneratedSolarEnergy && maxRessourcesAlllowed(solarRessource)) {
        ++solarRessource;
    }
    std::cout << "Number of solar energy: " << solarRessource << std::endl;
}

bool Character::maxRessourcesAlllowed(int ressource)
{
    return ressource <= 9;
}


