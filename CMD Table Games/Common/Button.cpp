#include "Common/Button.h"

Button::Button(int sizeX, int sizeY, const std::string& text)
: sizeX_(sizeX), sizeY_(sizeY), text_(text) {}

std::string Button::drawButton(int charX, int charY) {
	coordX_ = charX;
	coordY_ = charY;
	return text_;
}
