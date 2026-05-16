#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/booking.h"
#include "../include/patient.h"
#include "../include/UI.h"

/*
 * DONG BO STRUCT BookingInfo (trong booking.h):
 *   char department[100];
 *   char packageName[100];
 *   char doctor[50];
 *   char date[30];
 *   char time[20];
 * Phai khop voi format fscanf %99 %99 %49 %29 %19
 */

/* --- Hang so slot dung chung --- */
static const char *ALL_SLOTS[] = {
    "08:00","09:00","10:00","11:00",
    "14:00","15:00","16:00","17:00"
};
#define TOTAL_SLOTS 8

/* ============================================================
   HELPER: Ve duong ke ngang
   ============================================================ */
void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) putchar(ch);
    putchar('\n');
}

/* ============================================================
   HELPER: In tieu de co vien box
   ============================================================ */
void printBoxTitle(const char *title, int color) {
    int width = 46;
    setColor(color);
    printf("  +");
    printLine('-', width);
    int pad = (width - (int)strlen(title)) / 2;
    printf("  |%*s%s%*s|\n", pad, "", title, width - pad - (int)strlen(title), "");
    printf("  +");
    printLine('-', width);
    setColor(7);
}

/* ============================================================
   HELPER: Loading animation don gian
   ============================================================ */
void loadingDots(const char *msg, int color) {
    setColor(color);
    printf("\n  %s", msg);
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        printf(".");
        fflush(stdout);
    }
    setColor(7);
    printf("\n");
}

/* ============================================================
   HELPER: flush stdin an toan
   ============================================================ */
void flushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
   displayDepartment
   ============================================================ */
void displayDepartment(void) {
    setColor(14);
    printBoxTitle("DANH SACH CHUYEN KHOA", 14);
    setColor(11);
    printf("  |  1. Rang ham mat                            |\n");
    printf("  |  2. Da lieu                                 |\n");
    printf("  |  3. Tong quat                               |\n");
    printf("  +----------------------------------------------+\n");
    setColor(7);
}

/* ============================================================
   displayPackage
   ============================================================ */
void displayPackage(char department[]) {
    setColor(14);
    printBoxTitle("DANH SACH GOI KHAM", 14);
    setColor(11);

    if (strcmp(department, "Rang ham mat") == 0) {
        printf("  |  1. Kham rang tong quat                     |\n");
        printf("  |  2. Phau thuat nho rang khon, chinh ham lech|\n");
        printf("  |  3. Trong rang, boc rang su, nieng rang     |\n");
    } else if (strcmp(department, "Da lieu") == 0) {
        printf("  |  1. Kham da lieu tong quat                  |\n");
        printf("  |  2. Dieu tri mun                            |\n");
        printf("  |  3. Phau thuat tham my                      |\n");
    } else if (strcmp(department, "Tong quat") == 0) {
        printf("  |  1. Kham lam san                            |\n");
        printf("  |  2. Xet nghiem                              |\n");
    }

    printf("  +----------------------------------------------+\n");
    setColor(7);
}

/* ============================================================
   displayPackageDetail
   ============================================================ */
void displayPackageDetail(char packageName[]) {
    setColor(14);
    printBoxTitle("CHI TIET GOI KHAM", 14);

    typedef struct { const char *name; const char *price; const char *desc; const char *doctor; } PkgInfo;
    PkgInfo packages[] = {
        {"Kham rang tong quat",
         "200.000 VND",
         "Kiem tra rang mieng, chup X-quang, tu van",
         "BS. Nguyen Van An"},
        {"Phau thuat nho rang khon, chinh ham lech",
         "1.500.000 - 4.000.000 VND/rang",
         "Nho rang khon moc lech bang may Piezotome",
         "BS. Tran Thi Binh"},
        {"Trong rang, boc rang su, nieng rang",
         "10.000.000 - 50.000.000 VND",
         "Phuc hinh rang su, cam ghep Implant, nieng rang",
         "BS. Le Hoang Nam"},
        {"Kham da lieu tong quat",
         "350.000 VND",
         "Soi da so, chan doan benh ly da, toc, mong",
         "BS. Pham Minh Thu"},
        {"Dieu tri mun",
         "700.000 VND/buoi",
         "Lay nhan mun chuan y khoa, chieu anh sang sinh hoc",
         "BS. Do Duc Manh"},
        {"Phau thuat tham my",
         "5.000.000 - 20.000.000 VND",
         "Cat mi, nang mui, xoa nep nhan, tham lan toi thieu",
         "BS. Vu Phuong Thao"},
        {"Kham lam san",
         "150.000 VND",
         "Kiem tra huyet ap, can nang, chieu cao, noi khoa",
         "BS. Hoang Van Minh"},
        {"Xet nghiem",
         "800.000 VND",
         "Cong thuc mau, duong huyet, chuc nang gan va than",
         "BS. Dang Quoc Bao"},
    };

    int found = 0;
    int i;
    for (i = 0; i < (int)(sizeof(packages)/sizeof(packages[0])); i++) {
        if (strcmp(packageName, packages[i].name) == 0) {
            char buf[200];
            int maxW = 34;

            setColor(10);
            strncpy(buf, packages[i].name, maxW); buf[maxW] = '\0';
            printf("  | Goi     : %-34s |\n", buf);
            if ((int)strlen(packages[i].name) > maxW)
                printf("  |           %-34s |\n", packages[i].name + maxW);

            setColor(13);
            strncpy(buf, packages[i].price, maxW); buf[maxW] = '\0';
            printf("  | Gia     : %-34s |\n", buf);
            if ((int)strlen(packages[i].price) > maxW)
                printf("  |           %-34s |\n", packages[i].price + maxW);

            setColor(7);
            strncpy(buf, packages[i].desc, maxW); buf[maxW] = '\0';
            printf("  | Mo ta   : %-34s |\n", buf);
            if ((int)strlen(packages[i].desc) > maxW)
                printf("  |           %-34s |\n", packages[i].desc + maxW);

            setColor(11);
            strncpy(buf, packages[i].doctor, maxW); buf[maxW] = '\0';
            printf("  | Bac si  : %-34s |\n", buf);

            found = 1;
            break;
        }
    }
    if (!found) {
        setColor(12);
        printf("  | Khong tim thay thong tin goi kham!          |\n");
    }
    setColor(14);
    printf("  +----------------------------------------------+\n");
    setColor(7);
}

/* ============================================================
   isDuplicateBooking
   Tra ve 1 neu bac si da co lich vao ngay+gio do, 0 neu ranh.
   Logic: 1 bac si + 1 gio = 1 lich duy nhat.
   ============================================================ */
int isDuplicateBooking(BookingInfo info) {
    FILE *f = fopen("booking.txt", "r");
    if (f == NULL) return 0;

    BookingInfo temp;
    while (fscanf(f, " %99[^|]|%99[^|]|%49[^|]|%29[^|]|%19[^\n]",
                  temp.department, temp.packageName,
                  temp.doctor, temp.date, temp.time) == 5) {
        if (strcmp(temp.doctor, info.doctor) == 0 &&
            strcmp(temp.date,   info.date)   == 0 &&
            strcmp(temp.time,   info.time)   == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/* ============================================================
   displayAvailableSlot
   Hien thi cac gio ma bac si cu the con ranh trong ngay do.
   ============================================================ */
void displayAvailableSlot(char doctor[], char date[]) {
    int idx = 1;

    setColor(14);
    printBoxTitle("GIO KHAM CON TRONG", 14);

    int anySlot = 0;
    BookingInfo tmp;
    strncpy(tmp.doctor, doctor, sizeof(tmp.doctor)-1); tmp.doctor[sizeof(tmp.doctor)-1] = '\0';
    strncpy(tmp.date,   date,   sizeof(tmp.date)-1);   tmp.date[sizeof(tmp.date)-1]     = '\0';
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        strncpy(tmp.time, ALL_SLOTS[i], sizeof(tmp.time)-1); tmp.time[sizeof(tmp.time)-1] = '\0';
        if (!isDuplicateBooking(tmp)) {
            setColor(10);
            printf("  |  %d. %-41s|\n", idx++, ALL_SLOTS[i]);
            anySlot = 1;
        }
    }
    if (!anySlot) {
        setColor(12);
        printf("  |  Bac si nay da het gio trong cho ngay nay! |\n");
    }
    setColor(14);
    printf("  +----------------------------------------------+\n");
    setColor(7);
}

/* ============================================================
   saveBookingToFile  — ghi 1 dong vao booking.txt
   ============================================================ */
void saveBookingToFile(BookingInfo info) {
    FILE *f = fopen("booking.txt", "a");
    if (f == NULL) {
        setColor(12);
        printf("  [LOI] Khong the mo file booking.txt!\n");
        setColor(7);
        return;
    }
    fprintf(f, "%s|%s|%s|%s|%s\n",
            info.department, info.packageName,
            info.doctor, info.date, info.time);
    fclose(f);
}

/* ============================================================
   executeBookingProcess  — man hinh xac nhan + luu
   ============================================================ */
void executeBookingProcess(BookingInfo info, Patient *patient,
                           Patient **patientList, char *file_Name) {
    if (strlen(info.date) == 0) {
        setColor(12);
        printf("\n  [LOI] Du lieu dat lich khong hop le!\n");
        setColor(7);
        return;
    }

    /* Kiem tra bac si co bi trung gio khong */
    if (isDuplicateBooking(info)) {
        setColor(12);
        printBoxTitle("! TRUNG LICH !", 12);
        printf("  Bac si %-20s da co hen\n", info.doctor);
        printf("  vao luc %s ngay %s.\n", info.time, info.date);
        printf("  Vui long chon khung gio khac!\n");
        setColor(7);
        return;
    }

    /* --- Man hinh xac nhan --- */
    setColor(14);
    printf("\n");
    printBoxTitle("XAC NHAN DAT LICH", 14);

    #define PRINT_ROW(label, value, color) \
        do { \
            char _buf[200]; \
            setColor(color); \
            strncpy(_buf, (value), 32); _buf[32] = '\0'; \
            printf("  | " label ": %-32s|\n", _buf); \
            if ((int)strlen(value) > 32) \
                printf("  |              %-32s|\n", (value) + 32); \
            setColor(7); \
        } while(0)

    PRINT_ROW("Ho va ten  ", patient->fullName,              7);
    PRINT_ROW("Ma BHYT    ", patient->healthInsuranceNumbers, 7);
    PRINT_ROW("So DT      ", patient->phoneNumbers,           7);
    setColor(14);
    printf("  +----------------------------------------------+\n");
    PRINT_ROW("Chuyen khoa", info.department,  7);
    PRINT_ROW("Goi kham   ", info.packageName, 7);
    PRINT_ROW("Bac si     ", info.doctor,      7);
    setColor(10);
    printf("  | Thoi gian  : %-7s | %-22s|\n", info.time, info.date);
    setColor(14);
    printf("  +----------------------------------------------+\n");
    #undef PRINT_ROW
    setColor(7);

    printf("\n  Ban co chac chan muon dat lich? (Y/N): ");
    char confirmation;
    scanf(" %c", &confirmation);
    flushStdin();

    if (confirmation == 'Y' || confirmation == 'y') {
        loadingDots("  [1/2] Dang luu du lieu", 11);
        patient->booking = info;
        saveBookingToFile(info);
        saveListToFile(*patientList, file_Name);

        loadingDots("  [2/2] Dang cap nhat lich bac si", 11);

        setColor(10);
        printf("\n  +----------------------------------------------+\n");
        printf("  |       >>> DAT LICH THANH CONG! <<<           |\n");
        printf("  +----------------------------------------------+\n");
        setColor(7);
    } else {
        setColor(12);
        printf("\n  [HUY] Nguoi dung da huy xac nhan.\n");
        setColor(7);
    }
}

/* ============================================================
   bookingFlow  — luong chinh dat lich
   ============================================================ */
BookingInfo bookingFlow(Patient **patientList) {
    clearScreen();
    BookingInfo info;
    memset(&info, 0, sizeof(info));

    /* --- Nhap ma BHYT --- */
    setColor(14);
    printBoxTitle("DAT LICH KHAM BENH", 14);
    setColor(7);

    char healthIns_Num[50];
    printf("\n  Nhap ma BHYT: ");
    fgets(healthIns_Num, sizeof(healthIns_Num), stdin);
    healthIns_Num[strcspn(healthIns_Num, "\n")] = '\0';

    /* --- Tim benh nhan --- */
    Patient *found = NULL;
    for (Patient *cur = *patientList; cur; cur = cur->next) {
        if (strcmp(cur->healthInsuranceNumbers, healthIns_Num) == 0) {
            found = cur;
            break;
        }
    }

    if (!found) {
        setColor(12);
        printf("\n  Khong tim thay benh nhan voi ma BHYT: %s\n", healthIns_Num);
        setColor(7);

        char confirm;
        printf("  Ban co muon them benh nhan moi khong? (Y/N): ");
        scanf(" %c", &confirm);
        flushStdin();

        if (confirm == 'Y' || confirm == 'y') {
            Patient *newPatient = (Patient*)malloc(sizeof(Patient));
            if (!newPatient) {
                setColor(12);
                printf("  [LOI] Khong du bo nho!\n");
                setColor(7);
                return info;
            }
            newPatient->next = NULL;
            memset(&newPatient->booking, 0, sizeof(newPatient->booking));
            getPatientInput(newPatient);

            if (!*patientList) {
                *patientList = newPatient;
            } else {
                Patient *cur = *patientList;
                while (cur->next) cur = cur->next;
                cur->next = newPatient;
            }
            saveListToFile(*patientList, "data/patient.txt");
            setColor(10);
            printf("\n  Da them benh nhan moi thanh cong!\n\n");
            setColor(7);
            Sleep(1000);
            clearScreen();
            found = newPatient;
        } else {
            setColor(12);
            printf("  Da huy. Quay lai menu chinh.\n");
            setColor(7);
            return info;
        }
    }

    setColor(10);
    printf("\n  Xin chao, %s!\n\n", found->fullName);
    setColor(7);

    /* --- Chon chuyen khoa --- */
    displayDepartment();
    int departmentChoice;
    printf("\n  Chon chuyen khoa (1-3): ");
    if (scanf("%d", &departmentChoice) != 1) { flushStdin(); return info; }
    flushStdin();

    switch (departmentChoice) {
        case 1: strncpy(info.department, "Rang ham mat", sizeof(info.department)-1); break;
        case 2: strncpy(info.department, "Da lieu",      sizeof(info.department)-1); break;
        case 3: strncpy(info.department, "Tong quat",    sizeof(info.department)-1); break;
        default:
            setColor(12);
            printf("  Lua chon chuyen khoa khong hop le!\n");
            setColor(7);
            return info;
    }
    info.department[sizeof(info.department)-1] = '\0';

    /* --- Chon goi kham --- */
    displayPackage(info.department);
    int packageChoice;
    printf("\n  Chon goi kham: ");
    if (scanf("%d", &packageChoice) != 1) { flushStdin(); return info; }
    flushStdin();

    typedef struct { const char *pkg; const char *doc; } PkgDoc;
    PkgDoc map[3][3] = {
        {{"Kham rang tong quat","BS. Nguyen Van An"},
         {"Phau thuat nho rang khon, chinh ham lech","BS. Tran Thi Binh"},
         {"Trong rang, boc rang su, nieng rang","BS. Le Hoang Nam"}},
        {{"Kham da lieu tong quat","BS. Pham Minh Thu"},
         {"Dieu tri mun","BS. Do Duc Manh"},
         {"Phau thuat tham my","BS. Vu Phuong Thao"}},
        {{"Kham lam san","BS. Hoang Van Minh"},
         {"Xet nghiem","BS. Dang Quoc Bao"},
         {NULL, NULL}}
    };

    int depIdx = departmentChoice - 1;
    int maxPkg = (depIdx == 2) ? 2 : 3;

    if (packageChoice < 1 || packageChoice > maxPkg || map[depIdx][packageChoice-1].pkg == NULL) {
        setColor(12);
        printf("  Lua chon goi kham khong hop le!\n");
        setColor(7);
        return info;
    }

    strncpy(info.packageName, map[depIdx][packageChoice-1].pkg, sizeof(info.packageName)-1);
    info.packageName[sizeof(info.packageName)-1] = '\0';
    strncpy(info.doctor,      map[depIdx][packageChoice-1].doc, sizeof(info.doctor)-1);
    info.doctor[sizeof(info.doctor)-1] = '\0';

    displayPackageDetail(info.packageName);

    /* --- Nhap ngay kham voi kiem tra hop le --- */
    while (1) {
        printf("\n  Nhap ngay kham (dd/mm/yyyy): ");
        fgets(info.date, sizeof(info.date), stdin);
        info.date[strcspn(info.date, "\n")] = '\0';

        int dd, mm, yyyy;
        if (strlen(info.date) != 10 ||
            sscanf(info.date, "%2d/%2d/%4d", &dd, &mm, &yyyy) != 3) {
            setColor(12);
            printf("  [LOI] Dinh dang sai! Vui long nhap dd/mm/yyyy.\n");
            setColor(7);
            continue;
        }

        if (mm < 1 || mm > 12) {
            setColor(12);
            printf("  [LOI] Thang khong hop le (1-12).\n");
            setColor(7);
            continue;
        }

        int isLeap = (yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0);
        int daysInMonth[] = {31, isLeap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxDay = daysInMonth[mm - 1];

        if (dd < 1 || dd > maxDay) {
            setColor(12);
            printf("  [LOI] Ngay %d khong ton tai trong thang %d/%d (toi da %d ngay).\n",
                   dd, mm, yyyy, maxDay);
            setColor(7);
            continue;
        }

        if (yyyy < 2000 || yyyy > 2100) {
            setColor(12);
            printf("  [LOI] Nam khong hop le (2000-2100).\n");
            setColor(7);
            continue;
        }

        SYSTEMTIME st;
        GetLocalTime(&st);
        int todayVal = st.wYear * 10000 + st.wMonth * 100 + st.wDay;
        int inputVal = yyyy    * 10000 + mm       * 100 + dd;
        if (inputVal < todayVal) {
            setColor(12);
            printf("  [LOI] Khong the dat lich ngay trong qua khu!\n");
            setColor(7);
            continue;
        }

        setColor(10);
        printf("  [OK] Ngay hop le: %02d/%02d/%04d\n", dd, mm, yyyy);
        setColor(7);
        sprintf(info.date, "%02d/%02d/%04d", dd, mm, yyyy);
        break;
    }

    /* --- Chon gio kham --- */
    /* Hien thi gio con trong theo bac si va ngay da chon */
    displayAvailableSlot(info.doctor, info.date);

    /* Build mang cac gio con ranh cua bac si nay */
    const char *availSlots[TOTAL_SLOTS];
    int availCount = 0;
    BookingInfo tmp;
    strncpy(tmp.doctor, info.doctor, sizeof(tmp.doctor)-1); tmp.doctor[sizeof(tmp.doctor)-1] = '\0';
    strncpy(tmp.date,   info.date,   sizeof(tmp.date)-1);   tmp.date[sizeof(tmp.date)-1]     = '\0';
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        strncpy(tmp.time, ALL_SLOTS[i], sizeof(tmp.time)-1); tmp.time[sizeof(tmp.time)-1] = '\0';
        if (!isDuplicateBooking(tmp))
            availSlots[availCount++] = ALL_SLOTS[i];
    }

    if (availCount == 0) {
        setColor(12);
        printf("\n  Bac si nay da het gio trong cho ngay nay! Vui long chon ngay khac.\n");
        setColor(7);
        return info;
    }

    int timeChoice;
    printf("\n  Chon gio kham (1-%d): ", availCount);
    if (scanf("%d", &timeChoice) != 1) { flushStdin(); return info; }
    flushStdin();

    if (timeChoice < 1 || timeChoice > availCount) {
        setColor(12);
        printf("  Lua chon gio khong hop le!\n");
        setColor(7);
        return info;
    }

    strncpy(info.time, availSlots[timeChoice - 1], sizeof(info.time)-1);
    info.time[sizeof(info.time)-1] = '\0';

    /* --- Xac nhan va luu --- */
    executeBookingProcess(info, found, patientList, "data/patient.txt");

    return info;
}