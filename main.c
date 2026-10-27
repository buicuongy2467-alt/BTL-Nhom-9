#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    ChiTietSuaChua dsChiTiet[20];
    int soChiTiet;
    long tongTien;
    int trangThai; // 0: Dang xu ly, 1: Da hoan thanh (thanh toan)
} PhieuSuaChua;

// --- MANG TOAN CUC VA BIEN DEM ---
KhachHang dsKH[100]; int slKH = 0;
XeMay dsXe[100]; int slXe = 0;
DichVuBaoDuong dsDV[100]; int slDV = 0;
PhieuSuaChua dsPhieu[100]; int slPhieu = 0;

// --- HAM TIEN ICH ---
void xoaXuongDong(char x[]) {
    size_t len = strlen(x);
    if (len > 0 && x[len - 1] == ' ') x[len - 1] = ' ';
}

int soSanhNgay(Ngay n1, Ngay n2) {
    if (n1.nam != n2.nam) return n1.nam - n2.nam;
    if (n1.thang != n2.thang) return n1.thang - n2.thang;
    return n1.ngay - n2.ngay;
}

void khoiTaoDuLieu() {
    dsDV[slDV++] = (DichVuBaoDuong){1, "Rua xe bot tuyet", 50000, 999, 0};
    dsDV[slDV++] = (DichVuBaoDuong){2, "Thay nhot ban tong hop", 120000, 50, 0};
    dsDV[slDV++] = (DichVuBaoDuong){3, "Thay bugi", 80000, 5, 0}; // Ton kho thap de test
    dsDV[slDV++] = (DichVuBaoDuong){4, "Bao duong noi", 200000, 30, 0};
    dsDV[slDV++] = (DichVuBaoDuong){5, "Day curoa", 350000, 8, 0};
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

// --- 3. NGHIEP VU CO BAN ---
void tiepNhanXe() {
    printf("\n--- TIEP NHAN XE ---\n");
    char sdt[15], bienSo[20];
    
    printf("Nhap SDT khach hang: ");
    fflush(stdin); fgets(sdt, sizeof(sdt), stdin); xoaXuongDong(sdt);
    
    int idxKH = timKhachHangTheoSDT(sdt);
    if (idxKH == -1) {
        printf("-> Khach hang moi! Nhap ten KH: ");
        fgets(dsKH[slKH].ten, sizeof(dsKH[slKH].ten), stdin);
        xoaXuongDong(dsKH[slKH].ten);
        strcpy(dsKH[slKH].sdt, sdt);
        dsKH[slKH].id = slKH + 1;
        idxKH = slKH;
        slKH++;
    } else {
        printf("-> Khach hang cu: %s\n", dsKH[idxKH].ten);
    }

    printf("Nhap bien so xe: ");
    fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
    int idxXe = timXeTheoBienSo(bienSo);
    if (idxXe == -1) {
        printf("-> Xe chua luu tren he thong! Nhap dong xe: ");
        fgets(dsXe[slXe].dongXe, sizeof(dsXe[slXe].dongXe), stdin);
        xoaXuongDong(dsXe[slXe].dongXe);
        strcpy(dsXe[slXe].bienSo, bienSo);
        dsXe[slXe].idKhachHang = dsKH[idxKH].id;
        slXe++;
        printf("Tiep nhan xe THANH CONG!\n");
    } else {
        printf("-> Xe da ton tai trong he thong.\n");
    }
}

void lapPhieuDichVu() {
    printf("\n--- LAP PHIEU DICH VU ---\n");
    char bienSo[20];
    printf("Nhap bien so xe can lap phieu: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
    
    if (timXeTheoBienSo(bienSo) == -1) {
        printf("Khong tim thay xe! Vui long tiep nhan xe (Muc 1) truoc.\n");
        return;
    }

    PhieuSuaChua phieu;
    phieu.id = slPhieu + 1;
    strcpy(phieu.bienSo, bienSo);
    phieu.soChiTiet = 0;
    phieu.tongTien = 0;
    phieu.trangThai = 0; // Dang xu ly

    printf("Nhap ngay lap (dd mm yyyy): ");
    scanf("%d %d %d", &phieu.ngayLap.ngay, &phieu.ngayLap.thang, &phieu.ngayLap.nam);

    int chon;
    do {
        printf("\n%-4s | %-30s | %-12s | %-10s\n", "Ma", "Dich vu / phu tung", "Don gia", "Ton kho");
        printf("-----+--------------------------------+--------------+----------\n");
        for(int i=0; i<slDV; i++) {
            printf("%-4d | %-30s | %9ld VND | %8d\n",
                   dsDV[i].id, dsDV[i].tenPhuTung, dsDV[i].donGia, dsDV[i].tonKho);
        }
        printf("Nhap ma phu tung (0 de hoan tat): ");
        scanf("%d", &chon);
        
        if (chon > 0 && chon <= slDV) {
            int sl;
            printf("Nhap so luong can dung: ");
            scanf("%d", &sl);
            if (dsDV[chon-1].tonKho >= sl) {
                ChiTietSuaChua ct;
                ct.idDichVu = chon;
                ct.soLuong = sl;
                ct.thanhTien = sl * dsDV[chon-1].donGia;
                
                phieu.dsChiTiet[phieu.soChiTiet++] = ct;
                phieu.tongTien += ct.thanhTien;
                dsDV[chon-1].tonKho -= sl; // Tru ton tam thoi
                printf("=> Da them '%s' vao phieu.\n", dsDV[chon-1].tenPhuTung);
            } else {
                printf("=> LOI: Khong du ton kho!\n");
            }
        }
    } while (chon != 0);

    dsPhieu[slPhieu++] = phieu;
    printf("\nLap phieu THANH CONG.\nTong tien tam tinh: %ld VND\n", phieu.tongTien);
}

void thanhToanVaInHoaDon() {
    printf("\n--- THANH TOAN & IN HOA DON ---\n");
    char bienSo[20];
    printf("Nhap bien so xe can thanh toan: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);

    for (int i=0; i<slPhieu; i++) {
        // Tim phieu cua xe dang trong trang thai cho thanh toan (0)
        if (strcmp(dsPhieu[i].bienSo, bienSo) == 0 && dsPhieu[i].trangThai == 0) {
            printf("Tong tien: %ld VND\n", dsPhieu[i].tongTien);
            printf("Nhap 1 de xac nhan thanh toan: ");
            int xacNhan; scanf("%d", &xacNhan);
            if(xacNhan != 1) return;

            printf("Nhap ngay hen bao duong tiep theo (dd mm yyyy): ");
            scanf("%d %d %d", &dsPhieu[i].ngayHen.ngay, &dsPhieu[i].ngayHen.thang, &dsPhieu[i].ngayHen.nam);
            
            dsPhieu[i].trangThai = 1; // Danh dau da thanh toan

            // Cong thong ke so luong phu tung da thay the
            for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                int idDV = dsPhieu[i].dsChiTiet[j].idDichVu;
                dsDV[idDV-1].daThayThe += dsPhieu[i].dsChiTiet[j].soLuong;
            }

            // XUAT HOA DON RA FILE TEXT
            char tenFile[50];
            sprintf(tenFile, "HoaDon_%s_Phieu%d.txt", bienSo, dsPhieu[i].id);
            FILE *f = fopen(tenFile, "w");
            if (f != NULL) {
                fprintf(f, "===============================================\n");
                fprintf(f, "             HOA DON DICH VU XE MAY\n");
                fprintf(f, "===============================================\n");
                fprintf(f, "Ma phieu: %d\n", dsPhieu[i].id);
                fprintf(f, "Bien so xe: %s\n", dsPhieu[i].bienSo);
                fprintf(f, "Ngay lap: %02d/%02d/%04d\n", dsPhieu[i].ngayLap.ngay,
                        dsPhieu[i].ngayLap.thang, dsPhieu[i].ngayLap.nam);
                fprintf(f, "-----------------------------------------------\n");
                fprintf(f, "STT | Ten dich vu / phu tung       | SL | Thanh tien\n");
                fprintf(f, "----+------------------------------+----+------------\n");
                for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                    int id = dsPhieu[i].dsChiTiet[j].idDichVu - 1;
                    fprintf(f, "%-3d | %-28s | %-2d | %ld VND\n", j+1,
                            dsDV[id].tenPhuTung, dsPhieu[i].dsChiTiet[j].soLuong,
                            dsPhieu[i].dsChiTiet[j].thanhTien);
                }
                fprintf(f, "-----------------------------------------------\n");
                fprintf(f, "TONG CONG: %ld VND\n", dsPhieu[i].tongTien);
                fprintf(f, "Lich hen bao duong ky sau: %02d/%02d/%04d\n",
                        dsPhieu[i].ngayHen.ngay, dsPhieu[i].ngayHen.thang,
                        dsPhieu[i].ngayHen.nam);
                fprintf(f, "===============================================\n");
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
    printf("\n--- LICH HEN BAO DUONG (SAP XEP THEO NGAY) ---\n");
    PhieuSuaChua mangTam[100];
    int count = 0;
    
    // Loc ra nhung phieu da thanh toan co ton tai ngay hen
    for(int i=0; i<slPhieu; i++) {
        if(dsPhieu[i].trangThai == 1) {
            mangTam[count++] = dsPhieu[i];
        }
    }

    // Thuat toan sap xep noi bot (Bubble Sort) theo ngay hen
    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            if(soSanhNgay(mangTam[j].ngayHen, mangTam[j+1].ngayHen) > 0) {
                PhieuSuaChua temp = mangTam[j];
                mangTam[j] = mangTam[j+1];
                mangTam[j+1] = temp;
            }
        }
    }

    // In danh sach
    printf("%-12s | %-12s | %-10s\n", "Ngay hen", "Bien so", "Ma phieu");
    printf("-------------+--------------+-----------\n");
    for(int i=0; i<count; i++) {
        printf("%02d/%02d/%04d | %-12s | %-10d\n",
            mangTam[i].ngayHen.ngay, mangTam[i].ngayHen.thang, mangTam[i].ngayHen.nam, 
            mangTam[i].bienSo, mangTam[i].id);
    }
    if (count == 0) printf("Chua co lich hen nao.\n");
}

// --- 5. THONG KE ---
void thongKePhuTung() {
    printf("\n--- THONG KE DICH VU / PHU TUNG ---\n");
    printf("%-28s | %-12s | %-10s | %s\n",
           "Ten dich vu / phu tung", "Da thay", "Ton kho", "Ghi chu");
    printf("-----------------------------+--------------+------------+----------------\n");
    for(int i=0; i<slDV; i++) {
        printf("%-28s | %-12d | %-10d | %s\n",
               dsDV[i].tenPhuTung, dsDV[i].daThayThe, dsDV[i].tonKho,
               dsDV[i].tonKho < 10 ? "Can nhap them" : "Du ton");
    }
}

// --- HAM MAIN (MENU) ---
int main() {
    khoiTaoDuLieu();
    int chon;
    do {
        puts("\n==============================================");
        puts("      QUAN LY TIEM RUA & BAO DUONG XE MAY");
        puts("==============================================");
        puts("  1. Tiep nhan xe");
        puts("  2. Lap phieu dich vu / phu tung");
        puts("  3. Thanh toan va xuat hoa don");
        puts("  4. Xem lich hen bao duong");
        puts("  5. Thong ke dich vu / phu tung");
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
            case 0: printf("Thoat chuong trinh. Tam biet.\n"); break;
            default: printf("Lua chon khong hop le.\n"); break;
        }
    } while(chon != 0);

    return 0;
}
