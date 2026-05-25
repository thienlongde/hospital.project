#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <stdbool.h>
#include "auth.h"

// Kiểm tra tính hợp lệ của đầu vào (tên / SDT / BHYT)
bool isValidInfo(const char *input);

// Tìm kiếm bản ghi trong file theo từ khóa
void searchInFile(const char *fileName, const char *searchKey);

// Tra cứu lịch khám (mọi vai trò)
void processAppointmentLookup(const char *fileName);

// Kiểm tra bệnh nhân có tồn tại trong file không
bool isPatientExist(const char *fileName, const char *searchKey);

// Xóa lịch hẹn khỏi file theo từ khóa
void deleteAppointment(const char *fileName, const char *searchKey);

// Hủy lịch hẹn — Admin/Staff nhập tự do, Patient chỉ hủy của chính mình
void processDeleteAction(const char *fileName, const User *currentUser);
#endif
