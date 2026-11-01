# Nghiệp vụ còn thiếu và lỗi cần xử lý

Tài liệu này đối chiếu yêu cầu đề tài quản lý tiệm rửa xe, bảo dưỡng xe máy với chương trình trong [`main.c`](./main.c).

## Nghiệp vụ còn thiếu hoặc chưa hoàn thiện

1. **Dùng mảng `struct` động**
   - Yêu cầu đề tài nêu việc sử dụng mảng `struct` động.
   - Hiện khách hàng, xe, dịch vụ và phiếu dùng mảng cố định 100 phần tử; chi tiết phiếu cố định 20 phần tử.
   - Vị trí: khai báo các cấu trúc và mảng dữ liệu trong [`main.c`](./main.c#L9).

2. **Nhắc lịch bảo dưỡng**
   - Chương trình có lưu ngày hẹn và hiển thị danh sách lịch đã sắp xếp theo ngày.
   - Chưa thông báo lịch sắp tới hoặc lịch đã đến hạn.
   - Vị trí: [`sapXepLichBaoDuong`](./main.c#L293).

3. **Phân biệt dịch vụ với phụ tùng**
   - Rửa xe, thay nhớt và phụ tùng đang dùng chung một danh mục.
   - Khi thanh toán, mọi mục đều được tính vào thống kê “đã thay”; dịch vụ như rửa xe cũng bị trừ tồn kho như phụ tùng.
   - Vị trí: danh mục khởi tạo và phần cập nhật thống kê khi thanh toán trong [`main.c`](./main.c#L59).

4. **Tra cứu khách hàng/xe từ menu**
   - Đã có hàm tìm khách bằng số điện thoại và tìm xe bằng biển số, được dùng trong các luồng hiện tại.
   - Chưa có lựa chọn riêng để người dùng chủ động tra cứu từ menu.
   - Vị trí: [`timKhachHangTheoSDT`](./main.c#L72), [`timXeTheoBienSo`](./main.c#L79) và menu trong [`main.c`](./main.c#L345).

## Lỗi và rủi ro cần sửa

1. **Kiểm tra dữ liệu nhập**
   - Số lượng chưa được chặn ở giá trị dương; số âm có thể làm sai tổng tiền và tồn kho.
   - Ngày lập phiếu và ngày hẹn chưa được kiểm tra hợp lệ.
   - `scanf` chưa xử lý trường hợp người dùng nhập chữ hoặc dữ liệu sai định dạng, có thể làm luồng nhập bị kẹt.
   - Vị trí: nhập phiếu trong [`main.c`](./main.c#L152) và nhập thanh toán/ngày hẹn trong [`main.c`](./main.c#L199).

2. **Kiểm tra giới hạn mảng trước khi thêm dữ liệu**
   - Chưa chặn số lượng khách hàng, xe, phiếu hoặc chi tiết vượt sức chứa; có thể ghi vượt mảng.
   - Các giới hạn hiện tại được khai báo tại [`main.c`](./main.c#L39).

3. **Chỉ cập nhật thanh toán sau khi tạo hóa đơn thành công**
   - Phiếu được đánh dấu đã thanh toán và số liệu “đã thay” được cộng trước khi xác nhận file hóa đơn mở/ghi thành công.
   - Nếu tạo hóa đơn thất bại, trạng thái và thống kê đã đổi dù không có hóa đơn.
   - Vị trí: [`thanhToanVaInHoaDon`](./main.c#L193).

4. **Thay `fflush(stdin)` bằng cách xử lý nhập khả chuyển**
   - `fflush(stdin)` không có hành vi được chuẩn C bảo đảm cho luồng nhập; kết quả có thể khác theo trình biên dịch.
   - Vị trí: các luồng nhập như [`tiepNhanXe`](./main.c#L90) và [`thanhToanVaInHoaDon`](./main.c#L193).

5. **Đối chiếu chủ xe khi biển số đã tồn tại**
   - Khi biển số đã có, chương trình chỉ báo xe tồn tại; chưa thông báo xe đang thuộc khách hàng nào hoặc xử lý trường hợp nhập nhầm khách.
   - Vị trí: [`tiepNhanXe`](./main.c#L90).

## Thứ tự ưu tiên đề xuất

1. Chặn dữ liệu nhập sai và giới hạn mảng để tránh sai tiền, tồn kho hoặc ghi vượt bộ nhớ.
2. Đảm bảo trạng thái thanh toán chỉ hoàn tất sau khi hóa đơn được tạo thành công.
3. Phân biệt dịch vụ với phụ tùng để thống kê và quản lý tồn kho đúng loại.
4. Bổ sung tra cứu riêng và nhắc lịch bảo dưỡng.
5. Chuyển các mảng cố định sang cấu trúc động để đáp ứng yêu cầu đề tài.
