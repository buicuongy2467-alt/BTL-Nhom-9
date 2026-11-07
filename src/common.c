#include "common.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

KhachHang *dsKH = NULL;
int slKH = 0;
int capKH = 0;
XeMay *dsXe = NULL;
int slXe = 0;
int capXe = 0;
DichVuBaoDuong *dsDV = NULL;
int slDV = 0;
int capDV = 0;
PhieuSuaChua *dsPhieu = NULL;
int slPhieu = 0;
int capPhieu = 0;

Ngay layNgayHienTai() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    Ngay ngayHienTai;
    ngayHienTai.ngay = tm_info->tm_mday;
    ngayHienTai.thang = tm_info->tm_mon + 1;
    ngayHienTai.nam = tm_info->tm_year + 1900;
    return ngayHienTai;
}

void moRongDanhSach() {
    if (slKH >= capKH) {
        capKH = capKH == 0 ? 10 : capKH * 2;
        KhachHang *temp = (KhachHang*)realloc(dsKH, capKH * sizeof(KhachHang));
        if (temp != NULL) dsKH = temp;
    }
    if (slXe >= capXe) {
        capXe = capXe == 0 ? 10 : capXe * 2;
        XeMay *temp = (XeMay*)realloc(dsXe, capXe * sizeof(XeMay));
        if (temp != NULL) dsXe = temp;
    }
    if (slDV >= capDV) {
        capDV = capDV == 0 ? 10 : capDV * 2;
        DichVuBaoDuong *temp = (DichVuBaoDuong*)realloc(dsDV, capDV * sizeof(DichVuBaoDuong));
        if (temp != NULL) dsDV = temp;
    }
    if (slPhieu >= capPhieu) {
        capPhieu = capPhieu == 0 ? 10 : capPhieu * 2;
        PhieuSuaChua *temp = (PhieuSuaChua*)realloc(dsPhieu, capPhieu * sizeof(PhieuSuaChua));
        if (temp != NULL) dsPhieu = temp;
    }
}

void xoaXuongDong(char x[]) {
    size_t len = strlen(x);
    while (len > 0 && (x[len - 1] == '\n' || x[len - 1] == '\r')) {
        x[--len] = '\0';
    }
}

int soSanhNgay(Ngay n1, Ngay n2) {
    if (n1.nam != n2.nam) return n1.nam - n2.nam;
    if (n1.thang != n2.thang) return n1.thang - n2.thang;
    return n1.ngay - n2.ngay;
}
