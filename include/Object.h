#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "GameStatus.h"

const float P_SIZE = 60; //cell size
const float REGULAR_SPEED = 0.1f;
const int BOUNDARY_RESIZE = 2;

class Player;
class Object
{
public:
	Object()=default;
	virtual ~Object()=default;
	virtual void draw() {Graphics::getInstance().getWindow().draw(m_sprite);};
	virtual sf::Vector2f getPosition() { return m_sprite.getPosition(); }
	bool checkCollision(Object& obj);
	
protected:
	sf::Sprite m_sprite;
};
