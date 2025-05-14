#pragma once
#include "Button.h"
#include "Graphics.h"
const float SCALE_SIZE = 0.5;
const int CENTER = 2;
const int POSITION = 650;
class HelpButton :public Button
{
public:
	HelpButton() = default;
	HelpButton(float height);
	~HelpButton() = default;
	virtual void doThis() override;

private:
	sf::Sprite m_instruction;
	sf::Sprite m_return;
};
