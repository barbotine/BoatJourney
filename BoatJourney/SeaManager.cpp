#include "SeaManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

float SeaManager::wave(float x, float frequency, float amplitude, float speed, float phase, float time) {
    return sin(x * frequency + time * speed + phase) * amplitude;
}

float SeaManager::calculateWaveHeight(float x, float time) {
    float y = 0.0;

    y += wave(x, 10.0, 0.015, 2.0, 0.0, time);
    y += wave(x, 15.0, 0.01, 3.0, 1.0, time);
    y += wave(x, 20.0, 0.005, 1.5, 2.0, time);

    return y;
}