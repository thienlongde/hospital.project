#include "appointment.h"
#include "auth.h"
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
void deleteAppointment(const char *fileName, const char *searchKey ){
    // mo file goc de doc du lieu cua benh nhan
    FILE *f = fopen(fileName,"r");
    if(!f){
        printf("Loi khi mo file du lieu\n");
        return;
    }
    FILE *temp = fopen("temp_test.txt", "w");
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
     if (record[0] != '\0') {
        if (strstr(record, searchKey) == NULL) {
            fputs(record, temp);
        } else {
            found = true;
        }
    }
    fclose(f);
    fclose(temp);
    // CAP NHAT LAI FILE THONG TIN SAU KHI XOA
    if(found){
        remove(fileName); // XOA FILE DU LIEU CHUA THONG TIN CAN XOA
        rename("temp_test.txt", fileName); // DOI TEN FILE TEMP THANH FILE APPOINTMENT.H MOI
        printf("Da xoa thanh cong lich hen cua : %s\n", searchKey); // THONG BAO DA XOA THANH CONG LICH HEN
    } else {
        remove("temp_test.txt"); // XOA FILE TEMP NEU KHONG TIM THAY LICH HEN CAN XOA
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
        scanf("%c", &choice);
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
