#pragma once

#include <vector>
#include "Button.h"
#include "ConsoleWindow.h"

class MenuInteraction {
public:
	bool mouseEventWaiting(ConsoleWindow& cw, std::vector<Button>& buttons);
	int getButtonId(const std::vector<Button>& buttons, SHORT x, SHORT y);
};