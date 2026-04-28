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


    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: {
                int subChoice1;
                do {
                    showPatientMenu();
                    scanf("%d", &subChoice1);
                    getchar();
                    switch(subChoice1) {
                        case 1:
                            clearScreen();
                            setColor(10);
                            printf("\n  >> Them benh nhan moi <<\n\n");
                            Patient newPatient;
                            setColor(7);
                            getPatientInput(&newPatient);
                            saveToFile(&newPatient, "data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 2:
                            clearScreen();
                            setColor(12);
                            printf("\n  >> Xoa benh nhan <<\n\n");
                            setColor(7);
                            deletePatient("data/patient.txt");
                            pressEnterToContinue();
                            break;
                        case 3:
                            clearScreen();
                            setColor(14);
                            printf("\n  >> Sua thong tin benh nhan <<\n\n");
                            setColor(7);
                            editPatient("data/patient.txt");
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
                } while(subChoice1 != 0);
                break;
            }

            case 2: {
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

            case 3:
                clearScreen();
                setColor(10);
                printf("\n  >> Dat lich kham <<\n\n");
                setColor(7);
                
                BookingInfo booked = bookingFlow();
                
                pressEnterToContinue();
                break;

            case 4:{
               int patientChoice;
                do {
                    showchoiceMenu();
                    scanf("%d", &patientChoice);
                    getchar();
                    switch(patientChoice){
                        case 1:
                            clearScreen();
                            setColor(10);
                            printf("\n >> HUY LICH HEN <<");
                            setColor(7);
                            processDeleteAction("../data/booking.txt");
                            printf("\n DA XOA THONG TIN LICH HEN THANH CONG \n");
                            break;
                        case 2:
                            clearScreen();
                            setColor(12);
                            printf("\n >> TRA CUU LICH HEN <<\n");
                            setColor(7);
                            processAppointmentLookup("../data/booking.txt");
                            break;
                        default:
                            setColor(12);
                            printf("LUA CHON KHONG HOP LE");
                            setColor(7);
                            pressEnterToContinue();
                    } 
                }while(patientChoice != 0);
                    break;
            }
            case 5:
                clearScreen();
                setColor(10);
                printf("\n  >> Luu / Doc file <<\n\n");
                setColor(7);
                //thêm hàm lưu và đọc file ở đây
                pressEnterToContinue();
                break;

            case 0:
                clearScreen();
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
