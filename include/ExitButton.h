#pragma once
#include "Button.h"
const int DIVIDED_BY_TWO = 2;
class ExitButton :public Button
{
public:
	ExitButton() = default;
	ExitButton(float height);
	~ExitButton() = default;
	virtual void doThis() override;
private:

};