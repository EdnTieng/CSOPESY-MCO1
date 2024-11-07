#ifndef MARQUEE_H
#define MARQUEE_H

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <atomic>
#include <conio.h>

// Function to set cursor position
void gotoxy(int x, int y);

// Function to clear the previous position of the marquee
void clearMarqueeArea(int prevX, int prevY, int textLength);

// Function to move the marquee within the screen
void marqueeMovement(std::atomic<bool>& running, int screenWidth, int screenHeight, std::string& userInput);

// Function to capture user input while preserving the current screen
void captureUserInput(std::string& userInput, std::atomic<bool>& running, int screenWidth, int screenHeight);

#endif // MARQUEE_H
