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
#endif
