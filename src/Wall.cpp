#include "Wall.h"
#include "Player.h"
#include "Demon.h"

Wall::Wall(sf::Vector2f position) : m_texture(Graphics::getInstance().getTexture(GameTextures::WALL))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void Wall::handleCollision(Player& otherObject)
{
	otherObject.revertPosition();
}

void Wall::handleCollision(Demon& otherObject)
{
	otherObject.revertPosition();
}