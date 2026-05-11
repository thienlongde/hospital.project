#ifndef BOOKINGINFO_H
#define BOOKINGINFO_H
//FILE NÀY LÀ ĐỂ TRÁNH BỊ VÒNG LẶP PATIENT VÀ BOOKING GỌI LẪN NHAU 
typedef struct{
    char department[100];//lưu chuyên khoa
    char packageName[100];//lưu tên gói khám
    char doctor[50];//lưu bác sĩ tương ứng chuyên khoa
    char date[30];//lưu ngày khám
    char time[20];//lưu giờ khám
} BookingInfo;
#endif