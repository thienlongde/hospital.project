#include "../include/appointment.h"
#include <stdio.h>
#include <string.h>
#include "search.h"
#include <ctype.h>

#include <ctype.h> 

bool isValidInfo(const char *input) {
    int len = strlen(input);
    
    // 1. Kiểm tra rỗng hoặc quá ngắn
    if (len < 2) return false; 

    bool isAllDigits = true;
    bool isAllAlpha = true;

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

    if (isAllDigits) {
        if (len == 10 || len == 11) return true;
        else {
            printf("=> [LOI] So dien thoai phai co 10 hoac 11 chu so!\n");
            return false;
        }
    }

    // 3. Điều kiện cho Mã BHYT: Thường có độ dài chuẩn là 15 ký tự (chữ và số)
    // Nếu nghiệp vụ của bạn quy định độ dài khác, hãy sửa số 15 lại
    if (len == 15) {
        return true; 
    }

    // 4. Điều kiện cho Họ tên: Không chứa ký tự đặc biệt nguy hiểm
    if (isAllAlpha) {
        return true;
    }

    // Nếu không khớp với bất kỳ định dạng hợp lệ nào
    printf("=> [LOI] Dinh dang nhap vao khong hop le (Khong phai Ten, SDT 10-11 so, hoac BHYT 15 ky tu)!\n");
    return false;
}

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

void processAppointmentLookup(const char *fileName) {
    char searchKey[50];
    
    printf("\n--- HE THONG TRA CUU LICH KHAM ---\n");
    printf("Nhap BHYT (15 ky tu), Ho ten hoac SDT (10-11 so): ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = '\0';

    // FLOW mới: Ép điều kiện chặt chẽ trước khi quét file
    if (isValidInfo(searchKey)) {
        searchInFile(fileName, searchKey);
    } else {
        printf("Thong tin khong hop le. Ket thuc tra cuu!\n");
    }
}
// KIỂM TRA THÔNG TIN BỆNH NHÂN CÓ TỒN TẠI KHÔNG
bool isPatientExist(const char *fileName, const char *searchKey){
    FILE *f = fopen(fileName, "r");
    if(!f) {
        return false;
    }

    char line[256];
    char patientBlock[2048] = "";
    bool found = false;
    
    while(fgets(line, sizeof(line), f)){
    if(strncmp(line, "Chuyen khoa", 11) == 0){
        break;
    }
    strcat(patientBlock, line);  //  Tích lũy toàn bộ dòng
}

//  Tìm trong toàn bộ phần thông tin bệnh nhân
if(strstr(patientBlock, searchKey) != NULL){
    found = true;
}
    
    fclose(f);
    return found;
}


// XÓA LỊCH HẸN
void deleteAppointment(const char *fileName, const char *searchKey){
    FILE *f = fopen(fileName, "r");
    if(!f){
        printf("Loi khi mo file du lieu\n");
        return;
    }
    
    FILE *temp = fopen("temp_test.txt", "w");
    if(!temp){
        printf("Loi he thong khi tai file tam\n");
        fclose(f);
        return;
    }
    
    char line[256];
    char patientInfo[1024] = "";
    char appointmentInfo[1024] = "";
    bool foundAppointment = false;
    int appointmentDeletedCount = 0;
    
    while(fgets(line, sizeof(line), f)){
        // Đầu của lịch hẹn
        if(strncmp(line, "Chuyen khoa", 11) == 0){
            appointmentInfo[0] = '\0';
            strcat(appointmentInfo, line);
            foundAppointment = true;
        }
        // Cuối của lịch hẹn (dòng phân cách)
        else if(strncmp(line, "----------------------------\n", 28) == 0){
            if(foundAppointment){
                strcat(appointmentInfo, line);
                
                // Kiểm tra: thông tin bệnh nhân có chứa searchKey không?
                if(strstr(patientInfo, searchKey) != NULL){
                    // XÓA lịch hẹn - chỉ ghi thông tin bệnh nhân
                    fputs(patientInfo, temp);
                    fputs(line, temp); // viet dong phan cach thong tin benh nhan truoc va sau
                    appointmentDeletedCount++;
                } else {
<<<<<<< HEAD
                    // GIỮ lịch hẹn
=======
                    // GIữa lịch hẹn
>>>>>>> appointment-moi
                    fputs(patientInfo, temp);
                    fputs(appointmentInfo, temp);
                }
            }
            
            // Reset
            patientInfo[0] = '\0';
            appointmentInfo[0] = '\0';
            foundAppointment = false;
        }
        // Thông tin bệnh nhân (trước "Chuyen khoa")
        else if(!foundAppointment){
            strcat(patientInfo, line);
        }
        // Tiếp tục thông tin lịch hẹn
        else {
            strcat(appointmentInfo, line);
        }
    }
    
    fclose(f);
    fclose(temp);
    
    // Cập nhật file
    if(appointmentDeletedCount > 0){
        remove(fileName);
        rename("temp_test.txt", fileName);
        printf("Da xoa thanh cong lich hen cua: %s\n", searchKey);
    } else {
        remove("temp_test.txt");
        printf("Khong tim thay lich hen can xoa\n");
<<<<<<< HEAD
    }
}


// THỰC THI XÓA LỊCH HẸN
void processDeleteAction(const char *fileName){
    char searchKey[100];
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    while(attempts < MAX_ATTEMPTS){
        printf("\n--- HUY LICH HEN KHAM BENH ---\n");
        printf("Nhap Ma BHYT, Ten hoac SDT: ");
        fflush(stdout);
        //while(getchar() != '\n');  // Xóa bộ đệm
        
        if(fgets(searchKey, sizeof(searchKey), stdin) == NULL || strlen(searchKey) == 0){
            printf("Loi doc du lieu!\n");
            continue;
        }
        
        // xoa ky tu '\n' o cuoi 
        searchKey[strcspn(searchKey, "\n")] = '\0';
        
        // Kiểm tra thông tin có trống không
        if(strlen(searchKey) == 0){
            printf("Thong tin khong duoc de trong!\n");
            attempts++;
            printf("Con %d lan nhap (tong %d).\n", MAX_ATTEMPTS - attempts, MAX_ATTEMPTS);
            continue;
        }
        
        // Kiểm tra thông tin có tồn tại không
        if(!isPatientExist(fileName, searchKey)){
            printf("Khong tim thay thong tin benh nhan!\n");
            attempts++;
            
            if(attempts < MAX_ATTEMPTS){
                printf("Con %d lan nhap (tong %d).\n", MAX_ATTEMPTS - attempts, MAX_ATTEMPTS);
            }
            continue;
        }
        
        // Xác nhận xóa
        printf("\nXac nhan xoa lich hen (Y/N): ");
        fflush(stdout);
        char choice[5];
        if(fgets(choice, sizeof(choice), stdin) == NULL || strlen(choice) == 0){
            printf("Loi doc du lieu!\n");
            continue;
        }
        choice[strcspn(choice, "\n")] = '\0';

        if(choice[0] == 'y' || choice[0] == 'Y'){
            deleteAppointment(fileName, searchKey);
        } else {
            printf("Thao tac xoa da bi huy.\n");
        }
        
        break;  // Thoát khỏi vòng lặp
    }
    
    // Nếu hết lần nhập
    if(attempts >= MAX_ATTEMPTS){
        printf("Ban da nhap sai qua %d lan! Quay lai menu chinh.\n", MAX_ATTEMPTS);
=======
>>>>>>> appointment-moi
    }
}


// THỰC THI XÓA LỊCH HẸN
// THỰC THI XÓA LỊCH HẸN
void processDeleteAction(const char *fileName){
    char searchKey[100];
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    while(attempts < MAX_ATTEMPTS){
        printf("\n--- HUY LICH HEN KHAM BENH ---\n");
        printf("Nhap Ma BHYT, Ten hoac SDT: ");
        fflush(stdout);
        
        if(fgets(searchKey, sizeof(searchKey), stdin) == NULL){
            printf("Loi doc du lieu!\n");
            continue;
        }
        
        // Xóa ký tự xuống dòng '\n' ở cuối chuỗi
        searchKey[strcspn(searchKey, "\n")] = '\0';
        
        // ĐIỀU KIỆN MỚI: Kiểm tra tính hợp lệ của dữ liệu (Trống, sai định dạng tên/sdt/BHYT)
        if(!isValidInfo(searchKey)){
            attempts++;
            if(attempts < MAX_ATTEMPTS){
                printf("Con %d lan nhap (tong %d).\n", MAX_ATTEMPTS - attempts, MAX_ATTEMPTS);
            }
            continue;
        }
        
        // Kiểm tra thông tin có tồn tại trong hệ thống hay không
        if(!isPatientExist(fileName, searchKey)){
            printf("Khong tim thay thong tin benh nhan tren he thong!\n");
            attempts++;
            
            if(attempts < MAX_ATTEMPTS){
                printf("Con %d lan nhap (tong %d).\n", MAX_ATTEMPTS - attempts, MAX_ATTEMPTS);
            }
            continue;
        }
        
        // Xác nhận xóa nếu thông tin hoàn toàn hợp lệ và có tồn tại
        printf("\nXac nhan xoa lich hen cho [%s] (Y/N): ", searchKey);
        fflush(stdout);
        char choice[5];
        if(fgets(choice, sizeof(choice), stdin) == NULL){
            printf("Loi doc du lieu!\n");
            continue;
        }
        choice[strcspn(choice, "\n")] = '\0';

        if(choice[0] == 'y' || choice[0] == 'Y'){
            deleteAppointment(fileName, searchKey);
        } else {
            printf("Thao tac xoa da bi huy.\n");
        }
        
        break;  
    }
    
    // Nếu hết số lần nhập cho phép
    if(attempts >= MAX_ATTEMPTS){
        printf("\n[CANH BAO] Ban da nhap sai hoac khong hop le qua %d lan! Quay lai menu chinh.\n", MAX_ATTEMPTS);
    }
}