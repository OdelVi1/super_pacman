#pragma once
#include "AbstractPresent.h"
#include "Graphics.h"
class Player;

class Present :public AbstractPresent
{
public:
	Present() = default;
	Present(sf::Vector2f position);
	virtual ~Present() = default;
	virtual void handleCollision(Player& otherObject) override;

private:
	sf::Texture m_texture;
};