#pragma once
#include <SFML/Graphics.hpp>

class TimeClock
{
public:
	~TimeClock()=default;
	static TimeClock& getInstance();
	sf::Clock& getClock() {return m_clock;}
	void addCountDownTime(float seconds) { m_countDownStartTime += seconds; };
	float getCountDownSeconds() { return m_countDownStartTime; };
	void reset();
private:
	TimeClock();
	TimeClock(const TimeClock&)=default; //copy c-tor
	sf::Clock m_clock;
	float m_countDownStartTime;
};