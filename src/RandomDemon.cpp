#include "RandomDemon.h"

RandomDemon::RandomDemon(sf::Vector2f position) : Demon(), m_lastDirectionChangeTime(0)
{
	m_startingPosition = position;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void RandomDemon::setDirection(std::vector<std::vector<sf::Vector3i>> bfsTree)
{	
	if (getRemainingBlinkTime() > 0)
		return;

	Direction_t previousDirection = m_direction;
	
	setRandomDirection();
	
	fixPosition(previousDirection);
	switch (m_direction)
	{
	case Direction_t::RIGHT:
		m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_RIGHT);
		break;
	case Direction_t::DOWN:
		m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_DOWN);
		break;
	case Direction_t::LEFT:
		m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_LEFT);
		break;
	case Direction_t::UP:
		m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_UP);
		break;
	}	
	m_sprite.setTexture(m_texture);

}