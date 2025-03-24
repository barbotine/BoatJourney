#include "CloudManager.h"

vector<Cloud> CloudManager::createClouds(Texture &CloudText1, Texture &CloudText2)
{
    vector<Cloud> clouds;
    Cloud cloud = Cloud(Vector2f(0.f, 100.f), CloudText1, 100);
    Cloud cloud2 = Cloud(Vector2f(500.f, 150), CloudText2, 100);
    Cloud cloud3 = Cloud(Vector2f(900.f, 190), CloudText1, 100);
    Cloud cloud4 = Cloud(Vector2f(1400.f, 200), CloudText2, 100);

    clouds.push_back(cloud);
    clouds.push_back(cloud2);
    clouds.push_back(cloud3);
    clouds.push_back(cloud4);
    return clouds;
}