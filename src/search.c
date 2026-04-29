#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "search.h"
#include "UI.h"

static void printRecord(char *record) {
    char copy[1024];
    strncpy(copy, record, sizeof(copy));
    char *token = strtok(copy, "\r\n");
    while (token != NULL) {
        if (strlen(token) > 0) {
            printf("  %s\n", token);
            fflush(stdout);
        }
        token = strtok(NULL, "\r\n");
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
                clearScreen();
                setColor(11);
                printf("\n  >> Tim theo ma BHYT <<\n\n");
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
                clearScreen();
                setColor(11);
                printf("\n  >> Tim theo ho ten <<\n\n");
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
                clearScreen();
                setColor(11);
                printf("\n  >> Tim theo so dien thoai <<\n\n");
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