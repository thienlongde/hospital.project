#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "search.h"
#include "UI.h"

// ─────────────────────────────────────────────
//  TIỆN ÍCH NỘI BỘ
// ─────────────────────────────────────────────

// Xóa bộ đệm stdin — chống trôi lệnh nhập liệu
static void clearSearchBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Kiểm tra mã BHYT đúng 15 chữ số
static bool validateBHYT_Search(const char *bhyt) {
    if (strlen(bhyt) != 15) return false;
    for (int i = 0; i < 15; i++) {
        if (!isdigit((unsigned char)bhyt[i])) return false;
    }
    return true;
}

// ─────────────────────────────────────────────
//  SO KHỚP FIELD CHÍNH XÁC
// ─────────────────────────────────────────────
bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue) {
    const char *pos = strstr(record, fieldLabel);
    if (pos == NULL) return false;

    pos += strlen(fieldLabel);
    while (*pos == ' ' || *pos == '\t') pos++;

    size_t len = strcspn(pos, "\r\n");
    return (strlen(searchValue) == len && strncmp(pos, searchValue, len) == 0);
}

// ─────────────────────────────────────────────
//  IN RECORD ĐẸP
// ─────────────────────────────────────────────
void printRecord(const char *record) {
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

// ─────────────────────────────────────────────
//  1. TRA CỨU THEO MÃ BHYT
// ─────────────────────────────────────────────
void searchByBHYT(const char *file_Name) {
    char healthIns_Number[50];

    clearSearchBuffer();

    do {
        printf("\n--- TIM KIEM BENH NHAN THEO MA BHYT ---\n");
        printf("Hay nhap ma BHYT (yeu cau du 15 so): ");
        fflush(stdout);
        fgets(healthIns_Number, sizeof(healthIns_Number), stdin);
        healthIns_Number[strcspn(healthIns_Number, "\r\n")] = '\0';

        if (!validateBHYT_Search(healthIns_Number)) {
            setColor(12);
            printf("Loi: Ma BHYT phai gom chinh xac 15 chu so. Vui long nhap lai!\n");
            setColor(7);
        } else {
            break;
        }
    } while (true);

    FILE *patientInfo = fopen(file_Name, "r");
    if (!patientInfo) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "Ma BHYT:", healthIns_Number)) {
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                setColor(7);
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found) {
        setColor(12);
        printf("\n  Khong tim thay benh nhan voi ma BHYT: %s\n", healthIns_Number);
        setColor(7);
    }
}

// ─────────────────────────────────────────────
//  2. TRA CỨU THEO HỌ TÊN
// ─────────────────────────────────────────────
void searchByfullName(const char *file_Name) {
    char full_Name[50];

    clearSearchBuffer();

    printf("Hay nhap ho va ten cua ban: ");
    fflush(stdout);
    fgets(full_Name, sizeof(full_Name), stdin);
    full_Name[strcspn(full_Name, "\r\n")] = '\0';

    FILE *patientInfo = fopen(file_Name, "r");
    if (!patientInfo) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "Ho va Ten :", full_Name)) {
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                setColor(7);
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found) {
        setColor(12);
        printf("\n  Khong tim thay benh nhan voi ten: %s\n", full_Name);
        setColor(7);
    }
}

// ─────────────────────────────────────────────
//  3. TRA CỨU THEO SỐ ĐIỆN THOẠI
// ─────────────────────────────────────────────
void searchByPhoneNumbers(const char *file_Name) {
    char phone_Numbers[50];

    clearSearchBuffer();

    printf("Hay nhap so dien thoai cua ban: ");
    fflush(stdout);
    fgets(phone_Numbers, sizeof(phone_Numbers), stdin);
    phone_Numbers[strcspn(phone_Numbers, "\r\n")] = '\0';

    FILE *patientInfo = fopen(file_Name, "r");
    if (!patientInfo) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "So dien thoai :", phone_Numbers)) {
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                setColor(7);
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    fclose(patientInfo);

    if (!found) {
        setColor(12);
        printf("\n  Khong tim thay benh nhan voi so dien thoai: %s\n", phone_Numbers);
        setColor(7);
    }
}