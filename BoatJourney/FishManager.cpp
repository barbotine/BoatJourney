#include "FishManager.h"

vector<Fish> FishManager::createFishes(Texture& FishText1, Texture& FishText2, Texture& FishText3, Texture& FishText4)
{
    vector<Fish> clouds;
    Fish fish = Fish(Vector2f(1700, 700.f), FishText1, 0.2f, MovementDirection::RIGHT);
    Fish fish2 = Fish(Vector2f(500.f, 0.f), FishText2, 0.05f, MovementDirection::LEFT);
    Fish fish3 = Fish(Vector2f(900.f, 0.f), FishText3, 0.05f, MovementDirection::RIGHT);
    Fish fish4 = Fish(Vector2f(1400.f, 0.f), FishText4, 0.05f, MovementDirection::LEFT);

    clouds.push_back(fish);
    clouds.push_back(fish2);
    clouds.push_back(fish3);
    clouds.push_back(fish4);
    return clouds;
}

