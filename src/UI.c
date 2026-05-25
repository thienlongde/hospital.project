#include "UI.h"
#include <stdio.h>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    Sleep(50);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD homeCoords = {0, 0};

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
    fflush(stdout);
}

void setWindowSize(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setConsoleTitle(const char *title) {
    SetConsoleTitleA(title);
}

void setCursorVisibility(int visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void pressEnterToContinue() {
    setColor(8);
    printf("\n  Nhan Enter de tiep tuc...");
    setColor(7);
    fflush(stdout);
    getchar();
}

void printHeader() {
    setColor(11);
    printf("╔══════════════════════════════════════╗\n");
    printf("║     He thong quan ly va dat lich     ║\n");
    printf("╚══════════════════════════════════════╝\n");
    setColor(7);
}

void printMenuOption(int num, const char *text) {
    setColor(14);
    printf("  [%d] ", num);
    setColor(15);
    printf("%s\n", text);
    setColor(7);
}

void showMenu() {
    clearScreen();
    printHeader();
    printf("\n");
    setColor(10);
    printf("  *** MENU CHINH ***\n\n");
    setColor(7);
    printMenuOption(1, "Tra cuu thong tin");
    printMenuOption(2, "Dat lich kham");
    printMenuOption(3, "Quan ly / Tra cuu lich hen");
    printMenuOption(0, "Thoat");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
    fflush(stdout);
}

/*void showPatientMenu() {
    clearScreen();
    printHeader();
    printf("\n");
    setColor(10);
    printf("  *** QUAN LY BENH NHAN ***\n\n");
    setColor(7);
    printMenuOption(1, "Them benh nhan");
    printMenuOption(2, "Xoa benh nhan");
    printMenuOption(3, "Sua thong tin");
    printMenuOption(0, "Quay lai");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
    fflush(stdout);
}*/

void showSearchMenu() {
    clearScreen();
    printHeader();
    printf("\n");
    setColor(10);
    printf("  *** TRA CUU THONG TIN ***\n\n");
    setColor(7);
    printMenuOption(1, "Tim theo ma BHYT");
    printMenuOption(2, "Tim theo so dien thoai");
    printMenuOption(3, "Tim theo ho ten");
    printMenuOption(0, "Quay lai");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
    fflush(stdout);
}

void showchoiceMenu() {
    clearScreen();
    printHeader();
    printf("\n");
    setColor(10);
    printf("  *** QUAN LY LICH HEN ***\n\n");
    setColor(7);
    printMenuOption(1, "Huy lich hen");
    printMenuOption(2, "Tra cuu lich hen");
    printMenuOption(0, "Quay lai");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
    fflush(stdout);
}

void printSectionHeader(const char *title) {
    printf("\n");
    setColor(11);
    printf("  ╔══════════════════════════════════════╗\n");
    printf("  ║  %-36s║\n", title);
    printf("  ╚══════════════════════════════════════╝\n");
    setColor(7);
    printf("\n");
    fflush(stdout);
}

void printDivider() {
    setColor(8);
    printf("  ----------------------------------------\n");
    setColor(7);
    fflush(stdout);
}

void printField(const char *label, const char *value) {
    setColor(14);
    printf("  %-16s", label);
    setColor(7);
    printf(": ");
    setColor(15);
    printf("%s\n", value);
    setColor(7);
    fflush(stdout);
}

void printSuccess(const char *msg) {
    printf("\n");
    setColor(10);
    printf("  [OK] %s\n", msg);
    setColor(7);
    printf("\n");
    fflush(stdout);
}

void printError(const char *msg) {
    printf("\n");
    setColor(12);
    printf("  [!] %s\n", msg);
    setColor(7);
    printf("\n");
    fflush(stdout);
}

void printPrompt(const char *msg) {
    setColor(11);
    printf("  %s", msg);
    setColor(15);
    fflush(stdout);
}