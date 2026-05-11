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
void deleteAppointment(const char *fileName, const char *searchKey ){
    // mo file goc de doc du lieu cua benh nhan
    FILE *f = fopen(fileName,"r");
    if(!f){
        printf("Khong tim thay du lieu nguoi dung");
        return;
    }
    FILE *temp = fopen("../data/temp.txt", "w");
    if(!temp){
        printf("Loi he thong khi tai file tam\n ");
        fclose(f);
        return;
    }
    char line[256], record[1024] = "";
    bool found = false;
    // HAM LOGIC DOC DU LIEU 
    while(fgets(line, sizeof(line), f)){
        strcat(record, line);
        // KIEM TRA DONG PHAN CACH MOI CUOI BANG GHI
        if(strncmp(line, "----------------------------\n", 28) == 0){
            if(strstr(record, searchKey) == NULL){
                fputs(record, temp); // GIU LAI THONG TIN NGUOI DUNG NAY
            } else {
                found = true; // DANH DAU DA TIM THAY THONG TIN NGUOI DUNG DE XOA
            }
            record[0] = '\0'; //RESET CHUOI DE DOC THONG TIN TIEP THEO
        }
    }
    fclose(f);
    fclose(temp);
    // CAP NHAT LAI FILE THONG TIN SAU KHI XOA
    if(found){
        remove(fileName); // XOA FILE DU LIEU CHUA THONG TIN CAN XOA
        rename("../data/temp.txt", fileName); // DOI TEN FILE TEMP THANH FILE APPOINTMENT.H MOI
        printf("Da xoa thanh cong lich hen cua : %s\n", searchKey); // THONG BAO DA XOA THANH CONG LICH HEN
    } else {
        remove("../data/temp.txt"); // XOA FILE TEMP NEU KHONG TIM THAY LICH HEN CAN XOA
        printf("Khong tim thay thong tin lich hen "); // THONG BAO KHONG TIM THAY LICH HEN
    }  
}
// HAM THUC THI VIEC XOA DU LIEU LICH HEN
void processDeleteAction(const char *fileName){
    char searchKey[50];
    printf("\n --- HUY LICH HEN KHAM BENH --- ");
    printf("\nXin hay nhap ma BHYT, Ten hoac SĐT ban muon xoa ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = '\0';
    if(isValidInfo(searchKey)){
        printf("\n Xac nhan xoa (Y/N)");
        char choice;
        scanf(" %c ", &choice);
        getchar();
        if(choice == 'y' || choice == 'Y'){
            deleteAppointment(fileName, searchKey);
        } else {
            printf("\n Đã hủy bỏ thao tác xóa lịch hẹn \n");
        }
    } else {
        printf("Thông tin nhập vào không hợp lệ");
    }
}
