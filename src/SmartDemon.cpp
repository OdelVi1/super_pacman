#include "SmartDemon.h"

SmartDemon::SmartDemon(sf::Vector2f position) : Demon()
{
	m_startingPosition = position;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void SmartDemon::setBfsDirection(std::vector<std::vector<sf::Vector3i>> bfsTree, sf::Vector2i indexPosition)
{
	if (bfsTree[indexPosition.y][indexPosition.x].y != 0)
	{
		if (bfsTree[indexPosition.y][indexPosition.x].y == 1)
		{
			m_direction = Direction_t::LEFT;
			m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_LEFT);
		}
		else
		{
			m_direction = Direction_t::RIGHT;
			m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_RIGHT);
		}
	}
	else
	{
		if (bfsTree[indexPosition.y][indexPosition.x].z == 1)
		{
			m_direction = Direction_t::UP;
			m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_UP);
		}
		else
		{
			m_direction = Direction_t::DOWN;
			m_texture = Graphics::getInstance().getTexture(GameTextures::DEMON_DOWN);
		}
	}
}

void SmartDemon::setDirection(std::vector<std::vector<sf::Vector3i>> bfsTree)
{
	if (getRemainingBlinkTime() > 0)
		return;

	Direction_t previous_direction = m_direction;
	sf::Vector2i indexPosition = getPositionAsMatrixIndex();

	if (bfsTree.empty())
	{
		setRandomDirection();
	}
	else
	{
		setBfsDirection(bfsTree, indexPosition);
	}
	fixPosition(previous_direction);

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
