#include "search.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void searchByBHYT(const char *file_Name)
{
    char healthIns_Number[50];
    printf("hãy nhập mã BHYT của bạn : ");
    fgets(healthIns_Number,sizeof(healthIns_Number), stdin);
    healthIns_Number[strcspn(healthIns_Number,"\n")] = '\0';
    FILE *patientInfo = fopen(file_Name, "r");
    if(patientInfo == NULL)
    {
        printf("Lỗi: không mở được file!\n");
        return;
    } 
    char line[256];
    char record[1024] = "";
    bool found = false;
    while(fgets(line,sizeof(line),patientInfo))
    {
        //Gặp dấu phân cách == đọc xong thông tin 1 người
        if(strcmp(line,"----------------------------\n") == 0)
        {
            if(strstr(record,healthIns_Number) != NULL)
            {
                printf("\nTìm thấy bệnh nhân:\n");
                printf("----------------------------\n");
                printf("%s", record);
                printf("----------------------------\n");
                found = true;
                break;
            }
            record[0] = '\0'; //reset để tìm kiếm tiếp
            continue;
        }
        strcat(record,line);//cộng dồn từng dòng vào record
        if(!found)
        {
            printf("Thông Tin bệnh nhân chưa có sẵn!");
        }
        fclose(patientInfo);
}
}
void searchByfullName(const char *file_Name)
{
    char full_Name[50];
    printf("hãy nhập họ và tên của bạn : ");
    fgets(full_Name,sizeof(full_Name), stdin);
    full_Name[strcspn(full_Name,"\n")] = '\0';
    FILE *patientInfo = fopen(file_Name, "r");
    if(patientInfo == NULL)
    {
        printf("Lỗi: không mở được file!\n");
        return;
    } 
    char line[256];
    char record[1024] = "";
    bool found = false;
    while(fgets(line,sizeof(line),patientInfo))
    {
        //Gặp dấu phân cách == đọc xong thông tin 1 người
        if(strcmp(line,"----------------------------\n") == 0)
        {
            if(strstr(record,full_Name) != NULL)
            {
                printf("\nTìm thấy bệnh nhân:\n");
                printf("----------------------------\n");
                printf("%s", record);
                printf("----------------------------\n");
                found = true;
                break;
            }
            record[0] = '\0'; //reset để tìm kiếm tiếp
            continue;
        }
        strcat(record,line);//cộng dồn từng dòng vào record
        if(!found)
        {
            printf("Thông Tin bệnh nhân chưa có sẵn!");
        }
        fclose(patientInfo);
}
}
void searchByPhoneNumbers(const char *file_Name)
{
    char phone_Numbers[50];
    printf("hãy nhập họ và tên của bạn : ");
    fgets(phone_Numbers,sizeof(phone_Numbers), stdin);
    phone_Numbers[strcspn(phone_Numbers,"\n")] = '\0';
    FILE *patientInfo = fopen(file_Name, "r");
    if(patientInfo == NULL)
    {
        printf("Lỗi: không mở được file!\n");
        return;
    } 
    char line[256];
    char record[1024] = "";
    bool found = false;
    while(fgets(line,sizeof(line),patientInfo))
    {
        //Gặp dấu phân cách == đọc xong thông tin 1 người
        if(strcmp(line,"----------------------------\n") == 0)
        {
            if(strstr(record,phone_Numbers) != NULL)
            {
                printf("\nTìm thấy bệnh nhân:\n");
                printf("----------------------------\n");
                printf("%s", record);
                printf("----------------------------\n");
                found = true;
                break;
            }
            record[0] = '\0'; //reset để tìm kiếm tiếp
            continue;
        }
        strcat(record,line);//cộng dồn từng dòng vào record
        if(!found)
        {
            printf("Thông Tin bệnh nhân chưa có sẵn!");
        }
        fclose(patientInfo);
}
}
