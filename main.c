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
    printf("--- TIEP NHAN XE ---");
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
        printf("-> Khach hang cu: %s", dsKH[idxKH].ten);
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
        printf("Tiep nhan xe THANH CONG!");
    } else {
        printf("-> Xe da ton tai trong he thong.");
    }
}

void lapPhieuDichVu() {
    printf("--- LAP PHIEU DICH VU ---");
    char bienSo[20];
    printf("Nhap bien so xe can lap phieu: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);
    
    if (timXeTheoBienSo(bienSo) == -1) {
        printf("Khong tim thay xe! Vui long tiep nhan xe (Muc 1) truoc.");
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
        printf("-- Danh sach linh kien / phu tung --");
        for(int i=0; i<slDV; i++) {
            printf("%d. %s - %ld VND (Ton: %d)", dsDV[i].id, dsDV[i].tenPhuTung, dsDV[i].donGia, dsDV[i].tonKho);
        }
        printf("Nhap ID phu tung de them vao (Chon 0 de ket thuc): ");
        scanf("%d", &chon);
        
        if (chon > 0 && chon <= slDV) {
            int sl;
            printf("Nhap so luong can dung: "); scanf("%d", &sl);
            if (dsDV[chon-1].tonKho >= sl) {
                ChiTietSuaChua ct;
                ct.idDichVu = chon;
                ct.soLuong = sl;
                ct.thanhTien = sl * dsDV[chon-1].donGia;
                
                phieu.dsChiTiet[phieu.soChiTiet++] = ct;
                phieu.tongTien += ct.thanhTien;
                dsDV[chon-1].tonKho -= sl; // Tru ton tam thoi
                printf("=> Da them '%s' vao phieu.", dsDV[chon-1].tenPhuTung);
            } else {
                printf("=> LOI: Khong du ton kho!");
            }
        }
    } while (chon != 0);

    dsPhieu[slPhieu++] = phieu;
    printf("Lap phieu THANH CONG. Tong tien tam tinh: %ld VND", phieu.tongTien);
}

void thanhToanVaInHoaDon() {
    printf("--- THANH TOAN & IN HOA DON ---");
    char bienSo[20];
    printf("Nhap bien so xe can thanh toan: ");
    fflush(stdin); fgets(bienSo, sizeof(bienSo), stdin); xoaXuongDong(bienSo);

    for (int i=0; i<slPhieu; i++) {
        // Tim phieu cua xe dang trong trang thai cho thanh toan (0)
        if (strcmp(dsPhieu[i].bienSo, bienSo) == 0 && dsPhieu[i].trangThai == 0) {
            printf("Tong tien: %ld VND. Nhap 1 de xac nhan thanh toan: ", dsPhieu[i].tongTien);
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
                fprintf(f, "=======================================");
                fprintf(f, "        HOA DON DICH VU XE MAY");
                fprintf(f, "=======================================");
                fprintf(f, "Ma phieu: %d", dsPhieu[i].id);
                fprintf(f, "Bien so xe: %s", dsPhieu[i].bienSo);
                fprintf(f, "Ngay lap: %02d/%02d/%04d", dsPhieu[i].ngayLap.ngay, dsPhieu[i].ngayLap.thang, dsPhieu[i].ngayLap.nam);
                fprintf(f, "---------------------------------------");
                fprintf(f, "STT | Ten Phu Tung/DV       | SL | Thanh Tien");
                for(int j=0; j<dsPhieu[i].soChiTiet; j++) {
                    int id = dsPhieu[i].dsChiTiet[j].idDichVu - 1;
                    fprintf(f, "%-3d | %-21s | %-2d | %ld VND", j+1, dsDV[id].tenPhuTung, dsPhieu[i].dsChiTiet[j].soLuong, dsPhieu[i].dsChiTiet[j].thanhTien);
                }
                fprintf(f, "---------------------------------------");
                fprintf(f, "TONG CONG: %ld VND", dsPhieu[i].tongTien);
                fprintf(f, ">> Lich hen bao duong ky sau: %02d/%02d/%04d", dsPhieu[i].ngayHen.ngay, dsPhieu[i].ngayHen.thang, dsPhieu[i].ngayHen.nam);
                fprintf(f, "=======================================");
                fclose(f);
                printf("=> THANH TOAN XONG! Da xuat hoa don ra file: '%s'", tenFile);
            } else {
                printf("Loi khong the tao file hoa don!");
            }
            return;
        }
    }
    printf("Khong co phieu nao dang cho thanh toan cua xe: %s", bienSo);
}

// --- 4. THUAT TOAN SAP XEP ---
void sapXepLichBaoDuong() {
    printf("--- LICH HEN BAO DUONG (Sap xep theo ngay) ---");
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
    printf("%-12s | %-12s | %-10s", "Ngay Hen", "Bien So", "Ma Phieu");
    for(int i=0; i<count; i++) {
        printf("%02d/%02d/%04d | %-12s | %-10d", 
            mangTam[i].ngayHen.ngay, mangTam[i].ngayHen.thang, mangTam[i].ngayHen.nam, 
            mangTam[i].bienSo, mangTam[i].id);
    }
    if (count == 0) printf("Chua co lich hen nao!");
}

// --- 5. THONG KE ---
void thongKePhuTung() {
    printf("--- THONG KE PHU TUNG CAN THAY & DA THAY THE ---");
    printf("%-25s | %-12s | %-12s", "Ten Phu Tung/Dich Vu", "Da thay the", "Ton Kho (Can)");
    for(int i=0; i<slDV; i++) {
        printf("%-25s | %-12d | %-12d", dsDV[i].tenPhuTung, dsDV[i].daThayThe, dsDV[i].tonKho);
        if(dsDV[i].tonKho < 10) printf(" <-- CAN NHAP THEMM!"); // Canh bao neu ton kho < 10
        printf("");
    }
}

// --- HAM MAIN (MENU) ---
int main() {
    khoiTaoDuLieu();
    int chon;
    do {
        printf("==========================================");
        printf("   QUAN LY TIEM RUA & SUA XE MAY");
        printf("==========================================");
        printf("1. Tiep nhan xe (Tim bang Bien so/SDT)");
        printf("2. Lap phieu xu ly dich vu/phu tung");
        printf("3. Thanh toan, nhac lich & Xuat hoa don");
        printf("4. Xem danh sach lich hen (Sap xep tang dan)");
        printf("5. Thong ke linh kien phu tung");
        printf("0. Thoat");
        printf(">> Chon chuc nang: ");
        scanf("%d", &chon);
        
        switch(chon) {
            case 1: tiepNhanXe(); break;
            case 2: lapPhieuDichVu(); break;
            case 3: thanhToanVaInHoaDon(); break;
            case 4: sapXepLichBaoDuong(); break;
            case 5: thongKePhuTung(); break;
            case 0: printf("Thoat chuong trinh. Tam biet"); break;
            default: printf("Lua chon khong hop le.");
        }
    } while(chon != 0);

    return 0;
}

