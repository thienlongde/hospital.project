#ifndef PATIENT_H
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bookinginfo.h"
typedef struct Patient {
    char fullName[100];
    int age;
    char gender[10];
    char phoneNumbers[15];
    char healthInsuranceNumbers[15];
    BookingInfo booking;
    struct Patient *next;
} Patient;

void getPatientInput(Patient *patient);
void saveToFile(Patient *patient, const char *file_Name);
void deletePatient(Patient **head, const char *file_Name);
void editPatient(Patient **head, const char *file_Name);
void displayAllPatients(Patient *head);
void freeList(Patient **head);
Patient*  loadListFromFile(const char *file_Name);
void saveListToFile(Patient *head, const char *file_Name);

#endif