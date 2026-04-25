#include "../include/appointment.h"
#include <stdio.h>
#include <string.h>

bool isValidInfo(const char *input) {
    // Nếu chuỗi rỗng hoặc chỉ có khoảng trắng thì không hợp lệ
    if (strlen(input) < 1) return false;
    return true;
}

void searchInFile(const char *fileName, const char *searchKey) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Lỗi: Không tìm thấy dữ liệu khám bệnh!\n");
        return;
    }

    char line[256], record[1024] = "";
    bool found = false;

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "----------------------------\n") == 0) {
            if (strstr(record, searchKey)) {
                printf("\n[ KẾT QUẢ TÌM THẤY ]\n%s----------------------------\n", record);
                found = true;
                break;
            }
            record[0] = '\0';
            continue;
        }
        strcat(record, line);
    }

    if (!found) printf("=> Không có lịch khám cho: %s\n", searchKey);
    fclose(f);
}

void processAppointmentLookup(const char *fileName) {
    char searchKey[50];
    
    printf("\n--- HỆ THỐNG TRA CỨU LỊCH KHÁM ---\n");
    printf("Nhập BHYT, Họ tên hoặc SDT: ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = '\0';

    // FLOW: Kiểm tra hợp lệ -> Tìm kiếm
    if (isValidInfo(searchKey)) {
        searchInFile(fileName, searchKey);
    } else {
        printf("Thông tin không hợp lệ. Kết thúc!\n");
    }
}