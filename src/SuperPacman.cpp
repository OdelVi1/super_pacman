#include "SuperPacman.h"
void SuperPacman::handleCollision(Demon& otherObject)
{
	if (otherObject.getRemainingBlinkTime() > 0)
	{
		return;
	}
	m_sound.play();
	m_score += DEMON_SCORE;
	otherObject.resetPosition();
	otherObject.setBlink();
}
