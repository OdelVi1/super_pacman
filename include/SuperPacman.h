#pragma once
#include "AbstractPacman.h"

class SuperPacman : public AbstractPacman
{
public:
	SuperPacman() = default;
	SuperPacman(int& score) : m_score(score) {};
	virtual ~SuperPacman() = default;
	virtual sf::Color getColor() override { return sf::Color(0, 255, 0, 255); };
	virtual void handleCollision(Demon& otherObject) override;

private:
	int& m_score;
};
