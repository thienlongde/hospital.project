#include "UI.h"
#include <stdio.h>
#include <windows.h>
#include <stdio.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
}
// chỉnh kích thước cửa sổ và di chuyển
void setWindowSize(int width, int height){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    MoveWindow(console,r.left,r.top,width,height,TRUE);
}
//tên của cửa sổ
void setConsoleTitle(const char *title)
{
    SetConsoleTitleA(title);
}
//Hiển thị con chuột
void setCursorVisibility(int visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void pressEnterToContinue() {
    setColor(8);
    printf("\n  Nhan Enter de tiep tuc...");
    setColor(7);
    getchar();
}
void printHeader() {
    setColor(11);
    printf("╔══════════════════════════════════════╗\n");
    printf("║     He thong quan ly va dat lich     ║\n");
    printf("╚══════════════════════════════════════╝\n");
    setColor(7);
}
void printMenuOption(int num, const char* text) {
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
    printMenuOption(4, "Luu / Doc file");
    printMenuOption(0, "Thoat");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
}
void showPatientMenu() {
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
}
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
    printf("  *** XOA VA TRA CUU THONG TIN ***\n");
    setColor(7);
    printMenuOption(1, "Xoa thong tin lich hen");
    printMenuOption(2, "Tra cuu thong tin lich hen");
    printMenuOption(0, "Quay lai");
    printf("\n");
    setColor(11);
    printf("  Lua chon cua ban: ");
    setColor(15);
    fflush(stdout);
}
