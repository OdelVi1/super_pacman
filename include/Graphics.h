#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include <SFML/Audio.hpp>

enum class GameSounds {
	GAME_OVER = 0, 
	WIN,
	GAME_PRESENT_SOUND,
	COOKIE_SOUND,
	COLLISION_SOUND,
	DOOR_SOUND
};

enum class GameTextures
{
	PACMAN_RIGHT = 0,
	PACMAN_LEFT,
	PACMAN_UP,
	PACMAN_DOWN,
	DEMON_RIGHT,
	DEMON_LEFT,
	DEMON_UP,
	DEMON_DOWN,
	DOOR,
	PRESENT,
	LIFE,
	EXTEND_TIME,
	FROZEN_DEMON,
	FREEZE_DEMON_PRESENT,
	WALL,
	KEY,
	COOKIE,
	PACMAN_TITLE,
	HELP_BUTTON,
	GAME_OVER,
	GAME_WON,
	NEW_GAME_BUTTON,
	INSTRUCTION,
	RETURN,
	EXIT_BUTTON,
	LAST
};
class Graphics
{
public:
	~Graphics() = default;
	static Graphics& getInstance();
	sf::RenderWindow& getWindow() { return m_window; }
	sf::Texture& getTexture(GameTextures texture ) { return m_texture[int(texture)]; }
	sf::SoundBuffer& getSoundBuffer(GameSounds gameSound) { return m_soundBuffer[int(gameSound)]; };
	sf::Music& getMusic() { return m_music; }

private:
	Graphics();
	Graphics(const Graphics&) = default; //copy c-tor
	sf::RenderWindow m_window;
	std::vector < sf::Texture> m_texture;
	std::vector < sf::SoundBuffer> m_soundBuffer;
	sf::Music m_music;
};