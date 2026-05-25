#ifndef UI_H
#define UI_H
#include <windows.h>

void setColor(int color);
void clearScreen();
void setWindowSize(int width, int height);
void setConsoleTitle(const char *title);
void setCursorVisibility(int visible);
void pressEnterToContinue();
void printHeader();
void printMenuOption(int num, const char *text);
void showMenu();
void showPatientMenu();
void showSearchMenu();
void showchoiceMenu();
void printSectionHeader(const char *title);
void printDivider();
void printField(const char *label, const char *value);
void printSuccess(const char *msg);
void printError(const char *msg);
void printPrompt(const char *msg);
#endif