#include "Common/Button.h"

Button::Button(const std::string& text)
: text_(text) {
	sizeX_ = text.length();
}

std::string Button::drawButton(int charX, int charY) {
	coordX_ = charX;
	coordY_ = charY;
	return text_;
}
