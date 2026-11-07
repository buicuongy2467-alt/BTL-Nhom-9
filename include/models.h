#ifndef MODELS_H
#define MODELS_H

typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay;

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
    int daThayThe;
    int loai;
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
    ChiTietSuaChua *dsChiTiet;
    int soChiTiet;
    int capacityChiTiet;
    long tongTien;
    int trangThai;
    int tonKhoDaTru;
} PhieuSuaChua;

extern KhachHang *dsKH;
extern int slKH;
extern int capKH;
extern XeMay *dsXe;
extern int slXe;
extern int capXe;
extern DichVuBaoDuong *dsDV;
extern int slDV;
extern int capDV;
extern PhieuSuaChua *dsPhieu;
extern int slPhieu;
extern int capPhieu;

#endif
