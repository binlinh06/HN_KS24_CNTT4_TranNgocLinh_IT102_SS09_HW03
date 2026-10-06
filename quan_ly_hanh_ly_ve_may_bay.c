#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[16];
    char tenHanhKhach[51];
    char hangVe[21];
    float canNangHanhLy;
    float cuocHanhLy;
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong;
    int i;

    // =========================
    // 1. NHAP SO LUONG VE
    // =========================
    printf("Nhap so luong ve may bay: ");
    scanf("%d", &soLuong);
    while (getchar() != '\n');

    if (soLuong < 1 || soLuong > MAX_VE) {
        printf("Loi: So luong ve phai nam trong khoang 1 den %d!\n", MAX_VE);
        return 1;
    }

    // =========================
    // 2. NHAP DANH SACH VE
    // =========================
    for (i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        printf("Ma ve PNR: ");
        scanf("%15s", danhSachVe[i].maVe);
        while (getchar() != '\n');

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach,
              sizeof(danhSachVe[i].tenHanhKhach),
              stdin);

        danhSachVe[i].tenHanhKhach[
            strcspn(danhSachVe[i].tenHanhKhach, "\n")
        ] = '\0';

        printf("Hang ve (Business/Deluxe/Eco): ");
        fgets(danhSachVe[i].hangVe,
              sizeof(danhSachVe[i].hangVe),
              stdin);

        danhSachVe[i].hangVe[
            strcspn(danhSachVe[i].hangVe, "\n")
        ] = '\0';

        // Nhap can nang va kiem tra khong am
        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');

            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Loi: Can nang hanh ly khong duoc am! Vui long nhap lai.\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        // =========================
        // 3. TINH CUOC HANH LY
        // =========================
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy =
                    (danhSachVe[i].canNangHanhLy - 20) * 50000;
            }
        } else {
            // Eco va Deluxe
            danhSachVe[i].cuocHanhLy =
                danhSachVe[i].canNangHanhLy * 50000;
        }
    }

    // =========================
    // 4. HIEN THI DANH SACH
    // =========================
    float tongCuoc = 0;
    int viTriNangNhat = 0;

    for (i = 0; i < soLuong; i++) {
        tongCuoc += danhSachVe[i].cuocHanhLy;

        if (danhSachVe[i].canNangHanhLy >
            danhSachVe[viTriNangNhat].canNangHanhLy) {
            viTriNangNhat = i;
        }
    }

    printf("\n");
    printf("================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n",
           "STT",
           "MA VE",
           "HO TEN HANH KHACH",
           "HANG VE",
           "HANH LY (KG)",
           "CUOC PHI (VND)");

    printf("------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1,
               danhSachVe[i].maVe,
               danhSachVe[i].tenHanhKhach,
               danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy,
               danhSachVe[i].cuocHanhLy);
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);

    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n",
           danhSachVe[viTriNangNhat].maVe,
           danhSachVe[viTriNangNhat].tenHanhKhach,
           danhSachVe[viTriNangNhat].canNangHanhLy);

    // =========================
    // 5. CAP NHAT HANH LY
    // =========================
    char maVeTim[16];
    float canNangMoi;
    int viTriTimThay = -1;

    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");

    printf("Nhap ma ve PNR can cap nhat hanh ly: ");
    fgets(maVeTim, sizeof(maVeTim), stdin);

    maVeTim[strcspn(maVeTim, "\n")] = '\0';

    // Tim kiem tuyen tinh bang strcmp()
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maVeTim) == 0) {
            viTriTimThay = i;
            break;
        }
    }

    if (viTriTimThay == -1) {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    } else {
        do {
            printf("Nhap can nang hanh ly ky gui moi (kg): ");
            scanf("%f", &canNangMoi);
            while (getchar() != '\n');

            if (canNangMoi < 0) {
                printf("Loi: Can nang hanh ly khong duoc am! Vui long nhap lai.\n");
            }
        } while (canNangMoi < 0);

        // Cap nhat can nang
        danhSachVe[viTriTimThay].canNangHanhLy = canNangMoi;

        // Tinh lai cuoc
        if (strcmp(danhSachVe[viTriTimThay].hangVe, "Business") == 0) {
            if (canNangMoi <= 20) {
                danhSachVe[viTriTimThay].cuocHanhLy = 0;
            } else {
                danhSachVe[viTriTimThay].cuocHanhLy =
                    (canNangMoi - 20) * 50000;
            }
        } else {
            danhSachVe[viTriTimThay].cuocHanhLy =
                canNangMoi * 50000;
        }

        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n",
               danhSachVe[viTriTimThay].maVe,
               danhSachVe[viTriTimThay].cuocHanhLy);

        // =========================
        // 6. IN LAI DANH SACH
        // =========================
        printf("\n");
        printf("=============================== DANH SACH VE MAY BAY SAU CAP NHAT ===============================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n",
               "STT",
               "MA VE",
               "HO TEN HANH KHACH",
               "HANG VE",
               "HANH LY (KG)",
               "CUOC PHI (VND)");

        printf("--------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < soLuong; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
                   i + 1,
                   danhSachVe[i].maVe,
                   danhSachVe[i].tenHanhKhach,
                   danhSachVe[i].hangVe,
                   danhSachVe[i].canNangHanhLy,
                   danhSachVe[i].cuocHanhLy);
        }

        printf("--------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}