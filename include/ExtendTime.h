#pragma once
#include "AbstractPresent.h"
#include "Graphics.h"
#include "Player.h"
#include "TimeClock.h"

const int ADD_TIME = 10;

class ExtendTime :public AbstractPresent
{
public:
	ExtendTime() = default;
	ExtendTime(sf::Vector2f position);
	virtual ~ExtendTime() = default;
	virtual void handleCollision(Player& otherObject) override;

private:
	sf::Texture m_texture;
};