#include "main.h"
#include "alarm.h"
#include "button.h"
#include "globalConst.h"
#include "resource_dir.h"
#include "stopWatch.h"
#include "text.h"
#include "timeUtil.h"
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;
using namespace chrono;

constexpr int UPPERTEXT_FONTSIZE = 32; // topleft, top and topright
constexpr int STATETEXT_FONTSIZE = 50;

void posText(DisplayedText &topText, DisplayedText &topLeftText,
             DisplayedText &topRightText, DisplayedText &stateText,
             DisplayedText &timeText, Buttons &buttons)
{
    // 1. Position independent elements first
    for (auto &button : buttons)
    {
        button.centerTitleRelative();
    }
    topText.posText(TOP);           // Top-centered
    topLeftText.posText(TOPLEFT);   // Top-left corner
    topRightText.posText(TOPRIGHT); // Top-right corner

    // 2. Position elements relative to the above
    timeText.posText(CENTER_TEXT_RELATIVE);

    // 3. Finally, position elements with the most dependencies
    stateText.posText(STATE_TEXT_RELATIVE);
}

void drawUpperText(DisplayedText &topLeftText, DisplayedText &topText,
                   DisplayedText &topRightText)
{
    topLeftText.draw();
    topText.draw();
    topRightText.draw();
}

int main()
{
    SearchAndSetResourceDir("resources");
    // Init Window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Clock");
    SetTargetFPS(75);

    // Init Audio and Alarm Sound
    InitAudioDevice();

    // Init Buttons
    Button sampleButton;
    initNavButtons(sampleButton);

    DisplayedText topLeftText, topText, topRightText, timeText, stateText,
        alarmText;                                    // Declare all Text
    timeText.text = getFormattedTime();               // Init Time Text
    stateText.text = currentState;                    // Init State Text
    setUpperText(topLeftText, topText, topRightText); // Init Upper Text

    // Init StopWatch
    Stopwatch stopwatch;

    // Init Text Colors
    topLeftText.color = topText.color = topRightText.color = GRAY;
    stateText.color = RED;

    // Init Font Sizes
    topLeftText.fontSize = topText.fontSize = topRightText.fontSize =
        UPPERTEXT_FONTSIZE;
    stateText.fontSize = STATETEXT_FONTSIZE;

    posText(topText, topLeftText, topRightText, stateText, timeText, buttons);

    // Init Alarm
    Alarm alarm;

    std::vector<Button *> timeButtons = alarm.initTimeButtons();
    alarm.positionTimeElements();

    while (!WindowShouldClose())
    {
        // Update
        if (handleNavButtonClicks())
        {
            stateText.text = currentState;
            setUpperText(topLeftText, topText, topRightText);
            posText(topText, topLeftText, topRightText, stateText, timeText,
                    buttons);
            stopwatch.stopWatchText.posText(CENTER_TEXT_RELATIVE);
            alarm.positionTimeElements();
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);
        updateActiveButtonColor();
        drawNavButtons();

        if (currentState == "TIME")
        {
            timeText.text = getFormattedTime();
            timeText.draw();
        }
        {
        }
        if (currentState == "STOPWATCH")
        {
            stopwatch.handleInput();
            stopwatch.update();
            stopwatch.draw();
        }
        if (currentState == "ALARM")
        {
            alarm.handleInput();
            alarm.updateTimeButtonRects();
            alarm.draw();
        }
        alarm.handleRing();
        drawUpperText(topLeftText, topText, topRightText);
        stateText.draw();
        EndDrawing();
    }

    UnloadMusicStream(alarm.alarmRingtone);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
