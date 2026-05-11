#include <windows.h>
#include "patient.h"
#include "UI.h"
#include "search.h"
#include "appointment.h"
#include "booking.h"

int main() {
    FreeConsole();
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    setConsoleTitle("He Thong Quan Ly va Dat Lich Kham");
    setWindowSize(700, 500);
    setCursorVisibility(1);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setvbuf(stdout, NULL, _IONBF, 0);

    Patient *patientList = loadListFromFile("data/patient.txt");

    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: {
                int subChoice;
                do {
                    showSearchMenu();
                    scanf("%d", &subChoice);
                    getchar();
                    switch(subChoice) {
                        case 1:
                            clearScreen();
                            setColor(11);
                            printf("\n  >> Tim theo ma BHYT <<\n\n");
                            setColor(7);
                            searchByBHYT("data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 2:
                            clearScreen();
                            setColor(11);
                            printf("\n  >> Tim theo so dien thoai <<\n\n");
                            setColor(7);
                            searchByPhoneNumbers("data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 3:
                            clearScreen();
                            setColor(11);
                            printf("\n  >> Tim theo ho ten <<\n\n");
                            setColor(7);
                            searchByfullName("data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 0:
                            break;
                        default:
                            setColor(12);
                            printf("\n  [!] Lua chon khong hop le!\n");
                            setColor(7);
                            pressEnterToContinue();
                    }
                } while(subChoice != 0);
                break;
                }

                case 2: {
                clearScreen();
                setColor(10);
                printf("\n  >> Dat lich kham <<\n\n");
                setColor(7);
                Sleep(100);
                clearScreen();
                BookingInfo booked = bookingFlow(&patientList);
                pressEnterToContinue();
                break;
                }

            case 3: {
                int patientChoice;
                do {
                    showchoiceMenu();
                    scanf("%d", &patientChoice);
                    getchar();
                    switch(patientChoice) {
                        case 1:
                            clearScreen();
                            setColor(10);
                            printf("\n >> HUY LICH HEN <<");
                            setColor(7);
                            processDeleteAction("data/patient.txt");
                            printf("\n DA XOA THONG TIN LICH HEN THANH CONG \n");
                            pressEnterToContinue();
                            break;
                        case 2:
                            clearScreen();
                            setColor(12);
                            printf("\n >> TRA CUU LICH HEN <<\n");
                            setColor(7);
                            processAppointmentLookup("data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 3:
                            clearScreen();
                            setColor(12);
                            printf("\n >> XOA THONG TIN BENH NHAN <<\n");
                            setColor(7);
                            Patient *head = loadListFromFile("data/patient.txt");
                            deletePatient(&head, "data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 4:
                            clearScreen();
                            setColor(12);
                            printf("\n >> SUA THONG TIN BENH NHAN <<\n");
                            setColor(7);
                            editPatient(&head, "data/patient.txt");
                            pressEnterToContinue();
                            break;
                        default:
                            setColor(12);
                            printf("LUA CHON KHONG HOP LE");
                            setColor(7);
                            pressEnterToContinue();
                    }
                } while(patientChoice != 0);
                break;
            }

            case 4:
                clearScreen();
                setColor(10);
                printf("\n  >> Luu / Doc file <<\n\n");
                setColor(7);
                // thêm hàm lưu và đọc file ở đây
                pressEnterToContinue();
                break;

            case 0:
                clearScreen();
                freeList(&patientList);
                Sleep(1500);
                break;

            default:
                setColor(12);
                printf("\n  [!] Lua chon khong hop le, vui long chon lai!\n");
                setColor(7);
                pressEnterToContinue();
        }

    } while(choice != 0);

    system("pause");
    return 0;
}