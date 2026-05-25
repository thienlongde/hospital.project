#include "../include/auth.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *getRoleName(int role) {
    switch (role) {
        case ROLE_ADMIN:   return "Admin";
        case ROLE_STAFF:   return "Nhan vien";
        case ROLE_PATIENT: return "Benh nhan";
        default:           return "Khong xac dinh";
    }
}

static int parseRole(const char *roleStr) {
    if (strcmp(roleStr, "admin")   == 0) return ROLE_ADMIN;
    if (strcmp(roleStr, "staff")   == 0) return ROLE_STAFF;
    if (strcmp(roleStr, "patient") == 0) return ROLE_PATIENT;
    return -1;
}

static void stripCRLF(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len-1] == '\r' || s[len-1] == '\n' || s[len-1] == ' ')) {
        s[--len] = '\0';
    }
}

int loginUser(const char *userFile, User *outUser) {
    char inputUser[MAX_USERNAME];
    char inputPass[MAX_PASSWORD];

    printf("\n========== DANG NHAP HE THONG ==========\n");

    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    while (attempts < MAX_ATTEMPTS) {
        printf("Ten dang nhap: ");
        fgets(inputUser, sizeof(inputUser), stdin);
        stripCRLF(inputUser);

        printf("Mat khau    : ");
        fgets(inputPass, sizeof(inputPass), stdin);
        stripCRLF(inputPass);

        FILE *f = fopen(userFile, "r");
        printf("[DEBUG] Mo file: %s => %s\n", userFile, f ? "OK" : "THAT BAI");
        if (!f) {
        // In thư mục hiện tại
            system("cd");
        return 0;
        }

        char line[256];
        int found = 0;

        // Bỏ qua dòng tiêu đề
        fgets(line, sizeof(line), f);

        while (fgets(line, sizeof(line), f)) {
            stripCRLF(line);
            if (strlen(line) == 0) continue;

            char *uname = strtok(line, ",");
            char *upass = strtok(NULL, ",");
            char *urole = strtok(NULL, ",");

            if (!uname || !upass || !urole) continue;

            stripCRLF(uname);
            stripCRLF(upass);
            stripCRLF(urole);

            // DEBUG
            printf(">> Doc: [%s] [%s] [%s]\n", uname, upass, urole);
            printf(">> Nhap: [%s] [%s]\n", inputUser, inputPass);
            printf(">> So sanh user: %d | pass: %d\n",
                   strcmp(uname, inputUser), strcmp(upass, inputPass));

            if (strcmp(uname, inputUser) == 0 &&
                strcmp(upass, inputPass) == 0) {
                int role = parseRole(urole);
                if (role == -1) {
                    printf("[LOI] Role khong hop le: [%s]\n", urole);
                    continue;
                }
                strncpy(outUser->username, uname, MAX_USERNAME - 1);
                outUser->username[MAX_USERNAME - 1] = '\0';
                strncpy(outUser->password, upass, MAX_PASSWORD - 1);
                outUser->password[MAX_PASSWORD - 1] = '\0';
                outUser->role       = role;
                outUser->isLoggedIn = 1;
                found = 1;
                break;
            }
        }
        fclose(f);

        if (found) {
            printf("\n[OK] Dang nhap thanh cong! Xin chao %s (%s)\n",
                   outUser->username, getRoleName(outUser->role));
            return 1;
        }

        attempts++;
        printf("[LOI] Sai ten dang nhap hoac mat khau! Con %d lan.\n",
               MAX_ATTEMPTS - attempts);
    }

    printf("[CANH BAO] Dang nhap that bai qua %d lan!\n", MAX_ATTEMPTS);
    return 0;
}

int hasPermission(const User *user, int requiredRole) {
    if (!user->isLoggedIn) return 0;
    return user->role <= requiredRole;
}

static int isUsernameExists(const char *userFile, const char *username) {
    FILE *f = fopen(userFile, "r");
    if (!f) return 0;

    char line[256];
    // Bỏ qua dòng tiêu đề
    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f)) {
        stripCRLF(line);
        if (strlen(line) == 0) continue;

        char copy[256];
        strncpy(copy, line, sizeof(copy) - 1);
        copy[sizeof(copy) - 1] = '\0';

        char *uname = strtok(copy, ",");
        if (uname && strcmp(uname, username) == 0) {
            fclose(f);
            return 1;  // Username exists
        }
    }
    fclose(f);
    return 0;  // Username does not exist
}

int signupPatient(const char *userFile) {
    char newUsername[MAX_USERNAME];
    char newPassword[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD];

    printf("\n========== DANG KY TAI KHOAN BENH NHAN ==========\n");

    // Input username
    printf("Ten dang nhap (toi thieu 4 ky tu): ");
    fgets(newUsername, sizeof(newUsername), stdin);
    stripCRLF(newUsername);

    // Validate username length
    if (strlen(newUsername) < 4) {
        printf("[LOI] Ten dang nhap phai co toi thieu 4 ky tu!\n");
        return 0;
    }

    // Check if username already exists
    if (isUsernameExists(userFile, newUsername)) {
        printf("[LOI] Ten dang nhap da ton tai! Vui long chon ten khac.\n");
        return 0;
    }

    // Input password
    printf("Mat khau (toi thieu 6 ky tu)    : ");
    fgets(newPassword, sizeof(newPassword), stdin);
    stripCRLF(newPassword);

    // Validate password length
    if (strlen(newPassword) < 6) {
        printf("[LOI] Mat khau phai co toi thieu 6 ky tu!\n");
        return 0;
    }

    // Confirm password
    printf("Xac nhan mat khau              : ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    stripCRLF(confirmPassword);

    // Check if passwords match
    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("[LOI] Mat khau xac nhan khong khop!\n");
        return 0;
    }

    // Write new user to file
    FILE *f = fopen(userFile, "a");
    if (!f) {
        printf("[LOI] Khong the mo file de luu du lieu!\n");
        return 0;
    }

    fprintf(f, "%s,%s,patient\n", newUsername, newPassword);
    fclose(f);

    printf("\n[OK] Dang ky thanh cong! Ban da co the dang nhap voi tai khoan cua minh.\n");
    return 1;
}