#pragma once
#include "AbstractPacman.h"

class Pacman : public AbstractPacman
{
public:
	Pacman() = default;
	Pacman(int& life) : m_life(life) {};
	virtual ~Pacman() = default;
	virtual sf::Color getColor() override { return sf::Color(255, 255, 255, 255); };
	virtual void handleCollision(Demon& otherObject) override;
private:
	int& m_life;
};

