#include "service.h"
#include "customers.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kiemTraNhacLichBaoDuong() {
    Ngay homNay = layNgayHienTai();
    int dem = 0;
    for(int i=0; i<slPhieu; i++) {
        if(dsPhieu[i].trangThai == 1) {
            int cmp = soSanhNgay(dsPhieu[i].ngayHen, homNay);
            if (cmp <= 0) { // Ðã d?n h?n ho?c quá h?n
                if (dem == 0) {
                    printf("\n================================================\n");
                    printf("        THONG BAO: LICH HEN BAO DUONG DEN HAN\n");
                    printf("================================================\n");
                    printf("%-12s | %-12s | %-10s\n", "Ngay hen", "Bien so", "Trang thai");
                    printf("-------------+--------------+-----------\n");
                }
                printf("%02d/%02d/%04d | %-12s | %s\n",
                    dsPhieu[i].ngayHen.ngay, dsPhieu[i].ngayHen.thang, dsPhieu[i].ngayHen.nam, 
                    dsPhieu[i].bienSo, cmp == 0 ? "Hom nay" : "Qua han");
                dem++;
            }
        }
    }
}

void lapPhieuDichVu() {
    moRongDanhSach();
    printf("\n================================================\n");
    printf("                 LAP PHIEU DICH VU\n");
    printf("================================================\n");
    char bienSo[20];
    printf("Nhap bien so xe can lap phieu: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
    
    if (timXeTheoBienSo(bienSo) == -1) {
        printf("Khong tim thay xe. Vui long tiep nhan xe truoc.\n");
        return;
    }

    PhieuSuaChua phieu;
    phieu.id = slPhieu + 1;
    strcpy(phieu.bienSo, bienSo);
    phieu.soChiTiet = 0;
    phieu.capacityChiTiet = 5;
    phieu.dsChiTiet = (ChiTietSuaChua*)malloc(phieu.capacityChiTiet * sizeof(ChiTietSuaChua));
    phieu.tongTien = 0;
    phieu.trangThai = 0; // Dang xu ly
    phieu.tonKhoDaTru = 0;

    printf("Nhap ngay lap (dd mm yyyy): ");
    scanf("%d %d %d", &phieu.ngayLap.ngay, &phieu.ngayLap.thang, &phieu.ngayLap.nam);

  int chon;
    do {
        printf("\n%-4s | %-30s | %-16s | %-10s | %-10s\n",
               "Ma", "Dich vu / phu tung", "Don gia", "Ton kho", "Loai");
        printf("-----+--------------------------------+------------------+------------+------------\n");
        for(int i=0; i<slDV; i++) {
            printf("%-4d | %-30s | %11ld VND | %10d | %-10s\n",
                   dsDV[i].id, dsDV[i].tenPhuTung, dsDV[i].donGia, dsDV[i].tonKho, 
                   dsDV[i].loai == 0 ? "Phu tung" : "Dich vu");
        }
        printf("\nNhap ma dich vu / phu tung (0 de hoan tat): ");
        scanf("%d", &chon);

        if (chon > 0 && chon <= slDV) {
            int sl;
            printf("Nhap so luong can dung: ");
            scanf("%d", &sl);
            
            if (dsDV[chon-1].loai == 1 || dsDV[chon-1].tonKho >= sl) {
                if (phieu.soChiTiet >= phieu.capacityChiTiet) {
                    phieu.capacityChiTiet *= 2;
                    ChiTietSuaChua *temp = (ChiTietSuaChua*)realloc(phieu.dsChiTiet, phieu.capacityChiTiet * sizeof(ChiTietSuaChua));
                    if (temp != NULL) phieu.dsChiTiet = temp;
                }
                
                ChiTietSuaChua ct;
                ct.idDichVu = chon;
                ct.soLuong = sl;
                ct.thanhTien = sl * dsDV[chon-1].donGia;
                
                phieu.dsChiTiet[phieu.soChiTiet++] = ct;
                phieu.tongTien += ct.thanhTien;
                
                if (dsDV[chon-1].loai == 0) {
                    dsDV[chon-1].tonKho -= sl; 
                }
                printf("=> Da them '%s' vao phieu.\n", dsDV[chon-1].tenPhuTung);
            } else {
                printf("=> LOI: Khong du ton kho!\n");
            }
        }
    } while (chon != 0);

    phieu.tonKhoDaTru = 1;
    dsPhieu[slPhieu++] = phieu;
    printf("\nLap phieu thanh cong.\n");
    printf("Ma phieu: %d\n", phieu.id);
    printf("Tong tien tam tinh: %ld VND\n", phieu.tongTien);
}

void thanhToanVaInHoaDon() {
    printf("\n================================================\n");
    printf("              THANH TOAN VA IN HOA DON\n");
    printf("================================================\n");
    char bienSo[20];
    printf("Nhap bien so xe can thanh toan: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);

    for (int i=0; i<slPhieu; i++) {
        if (strcmp(dsPhieu[i].bienSo, bienSo) == 0 && dsPhieu[i].trangThai == 0) {
            long tongTien = dsPhieu[i].tongTien;
            long tienGiam = 0;
            
            // Tinh toan khuyen mai
            if (tongTien >= 1000000) {
                tienGiam = tongTien * 0.10;
                printf("=> Chuc mung! Hoa don tren 1,000,000 VND, ban duoc giam 10%%.\n");
            } else if (tongTien >= 500000) {
                tienGiam = tongTien * 0.05;
                printf("=> Chuc mung! Hoa don tren 500,000 VND, ban duoc giam 5%%.\n");
            }
            
            long tongThanhToan = tongTien - tienGiam;

            printf("Tong tien ban dau: %ld VND\n", tongTien);
            if (tienGiam > 0) printf("So tien duoc giam: %ld VND\n", tienGiam);
             printf("SO TIEN CAN THANH TOAN: %ld VND\n", tongThanhToan);
             printf("Nhap 1 de xac nhan thanh toan (so khac de huy): ");
            int xacNhan; scanf("%d", &xacNhan);
            if(xacNhan != 1) {
                if (dsPhieu[i].tonKhoDaTru) {
                    for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                        int idDV = dsPhieu[i].dsChiTiet[j].idDichVu;
                        if (dsDV[idDV-1].loai == 0) {
                            dsDV[idDV-1].tonKho += dsPhieu[i].dsChiTiet[j].soLuong;
                        }
                    }
                    dsPhieu[i].tonKhoDaTru = 0;
                    printf("Da huy thanh toan. Ton kho da duoc hoan lai; phieu van cho thanh toan.\n");
                } else {
                    printf("Da huy thanh toan. Phieu van duoc giu lai.\n");
                }
                return;
            }

            if (!dsPhieu[i].tonKhoDaTru) {
                for(int d=0; d<slDV; d++) {
                    if (dsDV[d].loai == 0) {
                        int soLuongCan = 0;
                        for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                            if (dsPhieu[i].dsChiTiet[j].idDichVu == d + 1) {
                                soLuongCan += dsPhieu[i].dsChiTiet[j].soLuong;
                            }
                        }
                        if (dsDV[d].tonKho < soLuongCan) {
                            printf("Khong du ton kho cho '%s'. Phieu van cho thanh toan.\n",
                                   dsDV[d].tenPhuTung);
                            return;
                        }
                    }
                }
                for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                    int idDV = dsPhieu[i].dsChiTiet[j].idDichVu;
                    if (dsDV[idDV-1].loai == 0) {
                        dsDV[idDV-1].tonKho -= dsPhieu[i].dsChiTiet[j].soLuong;
                    }
                }
                dsPhieu[i].tonKhoDaTru = 1;
            }

            printf("Nhap ngay hen bao duong tiep theo (dd mm yyyy): ");
            scanf("%d %d %d", &dsPhieu[i].ngayHen.ngay, &dsPhieu[i].ngayHen.thang, &dsPhieu[i].ngayHen.nam);
            
            dsPhieu[i].trangThai = 1; 

            for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                int idDV = dsPhieu[i].dsChiTiet[j].idDichVu;
                if (dsDV[idDV-1].loai == 0) {
                    dsDV[idDV-1].daThayThe += dsPhieu[i].dsChiTiet[j].soLuong;
                }
            }

            char tenFile[50];
            sprintf(tenFile, "HoaDon_%s_Phieu%d.txt", bienSo, dsPhieu[i].id);
            FILE *f = fopen(tenFile, "w");
            if (f != NULL) {
                fprintf(f, "===============================================================\n");
                fprintf(f, "                  HOA DON DICH VU XE MAY\n");
                fprintf(f, "===============================================================\n");
                fprintf(f, "Ma phieu: %d\n", dsPhieu[i].id);
                fprintf(f, "Bien so xe: %s\n", dsPhieu[i].bienSo);
                fprintf(f, "Ngay lap: %02d/%02d/%04d\n", dsPhieu[i].ngayLap.ngay,
                        dsPhieu[i].ngayLap.thang, dsPhieu[i].ngayLap.nam);
                fprintf(f, "---------------------------------------------------------------\n");
                fprintf(f, "%-4s | %-30s | %-5s | %15s\n",
                        "STT", "Dich vu / phu tung", "SL", "Thanh tien");
                fprintf(f, "-----+--------------------------------+-------+----------------\n");
                for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                    int id = dsPhieu[i].dsChiTiet[j].idDichVu - 1;
                    fprintf(f, "%-4d | %-30s | %-5d | %11ld VND\n", j+1,
                            dsDV[id].tenPhuTung, dsPhieu[i].dsChiTiet[j].soLuong,
                            dsPhieu[i].dsChiTiet[j].thanhTien);

                fprintf(f, "---------------------------------------------------------------\n");
                fprintf(f, "TONG TIEN BAN DAU: %ld VND\n", tongTien);
                if (tienGiam > 0) {
                    fprintf(f, "KHUYEN MAI GIAM GIA: -%ld VND\n", tienGiam);

                fprintf(f, "---------------------------------------------------------------\n");
                fprintf(f, "TONG CONG: %ld VND\n", dsPhieu[i].tongTien);
                fprintf(f, "Lich hen bao duong ky sau: %02d/%02d/%04d\n",
                        dsPhieu[i].ngayHen.ngay, dsPhieu[i].ngayHen.thang,
                        dsPhieu[i].ngayHen.nam);
                fprintf(f, "===============================================================\n");
                fclose(f);
                printf("=> THANH TOAN XONG!\nDa xuat hoa don ra file: '%s'\n", tenFile);
            } else {
                printf("Loi khong the tao file hoa don!\n");
            }
            return;
        }
    }
    printf("Khong co phieu nao dang cho thanh toan cua xe: %s\n", bienSo);
} 
}
}

void sapXepLichBaoDuong() {
    printf("\n================================================\n");
    printf("          LICH HEN BAO DUONG (THEO NGAY)\n");
    printf("================================================\n");
    PhieuSuaChua *mangTam = (PhieuSuaChua*)malloc(slPhieu * sizeof(PhieuSuaChua));
    int count = 0;
    
    for(int i=0; i<slPhieu; i++) {
        if(dsPhieu[i].trangThai == 1) {
            mangTam[count++] = dsPhieu[i];
        }
    }

    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            if(soSanhNgay(mangTam[j].ngayHen, mangTam[j+1].ngayHen) > 0) {
                PhieuSuaChua temp = mangTam[j];
                mangTam[j] = mangTam[j+1];
                mangTam[j+1] = temp;
            }
        }
    }

   if (count == 0) {
        printf("Chua co lich hen nao.\n");
        free(mangTam);
        return;
    }

    // Lay ngay he thong de so sanh va thong bao tinh trang
    Ngay homNay = layNgayHienTai();
    printf("Ngay he thong: %02d/%02d/%04d\n\n", homNay.ngay, homNay.thang, homNay.nam);
    printf("%-12s | %-12s | %-10s | %-15s\n", "Ngay hen", "Bien so", "Ma phieu", "Tinh trang");
    printf("-------------+--------------+------------+----------------\n");

    for(int i = 0; i < count; i++) {
        int cmp = soSanhNgay(mangTam[i].ngayHen, homNay);
        char tinhTrang[20];

        if (cmp < 0) {
            strcpy(tinhTrang, "QUA HAN");
        } else if (cmp == 0) {
            strcpy(tinhTrang, "HOM NAY");
        } else if (cmp <= 3) {
            strcpy(tinhTrang, "SAP DEN HAN");
        } else {
            strcpy(tinhTrang, "Chua den han");
        }

        printf("%02d/%02d/%04d | %-12s | %-10d | %-15s\n",
               mangTam[i].ngayHen.ngay, mangTam[i].ngayHen.thang, mangTam[i].ngayHen.nam, 
               mangTam[i].bienSo, mangTam[i].id, tinhTrang);
    }

    free(mangTam);
}

void thongKePhuTung() {
    printf("\n================================================\n");
    printf("          THONG KE DICH VU VA PHU TUNG\n");
    printf("================================================\n");
    printf("%-30s | %-12s | %-10s | %-10s | %-14s\n",
           "Dich vu / phu tung", "Da thay", "Ton kho", "Loai", "Trang thai");
    printf("-------------------------------+--------------+------------+------------+---------------\n");
    for(int i=0; i<slDV; i++) {
        printf("%-30s | %-12d | %-10d | %-10s | %-14s\n",
               dsDV[i].tenPhuTung, 
               dsDV[i].loai == 0 ? dsDV[i].daThayThe : 0, 
               dsDV[i].loai == 0 ? dsDV[i].tonKho : -1,
               dsDV[i].loai == 0 ? "Phu tung" : "Dich vu",
               dsDV[i].loai == 0 ? (dsDV[i].tonKho < 10 ? "Can nhap them" : "Du ton") : "Khong gioi han");
    }
}
