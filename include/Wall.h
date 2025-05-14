#pragma once
#include "Static.h"
#include "Graphics.h"
class Player;
class Demon;

class Wall : public Static
{
public:
	Wall() = default;
	Wall(sf::Vector2f position);
	virtual ~Wall() = default;
	virtual void handleCollision(Player& otherObject) override;
	virtual void handleCollision(Demon& otherObject) override;
private:
	sf::Texture m_texture;
};