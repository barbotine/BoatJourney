#include "HungerBar.h"


HungerBar::HungerBar(float PositionX, float PositionY) : ProgressBar(PositionX, PositionY), maxHunger(100), currentHunger(100), hungerDecayRate(5.0f)
{

}

void HungerBar::FillTheBar()
{
	currentHunger += 10;
	if (currentHunger > maxHunger) currentHunger = maxHunger;
}

void HungerBar::EmptyTheBar(float deltaTime)
{
    static float elapsedTime = 0;
    elapsedTime += deltaTime;
    if (elapsedTime >= 2.0f)
    {
        currentHunger -= 10;
        if (currentHunger < 0) currentHunger = 0;

        elapsedTime = 0;
    }
}

float HungerBar::GetCurrentHunger()
{
	return currentHunger;
}

float HungerBar::GetMaxHunger()
{
	return maxHunger;
}