#ifndef SEARCH_H
#define SEARCH_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//Tìm bệnh nhân theo mã BHYT
void searchByBHYT(const char *file_Name);
//Tìm bệnh nhân theo Họ tên
void searchByfullName(const char *file_Name);
//tìm bệnh nhân theo sđt
void searchByPhoneNumbers(const char *file_Name);
static bool fieldMatchesExact(const char *record, const char *fieldLabel, const char *searchValue);
#endif
