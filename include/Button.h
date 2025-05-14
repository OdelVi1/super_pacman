#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Graphics.h"

enum class ButtonState
{
    normal = 0,
    hovered = 1,
    clicked = 2
};

const int BUTTON_HEIGHT = 150;
const int BUTTON_WIDTH = 400;

class Button
{
public:
    Button() = default;
    Button(GameTextures);
    virtual ~Button() = default;
    void draw();
    void checkEvent(sf::Event& e);
    virtual void doThis() = 0;

protected:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
};