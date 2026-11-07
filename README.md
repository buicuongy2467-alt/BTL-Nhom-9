# Quản lý tiệm rửa xe và bảo dưỡng xe máy

Chương trình dòng lệnh viết bằng C để quản lý khách hàng, xe máy, dịch vụ, phụ tùng và phiếu sửa chữa tại tiệm.

## Yêu cầu

- GCC hoặc trình biên dịch C tương thích C11.
- Windows, Linux hoặc macOS.

## Cấu trúc dự án

```text
include/
  models.h       # Các kiểu dữ liệu và trạng thái dùng chung
  common.h       # Khai báo hàm tiện ích
  customers.h    # Khai báo nghiệp vụ khách hàng, xe máy
  service.h      # Khai báo nghiệp vụ dịch vụ, bảo dưỡng
  storage.h      # Khai báo khởi tạo và lưu dữ liệu
  reports.h      # Khai báo đăng nhập, khuyến mãi, báo cáo
src/
  main.c         # Menu và điểm vào chương trình
  common.c       # Trạng thái toàn cục và hàm tiện ích
  customers.c    # Tiếp nhận và tra cứu khách hàng, xe máy
  service.c      # Phiếu dịch vụ, thanh toán, lịch hẹn, thống kê kho
  storage.c      # Khởi tạo, đọc/ghi dữ liệu, giải phóng bộ nhớ
  reports.c      # Đăng nhập, khuyến mãi, doanh thu
```

## Biên dịch và chạy

Chạy các lệnh từ thư mục gốc của dự án.

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

- Đăng nhập với quyền nhân viên hoặc chủ tiệm. Quyền chủ tiệm yêu cầu mật khẩu quản trị.
- Tiếp nhận xe: tìm khách hàng theo số điện thoại, tạo khách hàng mới nếu chưa có và đăng ký xe.
- Lập phiếu dịch vụ/phụ tùng, ghi ngày lập, số lượng, đơn giá và tổng tiền; kiểm tra tồn kho phụ tùng.
- Thanh toán phiếu đang chờ, áp dụng giảm 5% từ 500.000 VND hoặc 10% từ 1.000.000 VND, cập nhật tồn kho và ghi hóa đơn thành tệp văn bản.
- Xem lịch hẹn bảo dưỡng đã thanh toán, sắp xếp theo ngày; kiểm tra lịch đến hạn/quá hạn khi khởi động.
- Thống kê số phụ tùng đã thay, tồn kho và tình trạng cần nhập thêm.
- Tra cứu khách hàng theo số điện thoại hoặc xe theo biển số.
- Xem chương trình khuyến mãi; chủ tiệm có thêm chức năng tính doanh thu theo tháng.

## Dữ liệu

Danh mục dịch vụ và phụ tùng được khởi tạo sẵn khi chạy chương trình. Khi thoát, chương trình ghi dữ liệu ra các tệp nhị phân `khachhang.bin`, `xe.bin`, `dichvu.bin` và `phieu.bin`; hóa đơn được ghi thành tệp `HoaDon_<bienSo>_Phieu<id>.txt` trong thư mục chạy chương trình.

**Lưu ý:** phiên bản hiện tại chưa gọi hàm đọc các tệp `.bin` khi khởi động. Vì vậy dữ liệu đã lưu không được nạp lại vào chương trình ở lần chạy tiếp theo.
