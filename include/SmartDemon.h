#pragma once
#include "Demon.h"
#include <queue>

class SmartDemon : public Demon
{
public:
	SmartDemon(sf::Vector2f position);
	virtual ~SmartDemon() = default;
	virtual void setDirection(std::vector<std::vector<sf::Vector3i>> bfsTree) override;
private:
	void setBfsDirection(std::vector<std::vector<sf::Vector3i>> bfsTree, sf::Vector2i indexPosition);
};