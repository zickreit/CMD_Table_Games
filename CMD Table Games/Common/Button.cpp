#include "Common/Button.h"

Button::Button(const std::string& text)
: text_(text) {
	for (auto c : text_)
	{
		sizeX_ += getCharByteLength(static_cast<unsigned char>(c));
	}
}

std::string Button::drawButton(int charX, int charY) {
	coordX_ = charX;
	coordY_ = charY;
	return text_;
}

short Button::getCharByteLength(unsigned char c) {
	if ((c & 0xC0) != 0x80) return 1;
	else return 0;
}