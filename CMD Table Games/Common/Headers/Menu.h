#pragma once

#include <vector>
#include "Button.h"
#include "ConsoleWindow.h"

class MenuUI {
private:
	std::vector<Button> buttons_;
public:
	MenuUI();
	std::vector<Button> drawMenu(ConsoleWindow& cw);
};