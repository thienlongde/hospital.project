#ifndef BOOKING_H
#define BOOKING_H
#include "bookinginfo.h"
#include "patient.h"
//khai báo hàm
void displayDepartment();
void displayPackage(char department[]);
void displayPackageDetail(char packageName[]);
int displayAvailableSlot(char *dotoc, char *date);
int checkSlotAvailable(char date[], char time[]);
BookingInfo bookingFlow(Patient **patientList);
int isDuplicateBooking(BookingInfo info);
void executeBookingProcess(BookingInfo info, Patient *patient, Patient **patientList, char *file_Name);
Patient* findOrCreatePatient(Patient **patientList);
int      chooseDepartment(char department[]);
int      choosePackage(BookingInfo *info, int departmentChoice);
int      inputBookingDate(char date[]);
int      chooseTimeSlot(BookingInfo *info);
#endif
