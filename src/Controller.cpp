#include "Controller.h"

void Controller::startGame()
{
	Level level;
	Graphics::getInstance().getMusic().openFromFile("background_music.wav");
	Graphics::getInstance().getMusic().setLoop(true);
	while(level.loadLevel())
	{
		Graphics::getInstance().getMusic().play();
		if (!level.run())
		{
			Graphics::getInstance().getMusic().stop();
			break;
		}
		Graphics::getInstance().getMusic().stop();
	}
}