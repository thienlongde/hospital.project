#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <stdbool.h>
// Hàm chính để điều phối việc nhập liệu và tìm kiếm
void processAppointmentLookup(const char *fileName);
// Hàm xử lý logic đọc file
void searchInFile(const char *fileName, const char *searchKey);
// Hàm kiểm tra tính hợp lệ của đầu vào
bool isValidInfo(const char *input);
#endif