#include<stdio.h>
#include<string.h>
#include"booking.h"
#include <stdlib.h>
#include "patient.h"
#include "UI.h"
void displayDepartment(){
    printf("=====DANH SACH CHUYEN KHOA=====\n");
    printf("1. Rang ham mat\n");
    printf("2. Da lieu\n");
    printf("3. Tong quat\n");
}

void displayPackage(char department[]){
    printf("=====DANH SACH GOI KHAM=====\n");
    //strcmp(a,b)==0 => hai chuỗi giống nhau
    if(strcmp(department,"Rang ham mat") == 0){
        printf("1. Kham rang tong quat\n");
        printf("2. Phau thuat nho rang khon, chinh ham lech\n");
        printf("3. Trong rang, boc rang su, nieng rang\n");
    }
    
    else if(strcmp(department,"Da lieu") == 0){
        printf("1. Kham da lieu tong quat\n");
        printf("2. Dieu tri mun\n");
        printf("3. Phau thuat tham my\n");
    }
    
    else if(strcmp(department,"Tong quat") == 0){
        printf("1. Kham lam san\n");
        printf("2. Xet nghiem\n");
    }
}

void displayPackageDetail(char packageName[]){
    printf("=====CHI TIET GOI KHAM=====\n");
    
    //chi tiết gói khám răng hàm mặt
    if(strcmp(packageName,"Kham rang tong quat") == 0){
        printf("Gia: 200.000 VND\n");
        printf("Mo ta: Kiem tra rang mieng tong quat, chup X-quang canh chao va tu van.\n");
        printf("Bac si: BS. Nguyen Van An\n");
    }
    else if(strcmp(packageName,"Phau thuat nho rang khon, chinh ham lech") == 0){
        printf("Gia: 1.500.000 - 4.000.000 VND/rang\n");
        printf("Mo ta: Tieu phat nho rang khon moc lech, moc ngam bang may Piezotome.\n");
        printf("Bac si: BS. Tran Thi Binh\n");
    }
    else if(strcmp(packageName,"Trong rang, boc rang su, nieng rang") == 0){
        printf("Gia: 10.000.000 - 50.000.000 VND\n");
        printf("Mo ta: Phuc hinh rang su tham my, cam ghep Implant ho cả nieng rang mac cai.\n");
        printf("Bac si: BS. Le Hoang Nam\n");
    }
    //chi tiết gói khám da liễu 
    else if(strcmp(packageName,"Kham da lieu tong quat") == 0){
        printf("Gia: 350.000 VND\n");
        printf("Mo ta: Soi da ky thuat so, chan doan cac benh ly ve da, toc va mong.\n");
        printf("Bac si: BS. Pham Minh Thu\n");
    }
    else if(strcmp(packageName,"Dieu tri mun") == 0){
        printf("Gia: 700.000 VND/buoi\n");
        printf("Mo ta: Lay nhan mun chuan y khoa, chieu anh sang sinh hoc tri tham.\n");
        printf("Bac si: BS. Do Duc Manh\n");
    }
    else if(strcmp(packageName,"Phau thuat tham my") == 0){
        printf("Gia: 5.000.000 - 20.000.000 VND\n");
        printf("Mo ta: Cat mi, nang mui, xoa nep nhan hoac cac thu thuat xam lan toi thieu.\n");
        printf("Bac si: BS. Vu Phuong Thao\n");
    }
    //chi tiết gói khám tổng quát
    else if(strcmp(packageName,"Kham lam san") == 0){
        printf("Gia: 150.000 VND\n");
        printf("Mo ta: Kiem tra huyet ap, can nang, chieu cao va kham noi khoa co ban.\n");
        printf("Bac si: BS. Hoang Van Minh\n");
    }
    else if(strcmp(packageName,"Xet nghiem") == 0){
        printf("Gia: 800.000 VND\n");
        printf("Mo ta: Xet nghiem cong thuc mau, duong huyet, chuc nang gan va than.\n");
        printf("Bac si: BS. Dang Quoc Bao\n");
    }
}

int checkSlotAvailable(char date[], char time[]){
    FILE *f = fopen("booking.txt","r");

    if(f == NULL){
        return 1;//file chưa tồn tại hoặc mở lỗi => còn slot
    }

    BookingInfo temp;
    int count = 0;

    while(fscanf(f,"%99[^|]|%99[^|]|%49[^|]|%29[^|]|%19[^\n]\n",
            temp.department,
            temp.packageName,
            temp.doctor,
            temp.date,
            temp.time) == 5){
        if(strcmp(temp.date,date) == 0 && strcmp(temp.time,time) == 0){
            count++;
        }
    }
    fclose(f);

    return count < 5;

}

void displayAvailableSlot(char date[]){
    printf("=====CHO CON TRONG======\n");
    
    if(checkSlotAvailable(date,"08:00"))
        printf("1. 08:00\n");

    if(checkSlotAvailable(date,"09:00"))
        printf("2. 09:00\n");
    
    if(checkSlotAvailable(date,"10:00"))
        printf("3. 10:00\n");
    
    if(checkSlotAvailable(date,"11:00"))
        printf("4. 11:00\n");
    
    if(checkSlotAvailable(date,"14:00"))
        printf("5. 14:00\n");
    
    if(checkSlotAvailable(date,"15:00"))
        printf("6. 15:00\n");
    
    if(checkSlotAvailable(date,"16:00"))
        printf("7. 16:00\n");
    
    if(checkSlotAvailable(date,"17:00"))
        printf("8. 17:00\n");
    
}

//TUYẾN TRÌNH ĐẶT LỊCH KHÁM
BookingInfo bookingFlow(Patient **patientList){
    clearScreen();
    BookingInfo info;//tạo 1 struct lưu dữ liệu booking của user
    memset(&info, 0, sizeof(info));
    // Tìm bệnh nhân theo BHYT
    char healthIns_Num[50];
    printf("Nhap ma BHYT de dat lich: ");
    fgets(healthIns_Num, sizeof(healthIns_Num), stdin);
    healthIns_Num[strcspn(healthIns_Num, "\n")] = '\0';
    // Tìm trong linked list
    Patient *found = NULL;
    for (Patient *cur = *patientList; cur; cur = cur->next){
        if (strcmp(cur->healthInsuranceNumbers, healthIns_Num) == 0) {
            found = cur;
            break;
        }
    }

    // Không tìm thấy → hỏi có muốn thêm mới không
    if (!found) {
        printf("\nKhong tim thay benh nhan voi ma BHYT: %s\n", healthIns_Num);

        char confirm;
        printf("Ban co muon them benh nhan moi khong? (Y/N): ");
        scanf(" %c", &confirm);
        getchar();

        if (confirm == 'Y' || confirm == 'y') {
            // Tạo node mới
            Patient *newPatient = (Patient*)malloc(sizeof(Patient));
            newPatient->next = NULL;
            memset(&newPatient->booking, 0, sizeof(newPatient->booking));
            getPatientInput(newPatient);
            // Append vào linked list
            if (!*patientList)*patientList = newPatient;
            else {
                Patient *cur = *patientList;
                while (cur->next) cur = cur->next;
                cur->next = newPatient;
            }
            // Lưu vào file
            saveListToFile(newPatient, "data/patient.txt");
            printf("\nDa them benh nhan moi thanh cong!\n\n");

            found = newPatient;
        } else {
            printf("Da huy. Quay lai menu chinh.\n");
            return info;
        }
    }

    printf("Xin chao, %s!\n\n", found->fullName);
    int departmentChoice, packageChoice, timeChoice;

    displayDepartment();//hiển thị chuyên khoa
    
    printf("Chon chuyen khoa: \n");
    scanf("%d",&departmentChoice);

    switch (departmentChoice){
        case 1: 
            strcpy(info.department,"Rang ham mat");//lưu chuỗi Răng hàm mặt vào dữ liệu chuyên khoa phần booking của user
            break;
        case 2: 
            strcpy(info.department,"Da lieu");//lưu chuỗi Da liễu vào dữ liệu chuyên khoa phần booking của user
            break;
        case 3: 
            strcpy(info.department,"Tong quat");//lưu chuỗi Tổng quát vào dữ liệu chuyên khoa phần booking của user
            break;
        default:
            printf("Lua chon chuyen khoa khong hop le!\n");
            return info;
    }
    
    displayPackage(info.department);

    printf("Chon goi kham: ");
    scanf("%d",&packageChoice);

    if(departmentChoice == 1){
        if(packageChoice == 1){
            strcpy(info.packageName,"Kham rang tong quat");
            strcpy(info.doctor,"BS. Nguyen Van An");
        }
        else if(packageChoice == 2){
            strcpy(info.packageName,"Phau thuat nho rang khon, chinh ham lech");
            strcpy(info.doctor,"BS. Tran Thi Binh");
        }
        else if(packageChoice == 3){
            strcpy(info.packageName,"Trong rang, boc rang su, nieng rang");
            strcpy(info.doctor,"BS. Le Hoang Nam");
        }
        else{
            printf("Lua chon goi kham khong hop le!\n");
            return info;
        }
    }

    else if(departmentChoice == 2){
        if(packageChoice == 1){
            strcpy(info.packageName,"Kham da lieu tong quat");
            strcpy(info.doctor,"BS. Pham Minh Thu");
        }
        else if(packageChoice == 2){
            strcpy(info.packageName,"Dieu tri mun");
            strcpy(info.doctor,"BS. Do Duc Manh");
        }
        else if(packageChoice == 3){
            strcpy(info.packageName,"Phau thuat tham my");
            strcpy(info.doctor,"BS. Vu Phuong Thao");
        }
        else{
            printf("Lua chon goi kham khong hop le!\n");
            return info;
        }
    }
    else if(departmentChoice == 3){
        if(packageChoice == 1){
            strcpy(info.packageName,"Kham lam san");
            strcpy(info.doctor,"BS. Hoang Van Minh");
        }
        else if(packageChoice == 2){
            strcpy(info.packageName,"Xet nghiem");
            strcpy(info.doctor,"BS. Dang Quoc Bao");
        }
        else{
            printf("Lua chon goi kham khong hop le!\n");
            return info;
        }
    }

    displayPackageDetail(info.packageName);

    getchar();//sử lý ký tự "\n" của phím enter

    printf("Nhap ngay kham (dd/mm/yyyy): ");
    fgets(info.date, sizeof(info.date), stdin);
    info.date[strcspn(info.date, "\n")] = 0;//xóa ký tự enter cuối chuỗi

    displayAvailableSlot(info.date);

    printf("Chon gio kham: ");
    scanf("%d",&timeChoice);

    switch(timeChoice) {
        case 1: 
            strcpy(info.time, "08:00"); 
            break;
        case 2: 
            strcpy(info.time, "09:00"); 
            break;
        case 3: 
            strcpy(info.time, "10:00"); 
            break;
        case 4: 
            strcpy(info.time, "11:00"); 
            break;
        case 5: 
            strcpy(info.time, "14:00"); 
            break;
        case 6: 
            strcpy(info.time, "15:00"); 
            break;
        case 7: 
            strcpy(info.time, "16:00"); 
            break;
        case 8: 
            strcpy(info.time, "17:00"); 
            break;
        default:
        printf("Lua chon gio khong hop le!\n");
        return info;
    }
    
    if(checkSlotAvailable(info.date, info.time) != 0){
        found->booking = info;//gán booking vào node
        saveListToFile(*patientList, "data/patient.txt");
        printf("Dat lich thanh cong!\n");
    }
    else{
        printf("Het cho!\n");
    }
    return info;
}
int isDuplicateBooking(BookingInfo info) {
    FILE *f = fopen("booking.txt", "r");
    if (f == NULL) return 0;

    BookingInfo temp;
    while (fscanf(f, " %99[^|]|%99[^|]|%49[^|]|%29[^|]|%19[^\n]\n",
                  temp.department, temp.packageName, temp.doctor, temp.date, temp.time) == 5) {
        
        if (strcmp(temp.date, info.date) == 0 && 
            strcmp(temp.time, info.time) == 0 && 
            strcmp(temp.doctor, info.doctor) == 0) {
            
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void executeBookingProcess(BookingInfo info, Patient *patient, Patient **patientList, char *file_Name) {
    if (strlen(info.date) == 0) return;

    if (isDuplicateBooking(info)) {
        printf("\n\n[THONG BAO] Trung lich! Bac si %s da co hen vao %s ngay %s.", info.doctor, info.time, info.date);
        
        printf("\n\nVui long thu lai voi khung gio khac!\n");
        return;
    }

    char confirmation;
    printf("\n==========================================");
    printf("\n         MAN HINH XAC NHAN DAT LICH");
    printf("\n==========================================");
    printf("\n Ho va ten  : %s", patient->fullName);
    printf("\n Ma BHYT    : %s", patient->healthInsuranceNumbers);
    printf("\n So DT      : %s", patient->phoneNumbers);
    printf("\n------------------------------------------");
    printf("\n Chuyen khoa: %s", info.department);
    printf("\n Goi kham   : %s", info.packageName);
    printf("\n Bac si     : %s", info.doctor);
    printf("\n Thoi gian  : %s | %s", info.time, info.date);
    printf("\n==========================================");
    printf("\nBan co chac chan muon dat lich? (Y/N): ");

    fflush(stdin);
    scanf(" %c", &confirmation);

    if (confirmation == 'Y' || confirmation == 'y') {
        patient->booking = info;
        saveListToFile(*patientList, file_Name);
        
        printf("\n\n[1/2] Dang luu du lieu vao database...");
        
        printf("\n\n[2/2] Dang cap nhat so slot con lai cho ca %s...", info.time);
        
        printf("\n\n>>> DAT LICH THANH CONG! <<<\n");
    } else {
        printf("\n\n[KET THUC] Nguoi dung da huy xac nhan. Giao dich dung lai.\n");
    }
}
