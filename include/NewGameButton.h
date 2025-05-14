#pragma once
#include "Button.h"
#include "Controller.h"
class NewGameButton :public Button
{
public:
	NewGameButton() = default;
	NewGameButton(float height);
	~NewGameButton() = default;
	virtual void doThis() override;
private:
};
