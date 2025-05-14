#pragma once
#include "Moving.h"
#include "Graphics.h"
#include "TimeClock.h"


const int DEMON_SCORE = 10;
const int RANDOM_DEMON_DIRECTION = 4;
const int PLUS_ONE = 1;
const int PLUS_THREE = 1;
class Demon :public Moving
{
public:
	Demon();
	virtual ~Demon() = default;
	void freezeDemon();
	virtual void setDirection(std::vector<std::vector<sf::Vector3i>> bfsTree) = 0;

protected:
	void alignHorizontal();
	void alignVertical();
	void fixPosition(Direction_t previousDirection);
	void setRandomDirection();

	sf::Texture m_texture;
	sf::Texture m_frozenTexture;
	float m_lastDirectionChangeTime;
};