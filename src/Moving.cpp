#include "Moving.h"

sf::Vector2f Moving::getCenter()
{
	sf::Vector2f centerPos;
	centerPos.x = (m_sprite.getGlobalBounds().left - 
		((int)m_sprite.getGlobalBounds().left % int(P_SIZE))) + P_SIZE / 2; //formula find the x center when the square length is M_SIZE
	centerPos.y = (m_sprite.getGlobalBounds().top - 
		((int)m_sprite.getGlobalBounds().top % int(P_SIZE))) + P_SIZE / 2; //formula find the y center when the square length is M_SIZE
	return centerPos;
}

bool Moving::outOfBoard(sf::Vector2f board_size)
{
	return m_sprite.getPosition().x + m_sprite.getGlobalBounds().width > board_size.x ||
		m_sprite.getPosition().x < 0 ||
		m_sprite.getPosition().y + m_sprite.getGlobalBounds().height > board_size.y ||
		m_sprite.getPosition().y < 0;
}

void Moving::move(sf::Vector2f boardSize)
{
	if (getRemainingBlinkTime() > 0)
		return;

	m_previousPosition = m_sprite.getPosition();

	switch (m_direction)
	{
	case Direction_t::UP:
		m_sprite.move(0, -getDistance(boardSize));
		break;
	case Direction_t::DOWN:
		m_sprite.move(0, getDistance(boardSize));
		break;
	case Direction_t::RIGHT:
		m_sprite.move(getDistance(boardSize), 0);
		break;
	case Direction_t::LEFT:
		m_sprite.move(-getDistance(boardSize), 0);
		break;
	}

	if (outOfBoard(boardSize))
		revertPosition(); //return the player to previous position
}

//Distance may be smaller if we are near a board border
float Moving::getDistance(sf::Vector2f boardSize)
{
	float distance = m_distance;
	switch (m_direction)
	{
	case Direction_t::UP:
		if (m_sprite.getGlobalBounds().top > 0 && m_sprite.getGlobalBounds().top < distance)
		{
			return m_sprite.getGlobalBounds().top;
		}
		break;
	case Direction_t::DOWN:
		if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height < boardSize.y &&
			boardSize.y - m_sprite.getGlobalBounds().top - m_sprite.getGlobalBounds().height < distance)
		{
			return boardSize.y - m_sprite.getGlobalBounds().top - m_sprite.getGlobalBounds().height;
		}
		break;
	case Direction_t::RIGHT:
		if (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width < boardSize.x &&
			boardSize.x - m_sprite.getGlobalBounds().left - m_sprite.getGlobalBounds().width < distance)
		{
			distance = boardSize.x - m_sprite.getGlobalBounds().left - m_sprite.getGlobalBounds().width;
		}
		break;
	case Direction_t::LEFT:
		if (m_sprite.getGlobalBounds().left > 0 && m_sprite.getGlobalBounds().left < distance)
		{
			distance = m_sprite.getGlobalBounds().left;
		}
		break;
	}
	return distance;
}

//Calculate the screen position as matrix index
sf::Vector2i Moving::getPositionAsMatrixIndex()
{
	int index_x = 0, index_y = 0;
	sf::FloatRect rect = m_sprite.getGlobalBounds();

	float x = rect.left / float(P_SIZE);
	float y = rect.top / float(P_SIZE);

	if (m_direction == Direction_t::LEFT)
	{
		if (int(rect.left / P_SIZE) == int((rect.left + rect.width) / P_SIZE))
		{
			index_x = int(x);
			index_y = int(y);
		}
		else
		{
			index_x = int(ceil(x));
			index_y = int(y);
		}
	}
	else if (m_direction == Direction_t::RIGHT)
	{
		index_x = int(x);
		index_y = int(y);
	}
	else if (m_direction == Direction_t::UP)
	{
		if (int(rect.top / P_SIZE) == int((rect.top + rect.height) / P_SIZE))
		{
			index_x = int(x);
			index_y = int(y);
		}
		else
		{
			index_x = int(x);
			index_y = int(ceil(y));
		}
	}
	else if (m_direction == Direction_t::DOWN)
	{
		if (int(rect.top / P_SIZE) == int((rect.top + rect.height) / P_SIZE) ||
			int(rect.top + rect.height) % int(P_SIZE) == 0)
		{
			index_x = int(x);
			index_y = int(y);
		}
		else
		{
			index_x = int(x);
			index_y = int(ceil(y));
		}
	}
	return sf::Vector2i(index_x, index_y);
}