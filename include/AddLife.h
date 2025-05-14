#pragma once
#include "AbstractPresent.h"
#include "Graphics.h"
#include "Player.h"

class Player;

class AddLife :public AbstractPresent
{
public:
	AddLife() = default;
	AddLife(sf::Vector2f position);
	virtual ~AddLife() = default;
	virtual void handleCollision(Player& otherObject) override;

private:
	sf::Texture m_texture;
};