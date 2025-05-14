#include "Demon.h"

Demon::Demon() : m_texture(Graphics::getInstance().getTexture(GameTextures::DEMON_RIGHT)),
m_frozenTexture(Graphics::getInstance().getTexture(GameTextures::FROZEN_DEMON)),
m_lastDirectionChangeTime()
{

}

void Demon::setRandomDirection()
{
	float timeSinceGameStarted = TimeClock::getInstance().getClock().getElapsedTime().asSeconds();
	int switchDirection = rand() % (int(timeSinceGameStarted) + PLUS_ONE) + PLUS_THREE;

	if (timeSinceGameStarted - m_lastDirectionChangeTime >= switchDirection)
	{
		Direction_t arr[] = { Direction_t::LEFT,
		Direction_t::RIGHT,
		Direction_t::UP,
		Direction_t::DOWN };
		m_direction = arr[rand() % RANDOM_DEMON_DIRECTION];
		m_lastDirectionChangeTime = TimeClock::getInstance().getClock().getElapsedTime().asSeconds();
	}
}

void Demon::freezeDemon()
{
	m_sprite.setTexture(m_frozenTexture);
}

void Demon::alignVertical()
{
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	if (int(rect.top) / P_SIZE <
		int(rect.top + rect.height) / P_SIZE)
	{
		float rounded_top = round(rect.top / float(P_SIZE)) * P_SIZE;
		m_sprite.move(0, rounded_top - rect.top); //align the demon vertically
	}
}

void Demon::alignHorizontal()
{
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	if (int(rect.left) / P_SIZE <
		int(rect.left + rect.width) / P_SIZE)
	{
		float rounded_left = round(rect.left / float(P_SIZE)) * P_SIZE;
		m_sprite.move(rounded_left - rect.left, 0); //align the demon Horizontally
	}
}

void Demon::fixPosition(Direction_t previousDirection)
{
	switch (previousDirection)
	{
	case Direction_t::RIGHT:
	case Direction_t::LEFT:
		if (m_direction != Direction_t::UP && m_direction != Direction_t::DOWN)
		{
			alignVertical(); //center the demon
		}
		break;
	case Direction_t::DOWN:
	case Direction_t::UP:
		if (m_direction != Direction_t::RIGHT && m_direction != Direction_t::LEFT)
		{
			alignHorizontal();
		}
		break;
	}
}