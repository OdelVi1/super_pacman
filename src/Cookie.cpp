#include "Cookie.h"
#include "Player.h"

Cookie::Cookie(sf::Vector2f position, int &cookies): m_texture(Graphics::getInstance().getTexture(GameTextures::COOKIE)),
m_cookies(cookies)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
	m_sound = sf::Sound(Graphics::getInstance().getSoundBuffer(GameSounds::COOKIE_SOUND));
}

void Cookie::handleCollision(Player& otherObject)
{
	m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::COOKIE_SOUND));
	m_sound.play();
	otherObject.addToScore(COOKIE_SCORE);
	m_cookies--;
	m_removed = true;
}
