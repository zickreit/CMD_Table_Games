#pragma once

#include <string>

class Button {
public:
	enum class State {
		notActive,
		noInteraction,
		aiming,
		pressed
	};
private:
	State state_{};
	short coordX_{};
	short coordY_{};
	std::string text_{};
	short sizeX_{};
	short sizeY_{};
public:
	Button(const std::string& text);
	std::string drawButton(int charX, int charY);
	short getCoordX() const { return coordX_; }
	short getCoordY() const { return coordY_; }
	short getSizeX() const { return sizeX_; }
	short getSizeY() const { return sizeY_; }
	State getState() const { return state_; }
	void setButtonState(State state) { state_ = state; }
	void setButtonText(const std::string& text) { text_ = text; }
};