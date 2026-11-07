# Quản lý tiệm rửa xe và bảo dưỡng xe máy

# Quản lý tiệm rửa xe và bảo dưỡng xe máy

Chương trình C quản lý khách hàng, xe máy, dịch vụ và phiếu sửa chữa tại tiệm.

## Yêu cầu

- GCC hoặc trình biên dịch C tương thích C11.
- Windows, Linux hoặc macOS có môi trường chạy chương trình C.

## Cấu trúc mã nguồn

```text
include/
  models.h       # Kiểu dữ liệu và trạng thái dùng chung
  common.h       # Khai báo hàm tiện ích
  customers.h    # Khai báo nghiệp vụ khách hàng, xe máy
  service.h      # Khai báo nghiệp vụ phiếu dịch vụ, bảo dưỡng
  storage.h      # Khai báo đọc/ghi và quản lý bộ nhớ
  reports.h      # Khai báo đăng nhập, khuyến mãi, báo cáo
src/
  main.c         # Menu và điểm vào chương trình
  common.c       # Trạng thái toàn cục và hàm tiện ích
  customers.c    # Nghiệp vụ khách hàng, xe máy
  service.c      # Lập phiếu, thanh toán, lịch và thống kê kho
  storage.c      # Khởi tạo, đọc/ghi, giải phóng dữ liệu
  reports.c      # Đăng nhập, khuyến mãi, doanh thu
```

## Biên dịch và chạy

### Windows (PowerShell)

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/common.c src/customers.c src/service.c src/storage.c src/reports.c -o quanlytiem.exe
.\quanlytiem.exe
```

### Linux hoặc macOS

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/common.c src/customers.c src/service.c src/storage.c src/reports.c -o quanlytiem
./quanlytiem
```

## Chức năng

## Chức năng

1. Tiếp nhận xe và lưu thông tin khách hàng, xe máy.
2. Lập phiếu dịch vụ, sử dụng phụ tùng và tính tổng tiền.
3. Thanh toán và xuất hóa đơn thành tệp văn bản.
4. Xem lịch hẹn bảo dưỡng đã sắp xếp theo ngày.
5. Thống kê dịch vụ, phụ tùng đã thay và lượng tồn kho.

Chương trình hiện lưu dữ liệu khách hàng, xe, phiếu và tồn kho trong bộ nhớ; dữ liệu được khởi tạo lại khi chạy chương trình lần sau. Hóa đơn được ghi thành tệp trong thư mục chạy chương trình.
