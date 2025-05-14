#pragma once
#include "Static.h"
#include "Graphics.h"
class Player;
const int DOOR_SCORE = 7;

class Door : public Static
{
public:
	Door() = default;
	Door(sf::Vector2f position, bool* locked);
	virtual ~Door() = default;
	virtual void handleCollision(Player& otherObject) override;
	virtual void handleCollision(Demon& otherObject) override;
	virtual bool isRemoved() override { return (m_removed || !(* m_locked));}; //return true if removed or the key open door

private:
	sf::Texture m_texture;
	bool* m_locked;
};