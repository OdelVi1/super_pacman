#include "Present.h"
#include "Player.h"

Present::Present(sf::Vector2f position) : AbstractPresent(),
	m_texture(Graphics::getInstance().getTexture(GameTextures::PRESENT))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
}

void Present::handleCollision(Player& otherObject)
{
	m_sound.play();
	otherObject.setSuperPacman();
	otherObject.addToScore(PRESENT_SCORE);
	m_removed = true;
}

