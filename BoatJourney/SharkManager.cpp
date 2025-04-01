#include "SharkManager.h"

vector<Shark> SharkManager::createSharks(Texture& sharkText1, Texture& sharkText2, Texture& sharkText3)
{
    vector<Shark> sharks;
    Shark shark = Shark(Vector2f(1900, 700.f), sharkText1, 150.f);
    Shark shark2 = Shark(Vector2f(2000, 900.f), sharkText2, 250.);
    Shark shark3 = Shark(Vector2f(1850, 750.f), sharkText3, 300.f);

    sharks.push_back(shark);
    sharks.push_back(shark2);
    sharks.push_back(shark3);

    return sharks;
}