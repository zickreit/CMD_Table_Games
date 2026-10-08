#pragma once
#include <string>
namespace ColorCodes {
	const std::string red = "\033[38;2;220;60;60m";
	const std::string blue = "\033[38;2;80;140;255m";
	const std::string darkGrey = "\033[38;5;236m";
	const std::string darkGreyInversed = "\033[48;5;244m\033[38;5;232m";
	const std::string grey = "\033[38;5;244m";
	const std::string dim = "\033[2m";
	const std::string reset = "\033[0m";
}
