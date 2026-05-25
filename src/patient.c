#include "patient.h"
#include <ctype.h>
#include "UI.h"
void getPatientInput(Patient *patient) {
    // Họ tên — chỉ chữ và khoảng trắng
    while (1) {
        printPrompt("Ho va ten: ");
        fgets(patient->fullName, sizeof(patient->fullName), stdin);
        patient->fullName[strcspn(patient->fullName, "\r\n")] = '\0';

        bool valid = strlen(patient->fullName) >= 2;
        for (int i = 0; patient->fullName[i] && valid; i++)
            if (!isalpha((unsigned char)patient->fullName[i]) && patient->fullName[i] != ' ')
                valid = false;

        if (valid) break;
        printError("Ho ten chi chua chu cai va khoang trang, toi thieu 2 ky tu!");
    }

    // Tuổi — chỉ số, 1-120
    while (1) {
        printPrompt("Tuoi: ");
        if (scanf("%d", &patient->age) == 1 && patient->age >= 1 && patient->age <= 120) {
            getchar();
            break;
        }
        while (getchar() != '\n');
        printError("Tuoi khong hop le (1-120)!");
    }

    // Giới tính — chỉ "Nam" hoặc "Nu"
    while (1) {
        printPrompt("Gioi tinh (Nam/Nu): ");
        fgets(patient->gender, sizeof(patient->gender), stdin);
        patient->gender[strcspn(patient->gender, "\r\n")] = '\0';

        if (strcmp(patient->gender, "Nam") == 0 || strcmp(patient->gender, "Nu") == 0)
            break;
        printError("Gioi tinh chi duoc nhap 'Nam' hoac 'Nu'!");
    }

    // Số điện thoại — chỉ số, 9-11 ký tự
    while (1) {
        printPrompt("So dien thoai: ");
        fgets(patient->phoneNumbers, sizeof(patient->phoneNumbers), stdin);
        patient->phoneNumbers[strcspn(patient->phoneNumbers, "\r\n")] = '\0';

        int len = strlen(patient->phoneNumbers);
        bool valid = (len >= 9 && len <= 11);
        for (int i = 0; patient->phoneNumbers[i] && valid; i++)
            if (!isdigit((unsigned char)patient->phoneNumbers[i]))
                valid = false;

        if (valid) break;
        printError("So dien thoai chi chua so, tu 9-11 ky tu!");
    }

    // Mã BHYT — chỉ số
    while (1) {
        printPrompt("Ma BHYT: ");
        fgets(patient->healthInsuranceNumbers, sizeof(patient->healthInsuranceNumbers), stdin);
        patient->healthInsuranceNumbers[strcspn(patient->healthInsuranceNumbers, "\r\n")] = '\0';

        bool valid = strlen(patient->healthInsuranceNumbers) >= 1;
        for (int i = 0; patient->healthInsuranceNumbers[i] && valid; i++)
            if (!isdigit((unsigned char)patient->healthInsuranceNumbers[i]))
                valid = false;

        if (valid) break;
        printError("Ma BHYT chi chua so!");
    }
}

void deletePatient(Patient **head, const char *file_Name) {
    char healthIns_Num[50];
    printf("Nhap ma BHYT cua benh nhan can xoa : ");
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
        printf("Thong tin benh nhan chua co san!\n");
        return;
    }
    // Ghi lại file sau khi xóa
    saveListToFile(*head, file_Name);
    printf("Xoa benh nhan thanh cong!\n");
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
            printf("Hay nhap thong tin moi:\n");
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
    if (!head) { printf("Danh sach trong!\n"); return; }
    int i = 1;
    for (Patient *cur = head; cur; cur = cur->next, i++) {
        printf("\n[%d] %-30s | %3d tuoi | %-6s | %-15s | %s\n",
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