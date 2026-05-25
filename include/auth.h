#ifndef AUTH_H
#define AUTH_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define ROLE_ADMIN   0
#define ROLE_STAFF   1
#define ROLE_PATIENT 2

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int  role;          // ROLE_ADMIN / ROLE_STAFF / ROLE_PATIENT
    int  isLoggedIn;
} User;

// Đăng nhập — trả về 1 nếu thành công, 0 nếu thất bại
int  loginUser(const char *userFile, User *outUser);

// Kiểm tra quyền
int  hasPermission(const User *user, int requiredRole);

// In tên vai trò
const char *getRoleName(int role);

#endif