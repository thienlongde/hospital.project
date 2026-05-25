#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // Thêm thư viện này để kiểm tra chữ số cho BHYT
#include "search.h"
<<<<<<< HEAD
#include "../include/UI.h"
static bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue) {
=======
#include "UI.h"

// 1. Bộ dọn bộ đệm chống trôi lệnh nhập liệu cho cả 3 hàm tra cứu
static void clearSearchBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 2. Bộ kiểm tra định dạng bắt buộc phải đủ 15 chữ số cho BHYT
static bool validateBHYT_Search(const char *bhyt) {
    if (strlen(bhyt) != 15) return false;
    for (int i = 0; i < 15; i++) {
        if (!isdigit((unsigned char)bhyt[i])) return false;
    }
    return true;
}

// MỞ KHÓA: Xóa chữ static để các file khác (hoặc chính nó) liên kết mượt mà
bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue) {
>>>>>>> appointment-moi
    const char *pos = strstr(record, fieldLabel);
    if (pos == NULL) return false;

    // Nhảy qua label để tới value
    pos += strlen(fieldLabel);

    // Bỏ qua khoảng trắng~
    while (*pos == ' ' || *pos == '\t') pos++;

    // So sánh value, kết thúc tại \r hoặc \n
    size_t len = strcspn(pos, "\r\n");
    return (strlen(searchValue) == len && strncmp(pos, searchValue, len) == 0);
}

// MỞ KHÓA: Xóa chữ static và sửa kiểu dữ liệu const char* để tránh cảnh báo biên dịch
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

// =========================================================
// 1. TRA CỨU THEO MÃ BHYT (Đã tích hợp chặn lỗi 15 chữ số)
void searchByBHYT(const char *file_Name) {
    char healthIns_Number[50];
    
    clearSearchBuffer(); // Chống trôi lệnh từ Menu chính

    do {
        printf("\n--- TÌM KIẾM BỆNH NHÂN THEO MÃ BHYT ---\n");
        printf("Hay nhap ma BHYT cua ban (Yeu cau DU 15 SO): ");
        fflush(stdout);
        fgets(healthIns_Number, sizeof(healthIns_Number), stdin);
        healthIns_Number[strcspn(healthIns_Number, "\r\n")] = '\0';

        if (!validateBHYT_Search(healthIns_Number)) {
            setColor(12); // Chuyển chữ sang màu đỏ báo lỗi
            printf("Loi: Ma BHYT phai gom chinh xac 15 chu so va khong chua ky tu chu. Vui long nhap lai!\n");
            setColor(7);  // Trả lại màu chữ bình thường
        } else {
            break; // Nhập đúng 15 chữ số thì thoát ra để tra cứu file
        }
    } while (true);

    FILE *patientInfo = fopen(file_Name, "r");
    if (patientInfo == NULL) { printf("Loi: khong mo duoc file!\n"); return; }

    char line[256];
    char record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), patientInfo)) {
        if (strncmp(line, "----------------------------", 28) == 0) {
            if (fieldMatchesExact(record, "Ma BHYT:", healthIns_Number)) {
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

// 2. TRA CỨU THEO HỌ VÀ TÊN (Đã sửa chống trôi lệnh)
void searchByfullName(const char *file_Name) {
    char full_Name[50];
    
    clearSearchBuffer(); // Chống trôi lệnh nhập họ tên

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
            if (fieldMatchesExact(record, "Ho va Ten :", full_Name)) {
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

// 3. TRA CỨU THEO SỐ ĐIỆN THOẠI (Đã sửa chống trôi lệnh)
void searchByPhoneNumbers(const char *file_Name) {
    char phone_Numbers[50];
<<<<<<< HEAD
    printf("Hay nhap so dien thoai cua ban :");
=======
    
    clearSearchBuffer(); // Chống trôi lệnh nhập SĐT

    printf("Hay nhap so dien thoai cua ban: ");
>>>>>>> appointment-moi
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
            if (fieldMatchesExact(record, "So dien thoai :", phone_Numbers)) {
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