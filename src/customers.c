#include "customers.h"
#include "common.h"

#include <stdio.h>
#include <string.h>

int timKhachHangTheoSDT(char* sdt) {
    for(int i=0; i<slKH; i++) {
        if(strcmp(dsKH[i].sdt, sdt) == 0) return i;
    }
    return -1;
}

int timXeTheoBienSo(char* bienSo) {
    for(int i=0; i<slXe; i++) {
        if(strcmp(dsXe[i].bienSo, bienSo) == 0) return i;
    }
    return -1;
}

void traCuuThongTin() {
    int luaChon;
    printf("\n================================================\n");
    printf("                  TRA CUU THONG TIN\n");
    printf("================================================\n");
    printf("1. Tra cuu khach hang theo so dien thoai\n");
    printf("2. Tra cuu xe may theo bien so\n");
    printf("Chon: ");
    scanf("%d", &luaChon);
    fflush(stdin);

    if (luaChon == 1) {
        char sdt[15];
        printf("Nhap SDT can tim: ");
        fgets(sdt, sizeof(sdt), stdin); xoaXuongDong(sdt);
        int idx = timKhachHangTheoSDT(sdt);
        if (idx != -1) {
            printf("\n=> Tim thay khach hang:\n");
            printf("Ma KH: %d | Ten: %s | SDT: %s\n", dsKH[idx].id, dsKH[idx].ten, dsKH[idx].sdt);
            printf("Cac xe cua khach hang:\n");
            int foundXe = 0;
            for(int i=0; i<slXe; i++) {
                if(dsXe[i].idKhachHang == dsKH[idx].id) {
                    printf(" - Bien so: %s | Dong xe: %s\n", dsXe[i].bienSo, dsXe[i].dongXe);
                    foundXe = 1;
                }
            }
            if (!foundXe) printf(" (Khach hang chua dang ky xe nao)\n");
        } else {
            printf("=> Khong tim thay khach hang co SDT: %s\n", sdt);
        }
    } else if (luaChon == 2) {
        char bienSo[20];
        printf("Nhap bien so xe can tim: ");
        fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
        int idxXe = timXeTheoBienSo(bienSo);
        if (idxXe != -1) {
            printf("\n=> Tim thay xe:\n");
            printf("Bien so: %s | Dong xe: %s\n", dsXe[idxXe].bienSo, dsXe[idxXe].dongXe);
            for(int i=0; i<slKH; i++) {
                if(dsKH[i].id == dsXe[idxXe].idKhachHang) {
                    printf("Chu xe: %s | SDT: %s\n", dsKH[i].ten, dsKH[i].sdt);
                    break;
                }
            }
        } else {
            printf("=> Khong tim thay xe co bien so: %s\n", bienSo);
        }
    } else {
        printf("Lua chon khong hop le.\n");
    }
}

void tiepNhanXe() {
    moRongDanhSach();
    printf("\n================================================\n");
    printf("                    TIEP NHAN XE\n");
    printf("================================================\n");
    char sdt[15], bienSo[20];
    
    printf("Nhap SDT khach hang: ");
    fflush(stdin); fgets(sdt, sizeof(sdt), stdin); xoaXuongDong(sdt);
    
    int idxKH = timKhachHangTheoSDT(sdt);
    if (idxKH == -1) {
        printf("Khach hang moi.\n");
        printf("Nhap ten khach hang: ");
        fgets(dsKH[slKH].ten, sizeof(dsKH[slKH].ten), stdin);
        xoaXuongDong(dsKH[slKH].ten);
        strcpy(dsKH[slKH].sdt, sdt);
        dsKH[slKH].id = slKH + 1;
        idxKH = slKH;
        slKH++;
        moRongDanhSach();
    } else {
        printf("Khach hang hien co: %s\n", dsKH[idxKH].ten);
    }

    printf("Nhap bien so xe: ");
    fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
    int idxXe = timXeTheoBienSo(bienSo);
    if (idxXe == -1) {
        printf("Xe chua co trong he thong.\n");
        printf("Nhap dong xe: ");
        fgets(dsXe[slXe].dongXe, sizeof(dsXe[slXe].dongXe), stdin);
        xoaXuongDong(dsXe[slXe].dongXe);
        strcpy(dsXe[slXe].bienSo, bienSo);
        dsXe[slXe].idKhachHang = dsKH[idxKH].id;
        slXe++;
        moRongDanhSach();
        printf("\nTiep nhan xe thanh cong.\n");
    } else {
        printf("Bien so xe da ton tai trong he thong.\n");
    }
}
