#pragma once

#include <string>

class Button {
public:
	enum class State {
		noInteraction,
		activated,
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
	bool isSwitch_{};
	int switchState_ = -1;
public:
	Button(const std::string& text, bool isSwitch = false);
	std::string drawButton(int charX, int charY);
	short getCoordX() const { return coordX_; }
	short getCoordY() const { return coordY_; }
	short getSizeX() const { return sizeX_; }
	short getSizeY() const { return sizeY_; }
	State getState() const { return state_; }
	void setButtonState(State state) { state_ = state; }
	void setButtonText(const std::string& text) { text_ = text; }
	short getCharByteLength(unsigned char c);
	bool isSwitchButton() { return isSwitch_; }
	int getSwitchState() { return switchState_; }
	void setSwitchState(int state) { switchState_ = state; }
};