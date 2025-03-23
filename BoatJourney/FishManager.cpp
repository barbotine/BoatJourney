#include "FishManager.h"

vector<Fish> FishManager::createFishes(Texture& FishText1, Texture& FishText2, Texture& FishText3, Texture& FishText4, Texture& FishText5, Texture& FishText6)
{
    vector<Fish> clouds;
    Fish fish = Fish(Vector2f(1700, 700.f), FishText1, 200.f, MovementDirection::RIGHT);
    Fish fish2 = Fish(Vector2f(-400.f, 900.f), FishText2, 250.f, MovementDirection::LEFT);
    Fish fish3 = Fish(Vector2f(-600, 750.f), FishText3, 300.f, MovementDirection::LEFT);
    Fish fish4 = Fish(Vector2f(1800.f, 800.f), FishText4, 250.f, MovementDirection::RIGHT);
    Fish fish5 = Fish(Vector2f(-200.f, 650.f), FishText5, 200.f, MovementDirection::LEFT);
    Fish fish6 = Fish(Vector2f(-500, 900.f), FishText6, 350.f , MovementDirection::LEFT);

    clouds.push_back(fish);
    clouds.push_back(fish2);
    clouds.push_back(fish3);
    clouds.push_back(fish4);
    clouds.push_back(fish5);
    clouds.push_back(fish6);

    return clouds;
}

