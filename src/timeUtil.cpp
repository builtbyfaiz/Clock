#include <ctime>  // For time handling
#include "timeUtil.h" // For the declaration of getFormattedTime()
#include "text.h"
#include "globalConst.h"
#include <iostream>
#include <array>
#include <string>

std::string getFormattedTime()
{
    std::array<char, 100> buffer{};

    std::time_t now = std::time(nullptr);
    std::tm timeinfo{};

#if defined(_WIN32) || defined(_WIN64)
    if (localtime_s(&timeinfo, &now) != 0) return "";
#else
    if (localtime_r(&now, &timeinfo) == nullptr) return "";
#endif

    if (std::strftime(buffer.data(), buffer.size(), "%I:%M:%S %p", &timeinfo) == 0)
        return "";

    return std::string(buffer.data());
}

void setUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText)
{
    if (currentState == "TIME")
    {
        topLeftText.text = "Clock By Faiz";
        topText.text = "<WELCOME>";
        topRightText.text = "V1.0";
    }
    if (currentState == "STOPWATCH")
    {
        topLeftText.text = "Left->Toggle";
        topText.text = "<MouseClick>";
        topRightText.text = "Reset<-Right";
    }
    if (currentState == "ALARM")
    {
        topLeftText.text = "---";
        topText.text = "NOT IMPLEMENTED";
        topRightText.text = "---";
    }
}