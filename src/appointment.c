#include "../include/appointment.h"
#include "../include/UI.h"
#include <stdio.h>
#include <string.h>

bool isValidInfo(const char *input) {
    if (strlen(input) < 1) return false;
    return true;
}
static bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue) {
    const char *pos = strstr(record, fieldLabel);
    if (pos == NULL) return false;
    pos += strlen(fieldLabel);
    while (*pos == ' ' || *pos == '\t') pos++;
    size_t len = strcspn(pos, "\r\n");
    return (strlen(searchValue) == len && strncmp(pos, searchValue, len) == 0);
}

static bool recordMatchesKey(const char *record, const char *searchKey) {
    return fieldMatchesExact(record, "Ma BHYT:",           searchKey) ||
           fieldMatchesExact(record, "Ho va Ten :",        searchKey) ||
           fieldMatchesExact(record, "So dien thoai :",    searchKey);
}
static void printAppointmentRecord(char *record) {
    char copy[1024];
    strncpy(copy, record, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';

    char *line = copy;
    char *end;

    while ((end = strchr(line, '\n')) != NULL) {
        *end = '\0';
        if (strlen(line) > 0) {
            printf("  %s\n", line);
            fflush(stdout);
        }
        line = end + 1;
    }
    if (strlen(line) > 0) {
        printf("  %s\n", line);
        fflush(stdout);
    }
}

void searchInFile(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printError("Khong tim thay du lieu lich kham!");
        return;
    }

    char line[256], record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
           if (recordMatchesKey(record, searchKey)) {
            printSectionHeader("KET QUA TIM KIEM");
            printDivider();
            printAppointmentRecord(record);
            printDivider();
            found = true;
            break;
        }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(f);

    if (!found)
        printError("Khong co lich kham cho thong tin da nhap!");
}

void processAppointmentLookup(const char *fileName) {
    char searchKey[50];

    clearScreen();
    printHeader();
    printSectionHeader("TRA CUU LICH KHAM");
    printPrompt("Nhap BHYT, Ho ten hoac SDT: ");

    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\r\n")] = '\0';

    if (isValidInfo(searchKey)) {
        searchInFile("data/patient.txt", searchKey);
    } else {
        printError("Thong tin khong hop le!");
    }
}

void deleteAppointment(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printError("Khong tim thay du lieu nguoi dung!");
        return;
    }

    FILE *temp = fopen("data/temp.txt", "w");
    if (!temp) {
        printError("Loi he thong khi tao file tam!");
        fclose(f);
        return;
    }

    char line[256], record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), f)) {
        strcat(record, line);
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (!recordMatchesKey(record, searchKey)) {
            fputs(record, temp);
        } else {
            found = true;
        }
            record[0] = '\0';
        }
    }
    fclose(f);
    fclose(temp);
    if (found) {
        remove(fileName);
        rename("data/temp.txt", fileName);
        printSuccess("Da xoa thanh cong lich hen!");
    } else {
        remove("data/patient.txt");
        printError("Khong tim thay lich hen can xoa!");
    }
}

void processDeleteAction(const char *fileName) {
    char searchKey[50];

    clearScreen();
    printHeader();
    printSectionHeader("HUY LICH HEN KHAM BENH");
    printPrompt("Nhap ma BHYT, Ho ten hoac SDT can xoa: ");

    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\r\n")] = '\0';

    if (!isValidInfo(searchKey)) {
        printError("Thong tin nhap vao khong hop le!");
        return;
    }

    printPrompt("Xac nhan xoa (Y/N): ");
    char choice;
    scanf(" %c", &choice);
    getchar();

    if (choice == 'y' || choice == 'Y') {
        deleteAppointment("data/patient.txt", searchKey);
    } else {
        printError("Da huy bo thao tac xoa lich hen!");
    }
}