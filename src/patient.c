#include "../include/patient.h"
#include <string.h>
void getPatientInput(Patient *patient)
{
    // nhập họ và tên
    printf("Họ và tên : ");
    fgets(patient->fullName,sizeof(patient->fullName),stdin);
    patient->fullName[strcspn(patient->fullName, "\n")] = '\0'; // xóa dấu xuống dòng thừa
    // nhập tuổi
    printf("Tuổi :  ");
    scanf("%d",&patient->age);
    getchar(); // xóa bộ nhớ đệm
    // nhập giới tính
    printf("Giới Tính : ");
    fgets(patient->gender,sizeof(patient->gender),stdin);
    patient->gender[strcspn(patient->gender, "\n")] = '\0';
    // nhập sđt
    printf("Số điện thoại : ");
    fgets(patient->phoneNumbers, sizeof(patient->phoneNumbers), stdin);
    patient->phoneNumbers[strcspn(patient->phoneNumbers, "\n")] = '\0';
    // nhập mã BHYT
    printf("Mã BHYT: ");
    fgets(patient->healthInsuranceNumbers, sizeof(patient->healthInsuranceNumbers), stdin);
    patient->healthInsuranceNumbers[strcspn(patient->healthInsuranceNumbers, "\n")] = '\0';
}
void saveToFile(Patient *patient,const char *file_Name)
{
    FILE *patientInfo = fopen(file_Name,"a");
    if(patientInfo == NULL)
    {
        printf("Lỗi : không mở được file!\n");
        return;
    }
    fprintf(patientInfo,"Họ và Tên : %s\n",patient->fullName);
    fprintf(patientInfo,"Tuổi : %d\n",patient->age);
    fprintf(patientInfo,"Giới Tính : %s\n",patient->gender);
    fprintf(patientInfo,"Số điện thoại : %s\n",patient->phoneNumbers);
    fprintf(patientInfo,"Mã BHYT: %s\n",patient->healthInsuranceNumbers);
    fprintf(patientInfo, "----------------------------\n");
    fclose(patientInfo);
    printf("Đã lưu thông tin  thành công\n");
}
void deletePatient(const char *file_Name)
{
    char healthIns_Num[50];
    printf("Nhập mã BHYT của bệnh nhân cần xóa : ");
    fgets(healthIns_Num,sizeof(healthIns_Num),stdin);
    healthIns_Num[strcspn(healthIns_Num,"\n")] = '\0';
    FILE *patientInfo = fopen(file_Name,"r");
    if(patientInfo == NULL)
    {
        printf("Lỗi : Không mở được file!");
        return;
    }
    char all[10000] = "";
    char line[256];
    char record[1024] = "";
    bool found = false;
    while(fgets(line,sizeof(line),patientInfo))
    {
        if(strcmp(line, "----------------------------\n") == 0)
        {
            if(strstr(record,healthIns_Num))//nếu record đúng
            {
                found = true; //bỏ qua record không ghi lại
            }
            else
            {
                strcat(all,record);
                strcat(all,"----------------------------\n");
            }
            record[0] = '\0';
            continue;
        }
        strcat(record,line);
    }
    fclose(patientInfo);
    if(!found)
        {
            printf("Thông Tin bệnh nhân chưa có sẵn!");
            return;
        }
    //Ghi lại File không chứa bệnh nhân đã xóa
    FILE *newFile = fopen(file_Name, "w");
    fprintf(newFile, "%s", all);
    fclose(newFile);
    printf("Xóa benh nhan thanh cong!\n");
}
void editPatient(const char *file_Name)
{
    char HealthIns_Num[50];
    printf("Nhap ma BHYT benh nhan can sua: ");
    fgets(HealthIns_Num, sizeof(HealthIns_Num), stdin);
    HealthIns_Num[strcspn(HealthIns_Num, "\n")] = '\0';
    FILE *patientInfo = fopen(file_Name,"r");
    if(patientInfo == NULL)
    {
        printf("Lỗi : không mở được file!");
        return;
    }
    char all[10000];
    char line[256];
    char record[1024] = "";
    bool found = false;
    while(fgets(line,sizeof(line),patientInfo))
    {
        if(strcmp(line,"----------------------------\n") == 0)
        {
            if(strstr(record,HealthIns_Num) != NULL)
            {
                found = true;
                Patient edited_Patient;
                printf("Hãy Nhập thông tin mới : ");
                getPatientInput(&edited_Patient);
                saveToFile(&edited_Patient,"data/temp.txt");
                FILE *temp = fopen("data/temp.txt","r");
                char newRecord[1024] = "";
                while(fgets(line, sizeof(line), temp))
                strcat(newRecord, line);
                fclose(temp);
                remove("data/temp.txt");
                strcat(all,newRecord);
            }else
        {
            strcat(all, record);
            strcat(all, "----------------------------\n");
        }
        record[0] = '\0';
        continue;
        }
        strcat(record,line);
    }
    fclose(patientInfo);
    if(!found)
    {
        printf("Khong tim thay benh nhan voi ma BHYT: %s\n", HealthIns_Num);
        return;
    }
    FILE *newFile = fopen(file_Name, "w");
    fprintf(newFile, "%s", all);
    fclose(newFile);
    printf("Da sua thong tin thanh cong!\n");
}