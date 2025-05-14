#pragma once
#include "Static.h"
#include "Graphics.h"

const int COOKIE_SCORE = 2;
class Player;

class Cookie : public Static
{
public:
	Cookie() = default;
	Cookie(sf::Vector2f position, int& cookies);
	virtual ~Cookie()=default;
	virtual void handleCollision(Player& otherObject) override;

private:
	sf::Texture m_texture;
	int& m_cookies;
};