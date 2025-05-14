#include "Object.h"

bool Object::checkCollision(Object& obj)
{
	auto player_bounds = sf::FloatRect(obj.m_sprite.getGlobalBounds());
	//Reduce the tested height and width by 10 pixels to avoid player stuck between objects and look like it touches it
	player_bounds.height -= BOUNDARY_RESIZE * 2;
	player_bounds.width -= BOUNDARY_RESIZE * 2;
	player_bounds.top += BOUNDARY_RESIZE;
	player_bounds.left += BOUNDARY_RESIZE;
	auto obj_bounds = m_sprite.getGlobalBounds();
	return player_bounds.intersects(obj_bounds);
}