#include <windows.h>
#include "patient.h"
#include "UI.h"
#include "search.h"
#include "appointment.h"
#include "booking.h"
#include "auth.h"

// ─────────────────────────────────────────────
//  Hiển thị menu tuỳ theo vai trò
// ─────────────────────────────────────────────
void showMenuByRole(const User *user) {
    clearScreen();
    setColor(11);
    printf("\n  ╔══════════════════════════════════════╗\n");
    printf("  ║   HE THONG QUAN LY DAT LICH KHAM    ║\n");
    printf("  ╠══════════════════════════════════════╣\n");
    printf("  ║  Xin chao: %-10s  [%-10s]  ║\n",
           user->username, getRoleName(user->role));
    printf("  ╠══════════════════════════════════════╣\n");
    setColor(7);

    // Mọi vai trò đều thấy
    printf("  ║  1. Tim kiem / Tra cuu lich kham     ║\n");

    if (hasPermission(user, ROLE_STAFF)) {
        // Admin + Staff
        printf("  ║  2. Dat lich kham                    ║\n");
        printf("  ║  3. Quan ly benh nhan & lich hen     ║\n");
    } else {
        // Bệnh nhân
        printf("  ║  2. Huy lich hen cua toi             ║\n");
    }

    printf("  ║  0. Thoat                            ║\n");
    printf("  ╚══════════════════════════════════════╝\n");
    setColor(14);
    printf("  >> Lua chon: ");
    setColor(7);
}

// ─────────────────────────────────────────────
//  Sub-menu Tìm kiếm (mọi vai trò)
// ─────────────────────────────────────────────
void handleSearchMenu() {
    int subChoice;
    do {
        showSearchMenu();
        scanf("%d", &subChoice);
        getchar();

        switch (subChoice) {
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
    } while (subChoice != 0);
}

// ─────────────────────────────────────────────
//  Sub-menu Quản lý (Admin / Staff)
// ─────────────────────────────────────────────
void handleManagementMenu(const User *user, Patient **patientList) {
    int patientChoice;
    do {
        clearScreen();
        setColor(11);
        printf("\n  ╔══════════════════════════════════════╗\n");
        printf("  ║       QUAN LY BENH NHAN & LICH       ║\n");
        printf("  ╠══════════════════════════════════════╣\n");
        setColor(7);
        printf("  ║  1. Huy lich hen                     ║\n");
        printf("  ║  2. Tra cuu lich hen                 ║\n");

        if (hasPermission(user, ROLE_ADMIN)) {
            printf("  ║  3. Xoa thong tin benh nhan [ADMIN]  ║\n");
            printf("  ║  4. Sua thong tin benh nhan [ADMIN]  ║\n");
        }

        printf("  ║  0. Quay lai                         ║\n");
        printf("  ╚══════════════════════════════════════╝\n");
        setColor(14);
        printf("  >> Lua chon: ");
        setColor(7);

        scanf("%d", &patientChoice);
        getchar();

        switch (patientChoice) {
            case 1:
                clearScreen();
                setColor(10);
                printf("\n  >> HUY LICH HEN <<\n");
                setColor(7);
                processDeleteAction("data/patient.txt", user);
                pressEnterToContinue();
                break;

            case 2:
                clearScreen();
                setColor(12);
                printf("\n  >> TRA CUU LICH HEN <<\n");
                setColor(7);
                processAppointmentLookup("data/patient.txt");
                pressEnterToContinue();
                break;

            case 3:
                if (!hasPermission(user, ROLE_ADMIN)) {
                    setColor(12);
                    printf("\n  [TU CHOI] Chi Admin moi co quyen xoa benh nhan!\n");
                    setColor(7);
                    pressEnterToContinue();
                    break;
                }
                clearScreen();
                setColor(12);
                printf("\n  >> XOA THONG TIN BENH NHAN <<\n");
                setColor(7);
                {
                    Patient *head = loadListFromFile("data/patient.txt");
                    deletePatient(&head, "data/patient.txt");
                }
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
    } while (patientChoice != 0);
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
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

    // ── ĐĂNG NHẬP HOẶC ĐĂNG KÝ ──────────────────────────────
    int authChoice = 0;
    do {
        clearScreen();
        setColor(11);
        printf("\n  ╔══════════════════════════════════════╗\n");
        printf("  ║   HE THONG QUAN LY DAT LICH KHAM    ║\n");
        printf("  ╚══════════════════════════════════════╝\n");
        setColor(7);
        printf("  ║  1. Dang nhap                        ║\n");
        printf("  ║  2. Dang ky tai khoan (Benh nhan)    ║\n");
        printf("  ║  0. Thoat                            ║\n");
        setColor(14);
        printf("  >> Lua chon: ");
        setColor(7);
        scanf("%d", &authChoice);
        getchar();

        if (authChoice == 1) {
            break;  // Proceed to login
        } else if (authChoice == 2) {
            clearScreen();
            signupPatient("data/users.txt");
            pressEnterToContinue();
        } else if (authChoice == 0) {
            return 0;
        } else {
            setColor(12);
            printf("  [!] Lua chon khong hop le!\n");
            setColor(7);
            pressEnterToContinue();
        }
    } while (authChoice != 1);

    // ── ĐĂNG NHẬP ──────────────────────────────
    User currentUser = {0};
    if (!loginUser("data/users.txt", &currentUser)) {
        setColor(12);
        printf("\n  [!] Dang nhap that bai. Thoat chuong trinh.\n");
        setColor(7);
        Sleep(2000);
        return 1;
    }

    // ── LOAD DỮ LIỆU ───────────────────────────
    Patient *patientList = loadListFromFile("data/patient.txt");

    int choice;
    do {
        showMenuByRole(&currentUser);
        scanf("%d", &choice);
        getchar();

        if (currentUser.role == ROLE_PATIENT) {
            // ── BỆNH NHÂN ───────────────────────
            switch (choice) {
                case 1:
                    handleSearchMenu();
                    break;
                case 2:
                    clearScreen();
                    setColor(10);
                    printf("\n  >> HUY LICH HEN CUA TOI <<\n");
                    setColor(7);
                    processDeleteAction("data/patient.txt", &currentUser);
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
        } else {
            // ── ADMIN / STAFF ────────────────────
            switch (choice) {
                case 1:
                    handleSearchMenu();
                    break;
                case 2:
                    clearScreen();
                    setColor(10);
                    printf("\n  >> DAT LICH KHAM <<\n\n");
                    setColor(7);
                    Sleep(100);
                    clearScreen();
                    bookingFlow(&patientList);
                    pressEnterToContinue();
                    break;
                case 3:
                    handleManagementMenu(&currentUser, &patientList);
                    break;
                case 0:
                    break;
                default:
                    setColor(12);
                    printf("\n  [!] Lua chon khong hop le, vui long chon lai!\n");
                    setColor(7);
                    pressEnterToContinue();
            }
        }

    } while (choice != 0);

    clearScreen();
    freeList(&patientList);
    Sleep(1500);
    system("pause");
    return 0;
}