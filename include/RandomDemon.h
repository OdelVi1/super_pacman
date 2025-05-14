#pragma once
#include "Demon.h"

class RandomDemon : public Demon
{
public:
	RandomDemon(sf::Vector2f position);
	virtual ~RandomDemon() = default;
	virtual void setDirection(std::vector<std::vector<sf::Vector3i>> bfsTree) override;
private:
	float m_lastDirectionChangeTime;
};