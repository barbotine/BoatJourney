#include <SFML/Graphics.hpp>
#include <cmath>
#include "SeaManager.h"

using namespace std;

float SeaManager::wave(float x, float frequency, float amplitude, float speed, float phase, float time) {
    return sin(x * frequency + time * speed + phase) * amplitude;
}

float SeaManager::calculateWaveHeight(float x, float time, sf::Vector2f currentResolution) {
    float y = 0.0;

    x = x / currentResolution.x;

    x *= currentResolution.x / currentResolution.y;


    y += this->wave(x, 10.0, 0.015, 2.0, 0.0, time);
    y += this->wave(x, 15.0, 0.01, 3.0, 1.0, time);
    y += this->wave(x, 20.0, 0.005, 1.5, 2.0, time);

    return y;
}
