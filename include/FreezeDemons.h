#pragma once
#include "AbstractPresent.h"
#include "Graphics.h"
#include "Player.h"

class Player;

class FreezeDemons :public AbstractPresent
{
public:
	FreezeDemons() = default;
	FreezeDemons(sf::Vector2f position);
	virtual ~FreezeDemons() = default;
	virtual void handleCollision(Player& otherObject) override;

private:
	sf::Texture m_texture;
};