#include "patient.h"
#include "UI.h"
#include "search.h"
int main()
{
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();  // xoá buffer
        switch(choice)
        {
            case 1:
            printf("\n== Quan ly benh nhan ==\n");
            printf("1. Them benh nhan\n");
            printf("2. Xoa benh nhan\n");
            printf("3. Sua thong tin\n");
            printf("0. Quay lai\n");
            printf("Chon: ");
            int subChoice1;
            scanf("%d", &subChoice1);
            getchar();
            switch(subChoice1)
            {
                case 1:
                    getPatientInput("data/patient.txt");
                    break;
                case 2:
                    deletePatient("data/patient.txt");
                    break;
                case 3:
                    editPatient("data/patient.txt");
                    break;
                case 0:
                    break;
                default:
                    printf("Chon khong hop le!\n");
            }
            break;
            case 2:
            printf("\n== Tra cuu thong tin ==\n");
            printf("1. Tim theo ma BHYT\n");
            printf("2. Tim theo so dien thoai\n");
            printf("3. Tim theo ho ten\n");
            printf("Chon: ");
            int subChoice;
            scanf("%d", &subChoice);
            getchar();
            switch(subChoice)
            {
                case 1:
                    searchByBHYT("data/patient.txt");
                    break;
                case 2:
                    searchByPhoneNumbers("data/patient.txt");
                    break;
                case 3:
                    searchByfullName("data/patient.txt");
                    break;
                default:
                    printf("Chon khong hop le!\n");
            }
            break;
            case 3:
                printf("-> Dat lich kham\n");
                // gọi hàm đặt lịch ở đây
                break;
            case 4:
                printf("-> Quan ly lich hen\n");
                break;
            case 5:
                printf("-> Luu / Doc file\n");
                break;
            case 0:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Chon khong hop le, vui long chon lai!\n");
        }

    } while(choice != 0);

    return 0;
}