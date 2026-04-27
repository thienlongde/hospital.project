#include<stdio.h>
#include<string.h>
#include"booking.h"

void displayDepartment(){
    printf("=====DANH SACH CHUYEN KHOA=====");
    printf("1. Rang ham mat\n");
    printf("2. Da lieu\n");
    printf("3. Tong quat\n");
}

void displayPackage(char department[]){
    printf("=====DANH SACH GOI KHAM=====");
    //strcmp(a,b)==0 => hai chuỗi giống nhau
    if(strcmp(department,"Rang ham mat") == 0){
        printf("1. Kham va chan doan tong quat\n");
        printf("2. Phau thuat nho rang khon, chinh ham lech\n");
        printf("3. Trong rang, boc rang su, nieng rang\n");
    }
    
    else if(strcmp(department,"Da lieu") == 0){
        printf("1. Kham va chan doan tong quat\n");
        printf("2. Dieu tri mun\n");
        printf("3. Phau thuat tham my\n");
    }
    
    else if(strcmp(department,"Tong quat") == 0){
        printf("1. Kham lam san\n");
        printf("2. Xet nghiem\n");
    }
}

void displayPackageDetail(char packageName[]){
    printf("=====CHI TIET GOI KHAM=====");
    
    //chi tiết gói khám răng hàm mặt
    if(strcmp(packageName,"Kham va chan doan tong quat") == 0){
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
    if(strcmp(packageName,"Kham va chan doan tong quat") == 0){
        printf("Gia: 350.000 VND\n");
        printf("Mo ta: Soi da ky thuat so, chan doan cac benh ly ve da, toc va mong.\n");
        printf("Bac si: BS. Pham Minh Thu\n");
    }
    else if(strcmp(packageName,"Dieu tri mun") == 0){
        printf("Gia: 700.000 VND/buoi\n");
        printf("Mo ta: Lay nhan mun chuan y khoa, chieu anh sang sinh hoc tri tham.\n");
        printf("Bac si: BS. Do Duc Manh\n")
    }
    else if(strcmp(packageName,"Phau thuat tham my") == 0){
        printf("Gia: 5.000.000 - 20.000.000 VND\n");
        printf("Mo ta: Cat mi, nang mui, xoa nep nhan hoac cac thu thuat xam lan toi thieu.\n");
        printf("Bac si: BS. Vu Phuong Thao\n");
    }
    //chi tiết gói khám tổng quát
    if(strcmp(packageName,"Kham lam san") == 0){
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

void saveBooking(BookingInfo info);