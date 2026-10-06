#pragma once

#include <string>

class Button {
private:
	enum class State {
		notActive,
		noInteraction,
		aiming,
		pressed
	};
	State state_{};
	int coordX_{};
	int coordY_{};
	std::string text_{};
	int sizeX_{};
	int sizeY_{};
public:
	Button(int sizeX, int sizeY, const std::string& text);
	std::string drawButton(int charX, int charY);
};

