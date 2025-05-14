#include "AddLife.h"

AddLife::AddLife(sf::Vector2f position) : m_texture(Graphics::getInstance().getTexture(GameTextures::LIFE))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void AddLife::handleCollision(Player& otherObject)
{
	m_sound.play();
	otherObject.addLife();
	otherObject.addToScore(PRESENT_SCORE);
	m_removed = true;
}
