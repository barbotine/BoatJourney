#pragma once
#include "ProgressBar.h"
class HungerBar : public ProgressBar
{
private :
    float maxHunger;          
    float currentHunger;      
    float hungerDecayRate;

public :
    HungerBar(float x, float y);
    void FillTheBar();
    void EmptyTheBar(float deltaTime);
    float GetCurrentHunger();
    float GetMaxHunger();
};

