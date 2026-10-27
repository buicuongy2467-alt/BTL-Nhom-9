# Quản lý tiệm rửa xe và bảo dưỡng xe máy

Chương trình C quản lý khách hàng, xe máy, dịch vụ và phiếu sửa chữa tại tiệm.

## Yêu cầu

- GCC hoặc trình biên dịch C tương thích C11.
- Windows, Linux hoặc macOS có môi trường chạy chương trình C.

## Biên dịch và chạy

### Windows (PowerShell)

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o quanlytiem.exe
.\quanlytiem.exe
```

### Linux hoặc macOS

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o quanlytiem
./quanlytiem
```

## Chức năng

1. Tiếp nhận xe và lưu thông tin khách hàng, xe máy.
2. Lập phiếu dịch vụ, sử dụng phụ tùng và tính tổng tiền.
3. Thanh toán và xuất hóa đơn thành tệp văn bản.
4. Xem lịch hẹn bảo dưỡng đã sắp xếp theo ngày.
5. Thống kê dịch vụ, phụ tùng đã thay và lượng tồn kho.

Chương trình hiện lưu dữ liệu khách hàng, xe, phiếu và tồn kho trong bộ nhớ; dữ liệu được khởi tạo lại khi chạy chương trình lần sau. Hóa đơn được ghi thành tệp trong thư mục chạy chương trình.
