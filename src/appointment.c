#include "../include/appointment.h"
#include <stdio.h>
#include <string.h>
#include "search.h"

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
// KIỂM TRA THÔNG TIN BỆNH NHÂN CÓ TỒN TẠI KHÔNG
bool isPatientExist(const char *fileName, const char *searchKey){
    FILE *f = fopen(fileName, "r");
    if(!f) return false;
    
    char line[256];
    char patientBlock[2048] = "";
    bool found = false;
    
    while(fgets(line, sizeof(line), f)){
    if(strncmp(line, "Chuyen khoa", 11) == 0){
        break;
    }
    strcat(patientBlock, line);  // ✅ Tích lũy toàn bộ dòng
}

// ✅ Tìm trong toàn bộ phần thông tin bệnh nhân
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
                    // GIỮ lịch hẹn
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
    }
}
