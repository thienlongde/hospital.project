#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "search.h"
#include "UI.h"
static bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue) {
    const char *pos = strstr(record, fieldLabel);
    if (pos == NULL) return false;

    // Nhảy qua label để tới value
    pos += strlen(fieldLabel);

    // Bỏ qua khoảng trắng
    while (*pos == ' ' || *pos == '\t') pos++;

    // So sánh value, kết thúc tại \r hoặc \n
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
    printf("Hay nhap ma BHYT cua ban: ");
    fflush(stdout);
    fgets(healthIns_Number, sizeof(healthIns_Number), stdin);
    healthIns_Number[strcspn(healthIns_Number, "\r\n")] = '\0';

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (strstr(record, healthIns_Number) != NULL) {
                setColor(11);
                printf("\n  >> Tim theo ma BHYT <<\n\n");
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                fflush(stdout);
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                fflush(stdout);
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
void searchByfullName(const char *file_Name) {
    char full_Name[50];
    printf("Hay nhap ho va ten cua ban: ");
    fflush(stdout);
    fgets(full_Name, sizeof(full_Name), stdin);
    full_Name[strcspn(full_Name, "\r\n")] = '\0';

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (strstr(record, full_Name) != NULL) {
                setColor(11);
                printf("\n  >> Tim theo ho ten <<\n\n");
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                fflush(stdout);
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                fflush(stdout);
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
        fflush(stdout);
        setColor(7);
    }
}   

void searchByPhoneNumbers(const char *file_Name) {
    char phone_Numbers[50];
    printf("Hay nhap so dien thoai cua ban: ");
    fflush(stdout);
    fgets(phone_Numbers, sizeof(phone_Numbers), stdin);
    phone_Numbers[strcspn(phone_Numbers, "\r\n")] = '\0';

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (strstr(record, phone_Numbers) != NULL) {
                setColor(11);
                printf("\n  >> Tim theo so dien thoai <<\n\n");
                setColor(10);
                printf("  Tim thay benh nhan:\n");
                printf("  ----------------------------\n");
                fflush(stdout);
                setColor(15);
                printRecord(record);
                setColor(10);
                printf("  ----------------------------\n");
                fflush(stdout);
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
        fflush(stdout);
        setColor(7);
    }
}