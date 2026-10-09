#include "Common/Headers/Button.h"
#include "Common/Headers/ColorsCodes.h"

Button::Button(const std::string& text, bool isSwitch)
: text_(text), isSwitch_(isSwitch) {
	if (isSwitch_) switchState_ = 0;
	for (auto c : text_)
	{
		sizeX_ += getCharByteLength(static_cast<unsigned char>(c));
	}
}

std::string Button::drawButton(int charX, int charY) {
	isDrawed_ = true;
	coordX_ = charX;
	coordY_ = charY;
	if (state_ == State::activated)
	{
		return ColorCodes::darkGrey + text_ + ColorCodes::reset;
	}
	else if (state_ == State::aiming)
	{
		return ColorCodes::grey + text_ + ColorCodes::reset;
	}
	else if (state_ == State::pressed)
	{
		return ColorCodes::darkGreyInversed + text_ + ColorCodes::reset;
	}
	else
	{
		return text_;
	}
}

short Button::getCharByteLength(unsigned char c) {
	if ((c & 0xC0) != 0x80) return 1;
	else return 0;
}