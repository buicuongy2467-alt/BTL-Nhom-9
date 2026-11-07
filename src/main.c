#include "customers.h"
#include "reports.h"
#include "service.h"
#include "storage.h"

#include <stdio.h>

int main() {
    khoiTaoDuLieu();
    int quyen = dangNhapKhoiTao();
    kiemTraNhacLichBaoDuong(); 
    int chon;
    do {
        puts("\n================================================");
        puts("       QUAN LY TIEM RUA & BAO DUONG XE MAY");
        puts("================================================");
        puts("  1. Tiep nhan xe");
        puts("  2. Lap phieu dich vu / phu tung");
        puts("  3. Thanh toan va xuat hoa don");
        puts("  4. Xem lich hen bao duong");
        puts("  5. Thong ke dich vu / phu tung");
        puts("  6. Tra cuu khach hang / xe");
        puts("  7. Khuyen mai cho don hang");
         if (quyen == 1) {
            puts("  8. [Ong chu] Tinh tong doanh thu thang");
        }
        puts("  0. Thoat");
        printf("Chon chuc nang: ");
        fflush(stdout);
        scanf("%d", &chon);
        
        switch(chon) {
            case 1: tiepNhanXe(); break;
            case 2: lapPhieuDichVu(); break;
            case 3: thanhToanVaInHoaDon(); break;
            case 4: sapXepLichBaoDuong(); break;
            case 5: thongKePhuTung(); break;
            case 6: traCuuThongTin(); break;
            case 7: khuyenMaiChoDonHang(); break;
            case 8:
            	if (quyen == 1) tinhDoanhThuThang();
                else printf("=> Ban khong co quyen xem doanh thu!\n");
                break;
            case 0:
            luuDuLieu(); 
                giaiPhongBoNho();
                printf("Thoat chuong trinh. Tam biet.\n"); 
                break;
            default: printf("Lua chon khong hop le.\n"); break;
        }
    } while(chon != 0);

    return 0;
}
