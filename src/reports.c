#include "reports.h"

#include <stdio.h>

int dangNhapKhoiTao() {
    int luaChon, matKhau;
    printf("\n================================================\n");
    printf("         HE THONG DANG NHAP QUAN LY\n");
    printf("================================================\n");
    printf("1. Dang nhap quyen Nhan vien\n");
    printf("2. Dang nhap quyen Ong chu\n");
    printf("Chon vai tro (1/2): ");
    scanf("%d", &luaChon);

    if (luaChon == 2) {
        printf("Nhap mat khau quan tri: ");
        scanf("%d", &matKhau);
        if (matKhau == 12345678) { // Mat khau cua ong chu
            printf("=> Dang nhap thanh cong: QUYEN ONG CHU\n");
            return 1;
        } else {
            printf("=> Sai mat khau! Tu dong chuyen ve QUYEN NHAN VIEN.\n");
        }
    } else {
        printf("=> Dang nhap thanh cong: QUYEN NHAN VIEN\n");
    }
    return 0; // 0: Nhan vien , 1: Ong chu
}

void tinhDoanhThuThang() {
    printf("\n================================================\n");
    printf("               TINH DOANH THU THANG\n");
    printf("================================================\n");
    int thang, nam;
    long tongDoanhThu = 0;
    int soPhieuDaThu = 0;

    printf("Nhap thang va nam can tinh (VD: 11 2026): ");
    scanf("%d %d", &thang, &nam);

    for(int i = 0; i < slPhieu; i++) {
        if(dsPhieu[i].trangThai == 1 && dsPhieu[i].ngayLap.thang == thang && dsPhieu[i].ngayLap.nam == nam) {
            tongDoanhThu += dsPhieu[i].tongTien;
            soPhieuDaThu++;
        }
    }

    printf("\n=> KET QUA THONG KE THANG %02d/%04d:\n", thang, nam);
    printf(" - So phieu da thanh toan: %d\n", soPhieuDaThu);
    printf(" - TONG DOANH THU        : %ld VND\n", tongDoanhThu);
}

void khuyenMaiChoDonHang() {
    printf("\n================================================\n");
    printf("         CHUONG TRINH KHUYEN MAI HIEN TAI\n");
    printf("================================================\n");
    printf("1. Giam 5%% cho tong hoa don tu 500,000 VND tro len.\n");
    printf("2. Giam 10%% cho tong hoa don tu 1,000,000 VND tro len.\n");
    printf("------------------------------------------------\n");
    printf("=> Chiet khau se duoc tu dong ap dung khi thanh toan!\n");
}
