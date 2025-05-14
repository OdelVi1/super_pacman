#include "Pacman.h"
void Pacman::handleCollision(Demon& otherObject)
{
	m_sound.play();
	m_life--;
}
