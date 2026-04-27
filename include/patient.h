#ifndef PATIENT_H
#define PATIENT_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
typedef struct{
    char fullName[100];
    int age;
    char gender[10];
    char phoneNumbers[15];
    char healthInsuranceNumbers[15];
} Patient;
//hàm để nhập thông tin bệnh nhân
void getPatientInput(Patient *patient);
//hàm để lưu thông tin bệnh nhân vào file
void saveToFile(Patient *patient,const char *file_Name);
//hàm để xoá thông tin bệnh nhân
void deletePatient(const char *file_Name);
//hàm để sửa thông tin bệnh nhân
void editPatient(const char *file_Name);
//hàm để hiện thị tất cả bệnh nhân
void displayAllPatients(const char *file_Name);
#endif