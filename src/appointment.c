#include "../include/appointment.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"
#include "booking.h"
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
void deleteAppointmentByName(const char *fileName, const char *searchKey){
    FILE *f = fopen(fileName, "r");
    if(!f){
        printf("Khong tim thay du lieu nguoi dung ");
        return;
    }
    FILE *temp = fopen("../data/temp.txt", "w");
    if(!temp){
        printf("Loi he thong khi tai file tam\n ");
        fclose(f);
        return;
    }
    BookingInfo record;
    bool found = false;
    while(fscanf(f, " %99[^|]|%99[^|]|%49[^|]|%29[^|]|%19[^\n]\n",
                  record.department,
                  record.packageName,
                  record.doctor,
                  record.date,
                  record.time) == 5) {
                     // TIM KIEM THEO bac si, ngay hoac gio
        if (strstr(record.doctor,     searchKey) != NULL ||
            strstr(record.date,       searchKey) != NULL ||
            strstr(record.time,       searchKey) != NULL ||
            strstr(record.packageName,searchKey) != NULL ||
            strstr(record.department, searchKey) != NULL) {

            found = true; // DANH DAU TIM THAY, BO QUA KHONG GHI VAO TEMP
            } else {
                    // Ghi lai nhung thong tin khong khop va file temp
                    fprintf(temp, "%s|%s|%s|%s|%s\n",
                            record.department,
                            record.packageName,
                            record.doctor,
                            record.date,
                            record.time);
                  }
                  fclose(f);
                  fclose(temp);
        if(found){
        remove(fileName);
        rename("../data/temp.txt", fileName);
        printf("Đã xóa thành công lịch hẹn của: %s\n", searchKey);
    } else {
        remove("../data/temp.txt");
        printf("Không tìm thấy lịch hẹn với thông tin: %s\n", searchKey);
    }
 }
}
void processDeleteAction(const char *fileName){
    char searchKey[50];
    printf("\n--- HỦY LỊCH HẸN KHÁM BỆNH ---\n");
    printf("Nhập tên bác sĩ, ngày khám hoặc giờ khám muốn xóa: ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = '\0';

    if (isValidInfo(searchKey)) {
        printf("\nXác nhận xóa lịch hẹn của \"%s\"? (Y/N): ", searchKey);
        char choice;
        scanf(" %c", &choice);
        getchar();

        if (choice == 'Y' || choice == 'y') {
            deleteAppointment(fileName, searchKey);
        } else {
            printf("Đã hủy bỏ thao tác xóa lịch hẹn.\n");
        }
    } else {
        printf("Thông tin nhập vào không hợp lệ.\n");
    }
}