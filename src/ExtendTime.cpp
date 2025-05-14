#include "ExtendTime.h"

ExtendTime::ExtendTime(sf::Vector2f position) : 
	m_texture(Graphics::getInstance().getTexture(GameTextures::EXTEND_TIME))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void ExtendTime::handleCollision(Player& otherObject)
{
	m_sound.play();
	TimeClock::getInstance().addCountDownTime(ADD_TIME);
	otherObject.addToScore(PRESENT_SCORE);
	m_removed = true;
}