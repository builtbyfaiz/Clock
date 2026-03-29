#pragma once
#include "text.h"
#include "button.h"

void drawUpperText(DisplayedText &topLeftText, DisplayedText &topText,
                   DisplayedText &topRightText);
                   
void posText(DisplayedText &topText, DisplayedText &topLeftText,
             DisplayedText &topRightText, DisplayedText &stateText,
             DisplayedText &timeText, Buttons &buttons);
