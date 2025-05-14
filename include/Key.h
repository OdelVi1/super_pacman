#pragma once
#include "Static.h"
#include "Graphics.h"
#include "Player.h"
const int KEY_SCORE = 7;
class Player;

class Key : public Static
{
public:
	Key() = default;
	Key(sf::Vector2f position, bool *locked);
	virtual ~Key() = default;
	virtual void handleCollision(Player& otherObject) override;
	virtual bool isRemoved() override { return (m_removed || !(*m_locked)); }; //return true if removed or the door not locked 
private:
	sf::Texture m_texture;
	bool* m_locked;
};