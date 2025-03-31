#pragma once
class SeaManager
{
	public:
		float wave(float x, float frequency, float amplitude, float speed, float phase, float time);
		float calculateWaveHeight(float x, float time);
};

