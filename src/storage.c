#include "storage.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

void khoiTaoDuLieu() {
    moRongDanhSach();
    dsDV[slDV++] = (DichVuBaoDuong){1, "Rua xe bot tuyet", 50000, 999, 0, 1}; // Loai 1: Dich vu
    moRongDanhSach();
    dsDV[slDV++] = (DichVuBaoDuong){2, "Thay nhot ban tong hop", 120000, 50, 0, 0}; // Loai 0: Phu tung
    moRongDanhSach();
    dsDV[slDV++] = (DichVuBaoDuong){3, "Thay bugi", 80000, 5, 0, 0};
    moRongDanhSach();
    dsDV[slDV++] = (DichVuBaoDuong){4, "Bao duong noi", 200000, 30, 0, 1};
    moRongDanhSach();
    dsDV[slDV++] = (DichVuBaoDuong){5, "Day curoa", 350000, 8, 0, 0};
}

void giaiPhongBoNho() {
    free(dsKH);
    free(dsXe);
    free(dsDV);
    for(int i=0; i<slPhieu; i++) {
        free(dsPhieu[i].dsChiTiet);
    }
    free(dsPhieu);
}

void luuDuLieu() {
    // 1. Luu khach hang
    FILE *fKH = fopen("khachhang.bin", "wb");
    if (fKH != NULL) {
        fwrite(&slKH, sizeof(int), 1, fKH);
        fwrite(dsKH, sizeof(KhachHang), slKH, fKH);
        fclose(fKH);
    }

    // 2. Luu xe may
    FILE *fXe = fopen("xe.bin", "wb");
    if (fXe != NULL) {
        fwrite(&slXe, sizeof(int), 1, fXe);
        fwrite(dsXe, sizeof(XeMay), slXe, fXe);
        fclose(fXe);
    }

    // 3. Luu dich vu / phu tung
    FILE *fDV = fopen("dichvu.bin", "wb");
    if (fDV != NULL) {
        fwrite(&slDV, sizeof(int), 1, fDV);
        fwrite(dsDV, sizeof(DichVuBaoDuong), slDV, fDV);
        fclose(fDV);
    }

    // 4. Luu phieu sua chua (Xu ly rieng mang dong dsChiTiet)
    FILE *fPhieu = fopen("phieu.bin", "wb");
    if (fPhieu != NULL) {
        fwrite(&slPhieu, sizeof(int), 1, fPhieu);
        for(int i = 0; i < slPhieu; i++) {
            fwrite(&dsPhieu[i], sizeof(PhieuSuaChua), 1, fPhieu);
            // Ghi tiep mang dong chi tiet cua phieu nay
            if (dsPhieu[i].soChiTiet > 0) {
                fwrite(dsPhieu[i].dsChiTiet, sizeof(ChiTietSuaChua), dsPhieu[i].soChiTiet, fPhieu);
            }
        }
        fclose(fPhieu);
    }
}

void docDuLieu() {
    // 1. Doc khach hang
    FILE *fKH = fopen("khachhang.bin", "rb");
    if (fKH != NULL) {
        fread(&slKH, sizeof(int), 1, fKH);
        capKH = slKH == 0 ? 10 : slKH;
        dsKH = (KhachHang*)malloc(capKH * sizeof(KhachHang));
        if (slKH > 0) fread(dsKH, sizeof(KhachHang), slKH, fKH);
        fclose(fKH);
    }

    // 2. Doc xe may
    FILE *fXe = fopen("xe.bin", "rb");
    if (fXe != NULL) {
        fread(&slXe, sizeof(int), 1, fXe);
        capXe = slXe == 0 ? 10 : slXe;
        dsXe = (XeMay*)malloc(capXe * sizeof(XeMay));
        if (slXe > 0) fread(dsXe, sizeof(XeMay), slXe, fXe);
        fclose(fXe);
    }

    // 3. Doc dich vu (Neu khong co file thi khoi tao mac dinh)
    FILE *fDV = fopen("dichvu.bin", "rb");
    if (fDV != NULL) {
        fread(&slDV, sizeof(int), 1, fDV);
        capDV = slDV == 0 ? 10 : slDV;
        dsDV = (DichVuBaoDuong*)malloc(capDV * sizeof(DichVuBaoDuong));
        if (slDV > 0) fread(dsDV, sizeof(DichVuBaoDuong), slDV, fDV);
        fclose(fDV);
    } else {
        khoiTaoDuLieu(); // Goi data mac dinh neu la lan chay dau tien
    }

    // 4. Doc phieu sua chua
    FILE *fPhieu = fopen("phieu.bin", "rb");
    if (fPhieu != NULL) {
        fread(&slPhieu, sizeof(int), 1, fPhieu);
        capPhieu = slPhieu == 0 ? 10 : slPhieu;
        dsPhieu = (PhieuSuaChua*)malloc(capPhieu * sizeof(PhieuSuaChua));
        
        for(int i = 0; i < slPhieu; i++) {
            fread(&dsPhieu[i], sizeof(PhieuSuaChua), 1, fPhieu);
            // Chu y: con tro dsChiTiet doc len tu file la dia chi rac (invalid address).
            // Phai cap phat lai bo nho moi va doc du lieu vao do.
            dsPhieu[i].capacityChiTiet = dsPhieu[i].soChiTiet == 0 ? 5 : dsPhieu[i].soChiTiet;
            dsPhieu[i].dsChiTiet = (ChiTietSuaChua*)malloc(dsPhieu[i].capacityChiTiet * sizeof(ChiTietSuaChua));
            
            if (dsPhieu[i].soChiTiet > 0) {
                fread(dsPhieu[i].dsChiTiet, sizeof(ChiTietSuaChua), dsPhieu[i].soChiTiet, fPhieu);
            }
        }
        fclose(fPhieu);
    }
}
