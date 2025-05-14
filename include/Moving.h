#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>
#include "Static.h"

enum class Direction_t { RIGHT, DOWN, LEFT, UP };

const int DIFF_SIZE = 5;
const int BLINK_MILISECONDS = 3000;
const float M_SIZE = P_SIZE - 5;


class Player;
class Moving :public Object
{
public:
	Moving() : m_direction(Direction_t::RIGHT), m_blink_time(0), m_distance(REGULAR_SPEED) {};
	virtual ~Moving()=default;
	virtual void resetPosition() { m_sprite.setPosition(m_startingPosition); };
	void revertPosition() { m_sprite.setPosition(m_previousPosition); }; //return the player to previous position
	void move(sf::Vector2f boardSize);
	bool outOfBoard(sf::Vector2f board_size);
	sf::Vector2i getPositionAsMatrixIndex(); //Calculate the screen position as matrix index
	void setBlink() { m_blink_time = TimeClock::getInstance().getClock().getElapsedTime().asMilliseconds(); };
	int getRemainingBlinkTime() { return BLINK_MILISECONDS -
		(TimeClock::getInstance().getClock().getElapsedTime().asMilliseconds() - m_blink_time); };

protected:
	float getDistance(sf::Vector2f boardSize);
	sf::Vector2f getCenter();

	sf::Vector2f m_startingPosition;
	sf::Vector2f m_previousPosition;
	Direction_t m_direction;
	float m_distance;
	int m_blink_time;
};