#pragma once
#include <iostream>
#include "Graphics.h"
#include "Demon.h"

class AbstractPacman
{
public:
	AbstractPacman() : m_sound(Graphics::getInstance().getSoundBuffer(GameSounds::COLLISION_SOUND)) {};
	virtual ~AbstractPacman() = default;
	virtual void handleCollision(Demon& otherObject) = 0;
	virtual sf::Color getColor() = 0;
	
protected:
	sf::Sound m_sound;
};
