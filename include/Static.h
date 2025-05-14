#pragma once
#include "Object.h"

class Demon;
class Player;
class Static : public Object
{
public:
	Static() : m_removed(false) {}
	virtual ~Static()=default;
	virtual void handleCollision(Player& otherObject) = 0;
	virtual void handleCollision(Demon& otherObject) {};

	virtual bool isRemoved() { return m_removed; };
	
protected:
	bool m_removed;
	sf::Sound m_sound;
};