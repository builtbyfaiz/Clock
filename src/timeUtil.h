#pragma once
#include <string>
#include "text.h"
struct DisplayedText; // Forward Declaration

std::string getFormattedTime(); // Gets the current system time and formats it as HH:MM:SS AM/PM
void setUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText);