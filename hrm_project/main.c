
#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

// Khai bao cau truc nhan vien
struct NhanVien {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
};

// Khai bao nguyen mau ham
void hienThiMenu(void);
int timKiemTheoMa(struct NhanVien ds[], int soLuong, int maNV);
void hienThiDanhSach(struct NhanVien ds[], int soLuong);
int themNhanVien(struct NhanVien ds[], int soLuong);
void suaNhanVien(struct NhanVien ds[], int soLuong);
int xoaNhanVien(struct NhanVien ds[], int soLuong);
void xoaBoDem(void);
int nhapSoNguyen(const char thongBao[], int *giaTri);
int nhapSoThuc(const char thongBao[], float *giaTri);
void tinhLuong(struct NhanVien nv, float *tienPhat,
               float *tienOT, float *luongThucNhan);

int main(void) {
    struct NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon;

    do {
        hienThiMenu();

        if (!nhapSoNguyen("Nhap lua chon: ", &luaChon)) {
            printf("Loi: Vui long nhap lua chon bang so nguyen!\n");
            continue;
        }

        switch (luaChon) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;

            case 2:
                soLuong = themNhanVien(ds, soLuong);
                break;

            case 3:
                suaNhanVien(ds, soLuong);
                break;

            case 4:
                soLuong = xoaNhanVien(ds, soLuong);
                break;

            case 0:
                printf("Da thoat chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }

    } while (luaChon != 0);

    return 0;
}

// Hien thi menu
void hienThiMenu(void) {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
}

// Xoa ky tu con lai trong bo dem nhap
void xoaBoDem(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        // Bo qua cac ky tu con lai
    }
}

// Nhap so nguyen
int nhapSoNguyen(const char thongBao[], int *giaTri) {
    printf("%s", thongBao);

    if (scanf("%d", giaTri) != 1) {
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}

// Nhap so thuc
int nhapSoThuc(const char thongBao[], float *giaTri) {
    printf("%s", thongBao);

    if (scanf("%f", giaTri) != 1) {
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}

// Tim nhan vien theo ma, tra ve vi tri hoac -1
int timKiemTheoMa(struct NhanVien ds[], int soLuong, int maNV) {
    int i;

    for (i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }

    return -1;
}

// Tinh tien phat, tien OT va luong thuc nhan
void tinhLuong(struct NhanVien nv, float *tienPhat,
               float *tienOT, float *luongThucNhan) {
    if (nv.phutMuon > 15) {
        *tienPhat = 50000.0f;
    } else {
        *tienPhat = 0.0f;
    }

    *tienOT = nv.soGioOT * (nv.luongCoBan / 160.0f) * 1.5f;

    *luongThucNhan = nv.luongCoBan + *tienOT - *tienPhat;
}

// Hien thi danh sach nhan vien va bang luong
void hienThiDanhSach(struct NhanVien ds[], int soLuong) {
    int i;
    float tienPhat, tienOT, luongThucNhan;

    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");

    for (i = 0; i < soLuong; i++) {
        tinhLuong(ds[i], &tienPhat, &tienOT, &luongThucNhan);

        printf("\nMa NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f VND\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.2f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f VND\n", tienPhat);
        printf("Tien OT: %.0f VND\n", tienOT);
        printf("Luong thuc nhan: %.0f VND\n", luongThucNhan);
    }

    printf("\nTong so nhan vien: %d\n", soLuong);
}

// Them nhan vien moi
int themNhanVien(struct NhanVien ds[], int soLuong) {
    struct NhanVien nv;
    int doDai;

    printf("\n--- THEM NHAN VIEN ---\n");

    if (soLuong >= MAX_NHAN_VIEN) {
        printf("Loi: Danh sach da day!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Ma NV: ", &nv.maNV)) {
        printf("Loi: Ma nhan vien khong hop le!\n");
        return soLuong;
    }

    if (nv.maNV <= 0) {
        printf("Loi: Ma nhan vien phai la so nguyen duong!\n");
        return soLuong;
    }

    if (timKiemTheoMa(ds, soLuong, nv.maNV) != -1) {
        printf("Loi: Ma nhan vien da ton tai!\n");
        return soLuong;
    }

    printf("Ho ten: ");

    if (fgets(nv.hoTen, sizeof(nv.hoTen), stdin) == NULL) {
        printf("Loi: Khong doc duoc ho ten!\n");
        return soLuong;
    }

    doDai = (int)strlen(nv.hoTen);

    if (doDai > 0 && nv.hoTen[doDai - 1] == '\n') {
        nv.hoTen[doDai - 1] = '\0';
    } else {
        xoaBoDem();
    }

    if (strlen(nv.hoTen) == 0) {
        printf("Loi: Ho ten khong duoc de trong!\n");
        return soLuong;
    }

    if (!nhapSoThuc("Luong co ban: ", &nv.luongCoBan)) {
        printf("Loi: Luong co ban khong hop le!\n");
        return soLuong;
    }

    if (nv.luongCoBan < 0.0f) {
        printf("Loi: Luong co ban khong duoc am!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Phut di muon: ", &nv.phutMuon)) {
        printf("Loi: So phut di muon khong hop le!\n");
        return soLuong;
    }

    if (nv.phutMuon < 0) {
        printf("Loi: So phut di muon khong duoc am!\n");
        return soLuong;
    }

    if (!nhapSoThuc("So gio OT: ", &nv.soGioOT)) {
        printf("Loi: So gio OT khong hop le!\n");
        return soLuong;
    }

    if (nv.soGioOT < 0.0f) {
        printf("Loi: So gio OT khong duoc am!\n");
        return soLuong;
    }

    ds[soLuong] = nv;
    soLuong++;

    printf("=> Them nhan vien thanh cong!\n");

    return soLuong;
}

// Sua thong tin nhan vien
void suaNhanVien(struct NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    float luongMoi, gioOTMoi;
    int phutMuonMoi;

    if (soLuong == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    if (!nhapSoNguyen("Nhap ma NV can sua: ", &maNV)) {
        printf("Loi: Ma nhan vien khong hop le!\n");
        return;
    }

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("Khong tim thay nhan vien!\n");
        return;
    }

    printf("\nCap nhat thong tin cho nhan vien %s\n",
           ds[viTri].hoTen);

    if (!nhapSoThuc("Luong co ban moi: ", &luongMoi)) {
        printf("Loi: Luong co ban khong hop le!\n");
        return;
    }

    if (luongMoi < 0.0f) {
        printf("Loi: Luong co ban khong duoc am!\n");
        return;
    }

    if (!nhapSoNguyen("So phut di muon moi: ", &phutMuonMoi)) {
        printf("Loi: So phut di muon khong hop le!\n");
        return;
    }

    if (phutMuonMoi < 0) {
        printf("Loi: So phut di muon khong duoc am!\n");
        return;
    }

    if (!nhapSoThuc("So gio OT moi: ", &gioOTMoi)) {
        printf("Loi: So gio OT khong hop le!\n");
        return;
    }

    if (gioOTMoi < 0.0f) {
        printf("Loi: So gio OT khong duoc am!\n");
        return;
    }

    ds[viTri].luongCoBan = luongMoi;
    ds[viTri].phutMuon = phutMuonMoi;
    ds[viTri].soGioOT = gioOTMoi;

    printf("=> Cap nhat nhan vien thanh cong!\n");
}

// Xoa nhan vien va dich mang
int xoaNhanVien(struct NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    int i;

    if (soLuong == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Ma NV can xoa: ", &maNV)) {
        printf("Loi: Ma nhan vien khong hop le!\n");
        return soLuong;
    }

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("Khong tim thay nhan vien!\n");
        return soLuong;
    }

    // Dich cac phan tu phia sau len mot vi tri
    for (i = viTri; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    soLuong--;

    printf("=> Xoa nhan vien thanh cong!\n");

    return soLuong;
}