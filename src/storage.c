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
        if (slKH < 0 || slKH > 100000) slKH = 0; // Bo loc chong tran bo nho
        capKH = slKH == 0 ? 10 : slKH;
        dsKH = (KhachHang*)malloc(capKH * sizeof(KhachHang));
        if (slKH > 0) fread(dsKH, sizeof(KhachHang), slKH, fKH);
        fclose(fKH);
        printf(" Da nap thanh cong %d khach hang.\n", slKH);
    } else {
        printf(" Khong tim thay khachhang.bin. Khoi tao vung nho trong.\n");
        capKH = 10; dsKH = (KhachHang*)malloc(capKH * sizeof(KhachHang));
    }

    // 2. Doc xe may
    FILE *fXe = fopen("xe.bin", "rb");
    if (fXe != NULL) {
        fread(&slXe, sizeof(int), 1, fXe);
        if (slXe < 0 || slXe > 100000) slXe = 0;
        capXe = slXe == 0 ? 10 : slXe;
        dsXe = (XeMay*)malloc(capXe * sizeof(XeMay));
        if (slXe > 0) fread(dsXe, sizeof(XeMay), slXe, fXe);
        fclose(fXe);
        printf(" Da nap thanh cong %d xe may.\n", slXe);
    } else {
        printf(" Khong tim thay xe.bin. Khoi tao vung nho trong.\n");
        capXe = 10; dsXe = (XeMay*)malloc(capXe * sizeof(XeMay));
    }

    // 3. Doc dich vu
    FILE *fDV = fopen("dichvu.bin", "rb");
    if (fDV != NULL) {
        fread(&slDV, sizeof(int), 1, fDV);
        if (slDV < 0 || slDV > 100000) slDV = 0;
        capDV = slDV == 0 ? 10 : slDV;
        dsDV = (DichVuBaoDuong*)malloc(capDV * sizeof(DichVuBaoDuong));
        if (slDV > 0) fread(dsDV, sizeof(DichVuBaoDuong), slDV, fDV);
        fclose(fDV);
        printf(" Da nap thanh cong %d dich vu/phu tung.\n", slDV);
    } else {
        printf(" Khong tim thay dichvu.bin. Tu dong tao du lieu mac dinh...\n");
        khoiTaoDuLieu();
    }

    // 4. Doc phieu sua chua
    FILE *fPhieu = fopen("phieu.bin", "rb");
    if (fPhieu != NULL) {
        fread(&slPhieu, sizeof(int), 1, fPhieu);
        if (slPhieu < 0 || slPhieu > 100000) slPhieu = 0;
        capPhieu = slPhieu == 0 ? 10 : slPhieu;
        dsPhieu = (PhieuSuaChua*)malloc(capPhieu * sizeof(PhieuSuaChua));
        
        for(int i = 0; i < slPhieu; i++) {
            fread(&dsPhieu[i], sizeof(PhieuSuaChua), 1, fPhieu);
            
            // Xoa cac con tro mang dia chi rac doc tu file
            dsPhieu[i].dsChiTiet = NULL; 
            dsPhieu[i].capacityChiTiet = dsPhieu[i].soChiTiet == 0 ? 5 : dsPhieu[i].soChiTiet;
            
            if (dsPhieu[i].capacityChiTiet > 0) {
                dsPhieu[i].dsChiTiet = (ChiTietSuaChua*)malloc(dsPhieu[i].capacityChiTiet * sizeof(ChiTietSuaChua));
            }
            
            if (dsPhieu[i].soChiTiet > 0 && dsPhieu[i].dsChiTiet != NULL) {
                fread(dsPhieu[i].dsChiTiet, sizeof(ChiTietSuaChua), dsPhieu[i].soChiTiet, fPhieu);
            }
        }
        fclose(fPhieu);
        printf(" Da nap thanh cong %d phieu sua chua.\n", slPhieu);
    } else {
        printf(" Khong tim thay phieu.bin. Khoi tao vung nho trong.\n");
        capPhieu = 10; dsPhieu = (PhieuSuaChua*)malloc(capPhieu * sizeof(PhieuSuaChua));
    }
}
