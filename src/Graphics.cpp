#include "Graphics.h"

Graphics::Graphics() :m_window(sf::RenderWindow(sf::VideoMode(1000, 1000), "Super-Pacman", sf::Style::Titlebar | sf::Style::Close)),
m_texture(int(GameTextures::LAST), sf::Texture()), m_soundBuffer(6, sf::SoundBuffer()), m_music() //intialize the vector with size and Texture instances
{
	m_texture[int(GameTextures::PACMAN_RIGHT)].loadFromFile("pacman_right.png");
	m_texture[int(GameTextures::PACMAN_LEFT)].loadFromFile("pacman_left.png");
	m_texture[int(GameTextures::PACMAN_UP)].loadFromFile("pacman_up.png");
	m_texture[int(GameTextures::PACMAN_DOWN)].loadFromFile("pacman_down.png");
	m_texture[int(GameTextures::DEMON_RIGHT)].loadFromFile("demon_right.png");
	m_texture[int(GameTextures::DEMON_UP)].loadFromFile("demon_up.png");
	m_texture[int(GameTextures::DEMON_LEFT)].loadFromFile("demon_left.png");
	m_texture[int(GameTextures::DEMON_DOWN)].loadFromFile("demon_down.png");
	m_texture[int(GameTextures::DOOR)].loadFromFile("door.png");
	m_texture[int(GameTextures::PRESENT)].loadFromFile("present.png");
	m_texture[int(GameTextures::LIFE)].loadFromFile("heart.png");
	m_texture[int(GameTextures::EXTEND_TIME)].loadFromFile("extend_time.png");
	m_texture[int(GameTextures::FROZEN_DEMON)].loadFromFile("frozen_demon.png");
	m_texture[int(GameTextures::FREEZE_DEMON_PRESENT)].loadFromFile("freeze.png");
	m_texture[int(GameTextures::WALL)].loadFromFile("wall.png");
	m_texture[int(GameTextures::KEY)].loadFromFile("key.png");
	m_texture[int(GameTextures::COOKIE)].loadFromFile("cookie.png");
	m_texture[int(GameTextures::PACMAN_TITLE)].loadFromFile("pac_man.png");
	m_texture[int(GameTextures::HELP_BUTTON)].loadFromFile("helpButton.png");
	m_texture[int(GameTextures::NEW_GAME_BUTTON)].loadFromFile("newgame.png");
	m_texture[int(GameTextures::EXIT_BUTTON)].loadFromFile("exit.png");
	m_texture[int(GameTextures::GAME_OVER)].loadFromFile("gameover.png");
	m_texture[int(GameTextures::GAME_WON)].loadFromFile("gamewon.png");
	m_texture[int(GameTextures::INSTRUCTION)].loadFromFile("instruction.png");
	m_texture[int(GameTextures::RETURN)].loadFromFile("return.png");
	m_soundBuffer[int(GameSounds::GAME_OVER)].loadFromFile("game_over.wav");
	m_soundBuffer[int(GameSounds::WIN)].loadFromFile("win.wav");
	m_soundBuffer[int(GameSounds::GAME_PRESENT_SOUND)].loadFromFile("present.wav");
	m_soundBuffer[int(GameSounds::COOKIE_SOUND)].loadFromFile("cookie.wav");
	m_soundBuffer[int(GameSounds::COLLISION_SOUND)].loadFromFile("collision.wav");
	m_soundBuffer[int(GameSounds::DOOR_SOUND)].loadFromFile("doorSound.wav");
}

Graphics& Graphics::getInstance()
{
	static Graphics m_instance;
	return m_instance;
}