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
void getPatientInput(Patient *patient);
void saveToFile(Patient *patient,const char *file_Name);
void deletePatient(const char *file_Name);
void editPatient(const char *file_Name);
void displayAllPatients(const char *file_Name);
#endif