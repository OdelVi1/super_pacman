#pragma once
#include "Moving.h"
#include "AbstractPacman.h"
#include "Pacman.h"
#include "SuperPacman.h"
#include "Static.h"
#include "Demon.h"
#include <queue>

float const SUPER_PACMAN_TIME = 8;
int const FROZEN_DEAMONS_MILLISECONDS = 6000; //defining time for freeze
float const DISTANCE = 1.5;
int const FOUR_SECONDS = 4;
int const THOUSAND_MILLI_SECONDS = 1000;
int const DIVIDED_BY = 2;
class Demon;
class Static;
class Player :public Moving
{
public:
	Player() = default;
	Player(int& life, int& score);
	virtual ~Player() = default;
	void setDirection(sf::Keyboard::Key direction);
	void setStartingPosition(sf::Vector2f position);
	void handleCollision(Demon& otherObject);
	void setSuperPacman();
	bool isSuperPacman() { return dynamic_cast<SuperPacman*> (m_pacman.get()); };
	void setFrozenDemons();
	int getRemainigFrozenDemonsSeconds() {
		auto x = FROZEN_DEAMONS_MILLISECONDS -
			(TimeClock::getInstance().getClock().getElapsedTime().asMilliseconds() - m_frozenDemonsStartTime);
		return x;
	};
	virtual void draw() override;
	void resetPacman();

	void addLife() { m_life++; };
	void decrementLife() { m_life--; };
	void addToScore(int score) { m_score += score; };
private:
	void setPacman();
	sf::Texture m_texture;
	std::unique_ptr <AbstractPacman> m_pacman; //Pointer to AbstractPacman since it is a pure virtual  
	//class and we can't hold a pure virtual class here but we can hold a pointer to a pure virtual class
	float m_superPacmanStartTime;
	int m_frozenDemonsStartTime;
	int& m_score;
	int& m_life;
};
