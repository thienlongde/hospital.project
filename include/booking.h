#ifndef BOOKING_H
#define BOOKING_H

//Tạo cấu stuct BookingInfo
typedef struct{
    char department[50];//lưu chuyên khoa
    char packageName[50];//lưu tên gói khám
    char doctor[50];//lưu bác sĩ tương ứng chuyên khoa
    char date[30];//lưu ngày khám
    char time[20];//lưu giờ khám
} BookingInfo;

//khai báo hàm
void displayDepartment();
void displayPackage(char department[]);
void displayPackageDetail(char packageName[]);
void displayAvailableSlot(char date[]);
int checkSlotAvailable(char date[], char time[]);
void saveBooking(BookingInfo info);
BookingInfo bookingFlow();

#endif
