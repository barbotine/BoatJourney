#include "SharkManager.h"

vector<Shark> SharkManager::createSharks(Texture& sharkText1, Texture& sharkText2, Texture& sharkText3)
{
    vector<Shark> sharks;
    Shark shark = Shark(Vector2f(1900.f, 700.f), sharkText1, 150.f);
    Shark shark2 = Shark(Vector2f(3000.f, 900.f), sharkText2, 150.);
    Shark shark3 = Shark(Vector2f(4000.f, 750.f), sharkText3, 200.f);

    sharks.push_back(shark);
    sharks.push_back(shark2);

    return sharks;
}