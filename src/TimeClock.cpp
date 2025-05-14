#include "TimeClock.h"

TimeClock::TimeClock() : m_clock(sf::Clock()), m_countDownStartTime(0.0f)
{
}

TimeClock& TimeClock::getInstance()
{
	static TimeClock m_instance;
	return m_instance;
}

void TimeClock::reset()
{ 
	m_countDownStartTime = 0.0f; 
	m_clock.restart();
}