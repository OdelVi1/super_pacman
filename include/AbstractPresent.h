#pragma once
#include "Static.h"

const int PRESENT_SCORE = 5;

class AbstractPresent :public Static
{
public:
	AbstractPresent() { m_sound = sf::Sound(Graphics::getInstance().getSoundBuffer(GameSounds::GAME_PRESENT_SOUND)); };
	virtual ~AbstractPresent()=default;
protected:
};