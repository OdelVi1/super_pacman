#include "Door.h"
#include "Player.h"
#include "Demon.h"

Door::Door(sf::Vector2f position, bool* locked) : m_texture(Graphics::getInstance().getTexture(GameTextures::DOOR)),
m_locked(locked)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.scale(P_SIZE / m_sprite.getGlobalBounds().width, P_SIZE / m_sprite.getGlobalBounds().height);
	m_sound = sf::Sound(Graphics::getInstance().getSoundBuffer(GameSounds::DOOR_SOUND));
}

void Door::handleCollision(Player& otherObject)
{
	if(otherObject.isSuperPacman()) //super pacman breaking doors
	{
		m_sound.play();
		m_removed = true;
		*m_locked = false;
		otherObject.addToScore(DOOR_SCORE);
	}
	else
	{
		otherObject.revertPosition();
	}
}

void Door::handleCollision(Demon& otherObject)
{
	otherObject.revertPosition();
}