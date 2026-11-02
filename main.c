#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- 1. KHOI TAO STRUCT ---
typedef struct { int ngay, thang, nam; } Ngay;

typedef struct {
    int id;
    char ten[50];
    char sdt[15];
} KhachHang;

typedef struct {
    char bienSo[20];
    int idKhachHang;
    char dongXe[30];
} XeMay;

typedef struct {
    int id;
    char tenPhuTung[50];
    long donGia;
    int tonKho;
    int daThayThe; // Thong ke so luong da ban/thay the
    int loai;      // 0: Phu tung (tru ton kho, co thong ke thay the), 1: Dich vu (khong tru ton kho)
} DichVuBaoDuong;

typedef struct {
    int idDichVu;
    int soLuong;
    long thanhTien;
} ChiTietSuaChua;

typedef struct {
    int id;
    char bienSo[20];
    Ngay ngayLap;
    Ngay ngayHen;
    ChiTietSuaChua *dsChiTiet; // Mang dong chi tiet
    int soChiTiet;
    int capacityChiTiet;
    long tongTien;
    int trangThai; // 0: Dang xu ly, 1: Da hoan thanh (thanh toan)
    int tonKhoDaTru;
} PhieuSuaChua;

// --- MANG DONG TOAN CUC VA BIEN QUAN LY KICH THUOC ---
KhachHang *dsKH = NULL; int slKH = 0; int capKH = 0;
XeMay *dsXe = NULL; int slXe = 0; int capXe = 0;
DichVuBaoDuong *dsDV = NULL; int slDV = 0; int capDV = 0;
PhieuSuaChua *dsPhieu = NULL; int slPhieu = 0; int capPhieu= 0;

// --- DINH NGHIA HAM LAY NGAY HIEN TAI ---
Ngay layNgayHienTai() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    Ngay ngayHienTai;
    ngayHienTai.ngay = tm_info->tm_mday;
    ngayHienTai.thang = tm_info->tm_mon + 1;
    ngayHienTai.nam = tm_info->tm_year + 1900;
    return ngayHienTai;
}

// --- HAM CAP PHAT DONG (CO EPI KIEU TUONG MINH) ---
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

// --- HAM TIEN ICH ---
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
// --- 2. THUAT TOAN TIM KIEM ---
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

// --- TINH NANG 4: TRA CUU TU MENU ---
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

// --- TINH NANG 2: NHAC LICH BAO DUONG ---
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

// --- 3. NGHIEP VU CO BAN ---
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
            printf("Tong tien: %ld VND\n", dsPhieu[i].tongTien);
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
                }
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

// --- 4. THUAT TOAN SAP XEP ---
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

// --- 5. THONG KE ---
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

// --- GIAI PHONG BO NHO TRUOC KHI THOAT ---
void giaiPhongBoNho() {
    free(dsKH);
    free(dsXe);
    free(dsDV);
    for(int i=0; i<slPhieu; i++) {
        free(dsPhieu[i].dsChiTiet);
    }
    free(dsPhieu);
}
// --- 6. DOC / GHI DU LIEU GIOI HAN BO NHO ---
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

// --- HAM MAIN (MENU) ---
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
         if (quyen == 1) {
            puts("  5. [Ong chu] Thong ke ton kho dich vu / phu tung");
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
            case 5:
            if (quyen == 1) thongKePhuTung(); 
                else printf("=> Ban khong co quyen xem ton kho!\n");
                break;
            case 6: thongKePhuTung(); break;
            case 7: traCuuThongTin(); break;
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
