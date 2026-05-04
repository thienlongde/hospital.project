#include "patient.h"

void getPatientInput(Patient *patient) {
    printf("Họ và tên : ");
    fgets(patient->fullName, sizeof(patient->fullName), stdin);
    patient->fullName[strcspn(patient->fullName, "\n")] = '\0';

    printf("Tuổi : ");
    scanf("%d", &patient->age);
    getchar();

    printf("Giới Tính : ");
    fgets(patient->gender, sizeof(patient->gender), stdin);
    patient->gender[strcspn(patient->gender, "\n")] = '\0';

    printf("Số điện thoại : ");
    fgets(patient->phoneNumbers, sizeof(patient->phoneNumbers), stdin);
    patient->phoneNumbers[strcspn(patient->phoneNumbers, "\n")] = '\0';

    printf("Mã BHYT: ");
    fgets(patient->healthInsuranceNumbers, sizeof(patient->healthInsuranceNumbers), stdin);
    patient->healthInsuranceNumbers[strcspn(patient->healthInsuranceNumbers, "\n")] = '\0';
}

void saveToFile(Patient *patient, const char *file_Name) {
    FILE *patientInfo = fopen(file_Name, "a");
    if (patientInfo == NULL) {
        printf("Lỗi : không mở được file!\n");
        return;
    }
    fprintf(patientInfo, "Họ và Tên : %s\n",       patient->fullName);
    fprintf(patientInfo, "Tuổi : %d\n",             patient->age);
    fprintf(patientInfo, "Giới Tính : %s\n",        patient->gender);
    fprintf(patientInfo, "Số điện thoại : %s\n",    patient->phoneNumbers);
    fprintf(patientInfo, "Mã BHYT: %s\n",           patient->healthInsuranceNumbers);
    fprintf(patientInfo, "----------------------------\n");
    fclose(patientInfo);
    printf("Đã lưu thông tin thành công!\n");
}

void deletePatient(Patient **head, const char *file_Name) {
    char healthIns_Num[50];
    printf("Nhập mã BHYT của bệnh nhân cần xóa : ");
    fgets(healthIns_Num, sizeof(healthIns_Num), stdin);
    healthIns_Num[strcspn(healthIns_Num, "\n")] = '\0';

    Patient *cur = *head, *prev = NULL;
    bool found = false;

    while (cur) {
        if (strcmp(cur->healthInsuranceNumbers, healthIns_Num) == 0) {
            if (prev) prev->next = cur->next;
            else      *head      = cur->next;
            free(cur);
            found = true;
            break;
        }
        prev = cur;
        cur  = cur->next;
    }

    if (!found) {
        printf("Thông tin bệnh nhân chưa có sẵn!\n");
        return;
    }
    // Ghi lại file sau khi xóa
    saveListToFile(*head, file_Name);
    printf("Xóa bệnh nhân thành công!\n");
}

void editPatient(Patient **head, const char *file_Name) {
    char HealthIns_Num[50];
    printf("Nhap ma BHYT benh nhan can sua: ");
    fgets(HealthIns_Num, sizeof(HealthIns_Num), stdin);
    HealthIns_Num[strcspn(HealthIns_Num, "\n")] = '\0';

    Patient *cur = *head;
    bool found = false;

    while (cur) {
        if (strcmp(cur->healthInsuranceNumbers, HealthIns_Num) == 0) {
            found = true;
            printf("Hãy nhập thông tin mới:\n");
            getPatientInput(cur);  // ghi đè trực tiếp vào node
            break;
        }
        cur = cur->next;
    }

    if (!found) {
        printf("Khong tim thay benh nhan voi ma BHYT: %s\n", HealthIns_Num);
        return;
    }

    // Ghi lại file sau khi sửa
    saveListToFile(*head, file_Name);
    printf("Da sua thong tin thanh cong!\n");
}

void displayAllPatients(Patient *head) {
    if (!head) { printf("Danh sách trống!\n"); return; }
    int i = 1;
    for (Patient *cur = head; cur; cur = cur->next, i++) {
        printf("\n[%d] %-30s | %3d tuổi | %-6s | %-15s | %s\n",
            i, cur->fullName, cur->age, cur->gender,
            cur->phoneNumbers, cur->healthInsuranceNumbers);
    }
}

void freeList(Patient **head) {
    Patient *cur = *head;
    while (cur) {
        Patient *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    *head = NULL;
}

void saveListToFile(Patient *head, const char *file_Name) {
    FILE *patientInfo = fopen(file_Name, "w");
    if (!patientInfo) { printf("Loi: khong mo duoc file!\n"); return; }

    for (Patient *cur = head; cur; cur = cur->next) {
        fprintf(patientInfo, "Ho va Ten : %s\n",      cur->fullName);
        fprintf(patientInfo, "Tuoi : %d\n",            cur->age);
        fprintf(patientInfo, "Gioi Tinh : %s\n",       cur->gender);
        fprintf(patientInfo, "So dien thoai : %s\n",   cur->phoneNumbers);
        fprintf(patientInfo, "Ma BHYT: %s\n",          cur->healthInsuranceNumbers);
        fprintf(patientInfo, "Chuyen khoa : %s\n",     cur->booking.department);
        fprintf(patientInfo, "Goi kham : %s\n",        cur->booking.packageName);
        fprintf(patientInfo, "Bac si : %s\n",          cur->booking.doctor);
        fprintf(patientInfo, "Ngay kham : %s\n",       cur->booking.date);
        fprintf(patientInfo, "Gio kham : %s\n",        cur->booking.time);
        fprintf(patientInfo, "----------------------------\n");
    }
    fclose(patientInfo);
}
Patient* loadListFromFile(const char *file_Name) {
    FILE *patientInfo = fopen(file_Name, "r");
    if (!patientInfo) return NULL;

    Patient *head = NULL, *tail = NULL;
    char line[256];

    while (!feof(patientInfo)) {
        Patient *p = (Patient*)malloc(sizeof(Patient));
        if (!p) break;
        p->next = NULL;
        memset(&p->booking, 0, sizeof(p->booking));

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Ho va Ten : %[^\n]",      p->fullName);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Tuoi : %d",               &p->age);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Gioi Tinh : %[^\n]",      p->gender);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "So dien thoai : %[^\n]",  p->phoneNumbers);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Ma BHYT: %[^\n]",         p->healthInsuranceNumbers);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Chuyen khoa : %[^\n]",    p->booking.department);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Goi kham : %[^\n]",       p->booking.packageName);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Bac si : %[^\n]",         p->booking.doctor);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Ngay kham : %[^\n]",      p->booking.date);

        if (!fgets(line, sizeof(line), patientInfo)) { free(p); break; }
        sscanf(line, "Gio kham : %[^\n]",       p->booking.time);

        fgets(line, sizeof(line), patientInfo); // bỏ dòng "---"

        if (!tail) head = tail = p;
        else { tail->next = p; tail = p; }
    }
    fclose(patientInfo);
    return head;
}