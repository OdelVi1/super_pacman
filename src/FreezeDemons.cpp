#include "FreezeDemons.h"

FreezeDemons::FreezeDemons(sf::Vector2f position) :
	m_texture(Graphics::getInstance().getTexture(GameTextures::FREEZE_DEMON_PRESENT))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void FreezeDemons::handleCollision(Player& otherObject)
{
	m_sound.play();
	otherObject.addToScore(PRESENT_SCORE);
	otherObject.setFrozenDemons();
	m_removed = true;
}