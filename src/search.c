#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "search.h"
#include "../include/UI.h"

// -------------------------------------------------------
// Validation
// -------------------------------------------------------
static bool isValidBHYT(const char *input) {
    if (strlen(input) < 1) return false;
    for (int i = 0; input[i]; i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

static bool isValidName(const char *input) {
    if (strlen(input) < 2) return false;
    for (int i = 0; input[i]; i++) {
        // chỉ cho phép chữ cái và khoảng trắng
        if (!isalpha((unsigned char)input[i]) && input[i] != ' ') return false;
    }
    return true;
}

static bool isValidPhone(const char *input) {
    if (strlen(input) < 9 || strlen(input) > 11) return false;
    for (int i = 0; input[i]; i++) {
        if (!isdigit(input[i])) return false;
    }
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

static void printRecord(char *record) {
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

void searchByBHYT(const char *file_Name) {
    char healthIns_Number[50];
    printPrompt("Hay nhap ma BHYT cua ban: ");
    fgets(healthIns_Number, sizeof(healthIns_Number), stdin);
    healthIns_Number[strcspn(healthIns_Number, "\r\n")] = '\0';

    if (!isValidBHYT(healthIns_Number)) {
        printError("Ma BHYT chi duoc chua so! Vui long nhap lai.");
        return;
    }

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printError("Loi: khong mo duoc file!"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "Ma BHYT:", healthIns_Number)) {
                printSectionHeader("KET QUA TIM KIEM");
                printDivider();
                printRecord(record);
                printDivider();
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found)
        printError("Khong tim thay benh nhan voi ma BHYT da nhap!");
}

// -------------------------------------------------------
// searchByfullName
// -------------------------------------------------------
void searchByfullName(const char *file_Name) {
    char full_Name[50];
    printPrompt("Hay nhap ho va ten cua ban: ");
    fgets(full_Name, sizeof(full_Name), stdin);
    full_Name[strcspn(full_Name, "\r\n")] = '\0';

    if (!isValidName(full_Name)) {
        printError("Ho ten chi duoc chua chu cai va khoang trang! Vui long nhap lai.");
        return;
    }

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printError("Loi: khong mo duoc file!"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "Ho va Ten :", full_Name)) {
                printSectionHeader("KET QUA TIM KIEM");
                printDivider();
                printRecord(record);
                printDivider();
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found)
        printError("Khong tim thay benh nhan voi ten da nhap!");
}

// -------------------------------------------------------
// searchByPhoneNumbers
// -------------------------------------------------------
void searchByPhoneNumbers(const char *file_Name) {
    char phone_Numbers[50];
    printPrompt("Hay nhap so dien thoai cua ban: ");
    fgets(phone_Numbers, sizeof(phone_Numbers), stdin);
    phone_Numbers[strcspn(phone_Numbers, "\r\n")] = '\0';

    if (!isValidPhone(phone_Numbers)) {
        printError("So dien thoai chi duoc chua so va tu 9-11 ky tu! Vui long nhap lai.");
        return;
    }

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printError("Loi: khong mo duoc file!"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "So dien thoai :", phone_Numbers)) {
                printSectionHeader("KET QUA TIM KIEM");
                printDivider();
                printRecord(record);
                printDivider();
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found)
        printError("Khong tim thay benh nhan voi so dien thoai da nhap!");
}