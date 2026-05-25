#include "appointment.h"
#include "auth.h"
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ─────────────────────────────────────────────
//  KIỂM TRA ĐỊNH DẠNG ĐẦU VÀO
// ─────────────────────────────────────────────
bool isValidInfo(const char *input) {
    int len = strlen(input);

    if (len < 2) return false;

    bool isAllDigits = true;
    bool isAllAlpha  = true;

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            isAllDigits = false;
        }
        if (!isalpha((unsigned char)input[i]) && input[i] != ' ') {
            if (ispunct((unsigned char)input[i])) {
                isAllAlpha = false;
            }
        }
    }

    // Số điện thoại
    if (isAllDigits) {
        if (len == 10 || len == 11) return true;
        printf("=> [LOI] So dien thoai phai co 10 hoac 11 chu so!\n");
        return false;
    }

    // Mã BHYT
    if (len == 15) return true;

    // Họ tên
    if (isAllAlpha) return true;

    printf("=> [LOI] Dinh dang khong hop le (Ten, SDT 10-11 so, hoac BHYT 15 ky tu)!\n");
    return false;
}

// ─────────────────────────────────────────────
//  TÌM KIẾM TRONG FILE
// ─────────────────────────────────────────────
void searchInFile(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Loi: Khong tim thay du lieu kham benh!\n");
        return;
    }

    char line[256], record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "----------------------------\n") == 0) {
            if (strstr(record, searchKey)) {
                printf("\n[ KET QUA TIM THAY ]\n%s----------------------------\n", record);
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    if (!found) printf("=> Khong co lich kham cho: %s\n", searchKey);
    fclose(f);
}

// ─────────────────────────────────────────────
//  TRA CỨU LỊCH KHÁM
// ─────────────────────────────────────────────
void processAppointmentLookup(const char *fileName) {
    char searchKey[50];

    printf("\n--- HE THONG TRA CUU LICH KHAM ---\n");
    printf("Nhap BHYT (15 ky tu), Ho ten hoac SDT (10-11 so): ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = '\0';

    if (isValidInfo(searchKey)) {
        searchInFile(fileName, searchKey);
    } else {
        printf("Thong tin khong hop le. Ket thuc tra cuu!\n");
    }
}

// ─────────────────────────────────────────────
//  KIỂM TRA BỆNH NHÂN TỒN TẠI
// ─────────────────────────────────────────────
bool isPatientExist(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) return false;

    char line[256];
    char patientBlock[2048] = "";
    bool found = false;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Chuyen khoa", 11) == 0) break;
        strcat(patientBlock, line);
    }

    if (strstr(patientBlock, searchKey) != NULL) found = true;

    fclose(f);
    return found;
}

// ─────────────────────────────────────────────
//  XÓA LỊCH HẸN KHỎI FILE
// ─────────────────────────────────────────────
void deleteAppointment(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Loi khi mo file du lieu\n");
        return;
    }

    FILE *temp = fopen("temp_test.txt", "w");
    if (!temp) {
        printf("Loi he thong khi tao file tam\n");
        fclose(f);
        return;
    }

    char line[256];
    char patientInfo[1024]     = "";
    char appointmentInfo[1024] = "";
    bool foundAppointment      = false;
    int  appointmentDeletedCount = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Chuyen khoa", 11) == 0) {
            appointmentInfo[0] = '\0';
            strcat(appointmentInfo, line);
            foundAppointment = true;
        }
        else if (strncmp(line, "----------------------------\n", 28) == 0) {
            if (foundAppointment) {
                strcat(appointmentInfo, line);

                if (strstr(patientInfo, searchKey) != NULL) {
                    // XÓA lịch hẹn — chỉ giữ lại thông tin bệnh nhân
                    fputs(patientInfo, temp);
                    fputs(line, temp);
                    appointmentDeletedCount++;
                } else {
                    // GIỮ lịch hẹn nguyên vẹn
                    fputs(patientInfo, temp);
                    fputs(appointmentInfo, temp);
                }
            }

            patientInfo[0]     = '\0';
            appointmentInfo[0] = '\0';
            foundAppointment   = false;
        }
        else if (!foundAppointment) {
            strcat(patientInfo, line);
        }
        else {
            strcat(appointmentInfo, line);
        }
    }

    fclose(f);
    fclose(temp);

    if (appointmentDeletedCount > 0) {
        remove(fileName);
        rename("temp_test.txt", fileName);
        printf("Da xoa thanh cong lich hen cua: %s\n", searchKey);
    } else {
        remove("temp_test.txt");
        printf("Khong tim thay lich hen can xoa\n");
    }
}

// ─────────────────────────────────────────────
//  HỦY LỊCH HẸN (Admin/Staff: bất kỳ | Patient: của chính mình)
//  Được gọi từ menu case 3 — tất cả vai trò
// ─────────────────────────────────────────────
void processDeleteAction(const char *fileName, const User *currentUser) {
    char searchKey[100];
    int  attempts     = 0;
    const int MAX_ATT = 3;

    printf("\n--- HUY LICH HEN KHAM BENH ---\n");

    // Bệnh nhân: tự động dùng username của mình, không hỏi
    if (currentUser->role == ROLE_PATIENT) {
        printf("[INFO] Ban chi co the huy lich hen cua chinh minh.\n");
        strncpy(searchKey, currentUser->username, sizeof(searchKey) - 1);
        searchKey[sizeof(searchKey) - 1] = '\0';

        if (!isPatientExist(fileName, searchKey)) {
            printf("Khong tim thay lich hen cua: %s\n", searchKey);
            return;
        }

        printf("Xac nhan huy lich hen cho [%s] (Y/N): ", searchKey);
        char choice[5];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        if (choice[0] == 'y' || choice[0] == 'Y')
            deleteAppointment(fileName, searchKey);
        else
            printf("Thao tac huy da bi bo qua.\n");
        return;
    }

    // Admin / Staff: nhập tự do, có giới hạn 3 lần
    while (attempts < MAX_ATT) {
        printf("Nhap Ma BHYT, Ten hoac SDT: ");
        fflush(stdout);

        if (fgets(searchKey, sizeof(searchKey), stdin) == NULL) {
            printf("Loi doc du lieu!\n");
            continue;
        }
        searchKey[strcspn(searchKey, "\n")] = '\0';

        if (!isValidInfo(searchKey)) {
            attempts++;
            if (attempts < MAX_ATT)
                printf("Con %d lan nhap (tong %d).\n", MAX_ATT - attempts, MAX_ATT);
            continue;
        }

        if (!isPatientExist(fileName, searchKey)) {
            printf("Khong tim thay thong tin benh nhan tren he thong!\n");
            attempts++;
            if (attempts < MAX_ATT)
                printf("Con %d lan nhap (tong %d).\n", MAX_ATT - attempts, MAX_ATT);
            continue;
        }

        printf("\nXac nhan huy lich hen cho [%s] (Y/N): ", searchKey);
        fflush(stdout);
        char choice[5];
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Loi doc du lieu!\n");
            continue;
        }
        choice[strcspn(choice, "\n")] = '\0';

        if (choice[0] == 'y' || choice[0] == 'Y')
            deleteAppointment(fileName, searchKey);
        else
            printf("Thao tac huy da bi bo qua.\n");

        return; // Xong — thoát
    }

    printf("\n[CANH BAO] Nhap sai qua %d lan! Quay lai menu chinh.\n", MAX_ATT);
}