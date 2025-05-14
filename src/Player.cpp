#include "Player.h"

Player::Player(int& life, int& score) : m_texture(Graphics::getInstance().getTexture(GameTextures::PACMAN_RIGHT)),
m_superPacmanStartTime(0.0f), m_frozenDemonsStartTime(-FROZEN_DEAMONS_MILLISECONDS), m_score(score), m_life(life)
{
	m_distance = REGULAR_SPEED * DISTANCE;
	setPacman();
	m_direction = Direction_t::RIGHT;
	m_sprite.setTexture(m_texture);
	m_sprite.scale((M_SIZE) / m_sprite.getGlobalBounds().width, (M_SIZE) / m_sprite.getGlobalBounds().height);
}

void Player::setStartingPosition(sf::Vector2f position) //in the beginning of the level 
{
	m_startingPosition = position;
	m_sprite.setPosition(position);
	m_superPacmanStartTime = 0;
	setPacman();
	m_frozenDemonsStartTime = -FROZEN_DEAMONS_MILLISECONDS;
}

void Player::setDirection(sf::Keyboard::Key direction)
{	
	if (getRemainingBlinkTime() > 0)
		return;

	switch (direction)
	{
	case sf::Keyboard::Left:
		m_direction = Direction_t::LEFT;
		m_texture = Graphics::getInstance().getTexture(GameTextures::PACMAN_LEFT);
		break;
	case sf::Keyboard::Right:
		m_direction = Direction_t::RIGHT;
		m_texture = Graphics::getInstance().getTexture(GameTextures::PACMAN_RIGHT);
		break;
	case sf::Keyboard::Up:
		m_direction = Direction_t::UP;
		m_texture = Graphics::getInstance().getTexture(GameTextures::PACMAN_UP);
		break;
	case sf::Keyboard::Down:
		m_direction = Direction_t::DOWN;
		m_texture = Graphics::getInstance().getTexture(GameTextures::PACMAN_DOWN);
		break;
	}
	m_sprite.setTexture(m_texture);
}

void Player::handleCollision(Demon& otherObject)
{
	m_pacman->handleCollision(otherObject);	
}

//change the player to Super Pacman
void Player::setSuperPacman()
{
	m_superPacmanStartTime = TimeClock::getInstance().getClock().getElapsedTime().asSeconds();
	if (!isSuperPacman())
	{
		m_pacman = std::make_unique < SuperPacman >(m_score);
		m_sprite.setColor(m_pacman->getColor());
	}
}

//change the player to regular Pacman
void Player::setPacman()
{
	m_pacman = std::make_unique < Pacman >(m_life);
	m_sprite.setColor(m_pacman->getColor());
}

//Reset FrozenDemons 
void Player::setFrozenDemons()
{
	m_frozenDemonsStartTime = TimeClock::getInstance().getClock().getElapsedTime().asMilliseconds();
}

void Player::draw() 
{
	resetPacman();
	auto time_pass = TimeClock::getInstance().getClock().getElapsedTime();
	if (isSuperPacman() && time_pass.asSeconds() >= m_superPacmanStartTime + SUPER_PACMAN_TIME - FOUR_SECONDS)
	{
		time_pass.asMilliseconds() % THOUSAND_MILLI_SECONDS > (THOUSAND_MILLI_SECONDS / DIVIDED_BY) ? 
			m_sprite.setColor(sf::Color(255, 255, 255, 255)) : m_sprite.setColor(m_pacman->getColor());
	}
	Graphics::getInstance().getWindow().draw(m_sprite);
};

void Player::resetPacman()
{
	if (isSuperPacman() &&
		TimeClock::getInstance().getClock().getElapsedTime().asSeconds() >= m_superPacmanStartTime + SUPER_PACMAN_TIME)
	{
		setPacman();
	}
}