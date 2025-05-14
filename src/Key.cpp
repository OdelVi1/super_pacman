#include "Key.h"


Key::Key(sf::Vector2f position, bool* locked) : m_texture(Graphics::getInstance().getTexture(GameTextures::KEY)),
m_locked(locked)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
	m_sound = sf::Sound(Graphics::getInstance().getSoundBuffer(GameSounds::DOOR_SOUND));
}

void Key::handleCollision(Player& otherObject)
{
	m_sound.play();
	otherObject.addToScore(KEY_SCORE);
	m_removed = true;
	*m_locked = false;
}