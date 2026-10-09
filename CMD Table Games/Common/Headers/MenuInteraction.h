#pragma once

#include <vector>
#include "Button.h"
#include "ConsoleWindow.h"

class MenuInteraction {
public:
	bool mouseEventWaiting(ConsoleWindow& cw, const std::vector<Button>& buttons);
};