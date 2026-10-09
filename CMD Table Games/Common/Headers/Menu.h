#pragma once

#include <vector>
#include "Button.h"
#include "ConsoleWindow.h"

class MenuUI : ConsoleWindow {
private:
	std::vector<Button> buttons_;
public:
	MenuUI();
	void drawMenu();
};

void drawMenu();