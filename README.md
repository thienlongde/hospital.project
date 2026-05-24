# hospital.project
BTL KTLT
//
Thành Viên Nhóm : Võ Tấn Tiến, Nguyễn Trung Tỉnh, Nguyễn Quang Nhân Kiệt, Huỳnh Quang Khải, Nguyễn Trần Thiên Long.
//
Lí do chọn đề tài : 
Ứng dụng quản lí và đặt lịch phòng khám là một ứng dụng được xây dựng dựa trên ngôn ngữ C thuần và việc áp dụng những kiến thức được học từ môn kỹ thuật lập trình và tin học đại cương. Ý tưởng xây dựng ứng dụng dựa trên bối cảnh mọi người phải xếp hàng chờ đợi để được khám bệnh. Để giải quyết việc đó ứng dụng quản lí và đặt lịch khám cho phép người dùng đặt lịch và kiểm tra thông tin của mình chỉ bằng cái nhấp chuột.
//
Hướng dẫn sử dụng :
Bước 1 : tải toàn bộ file mã nguồn dự án qua link github "https://github.com/thienlongde/hospital.project.git"
Bước 2 : mở file vừa tải về trên vs code hoặc dev c++, mở màn hình terminal và chạy lệnh 
gcc -std=c99 src/main.c src/UI.c src/patient.c src/booking.c src/search.c src/appointment.c -Include -o HospitalManager.exe
Bước 3 : chạy file thực thi vừa tạo " HospitalManager.exe "
Lưu ý : console phải hỗ trợ utf8 ( code page 65001) để hiển thị tiếng việt có dấu. Thư mục data phải tồn tại cùng cấp với thư mục .exe trước khi chạy.
//
