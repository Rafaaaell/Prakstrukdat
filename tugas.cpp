#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

struct identitasroti {
    int  id;
    char nama[50];
    int  harga;
    int  stok;
};

struct datainvoice {
    int    idRoti;
    string namaRoti;
    int    harga;
    int    jumlahBeli;
    int    totalHarga;
};


struct identitasroti roti[100];
struct datainvoice   invoiceList[100];
int jumlahInvoice = 0;


void menukaryawan();
void menupembeli();
void menu1();
void menu2();
void menu3();
void ascending();
void descending();
void tengah(identitasroti arr[], int kiri, int kanan);
void beli();
void invoice();
void cari();
void sequensial();
void binary();
void partisiNama(int kiri, int kanan);
int  hitung(int a, int b);
int  hitungData();
void menulogin();


int hitungData() {
    int jumlah = 0;

    FILE *menu = fopen("roti.txt", "r");
    if (menu == NULL) {
        cout << "Error Open data!!!" << endl;
        exit(1);
    }

    while (jumlah < 100 &&
           fscanf(menu, "%d %s %d %d",
                  &roti[jumlah].id,
                   roti[jumlah].nama,
                  &roti[jumlah].harga,
                  &roti[jumlah].stok) == 4) {
        jumlah++;
    }

    fclose(menu);
    return jumlah;
}


void menulogin() {
    system("cls");

    string pw, usn;
    string usnb = "090";
    string pwb  = "123";

    cout << "Silahkan Login" << endl;
    cout << "Masukkan Username : "; cin >> usn;
    cout << "Masukkan Password : "; cin >> pw;

    if (usn == usnb && pw == pwb) {
        menukaryawan();
    } else {
        cout << "\nUsername atau Password Salah!" << endl;
        cin.ignore();
        cin.get();
    }
}

void menu1() {
    int tambah;
    cout << "Masukan jumlah menu yang ingin ditambahkan : ";
    cin >> tambah;

    FILE *buka = fopen("roti.txt", "a");
    if (buka == NULL) {
        cout << "Error Open data!!!" << endl;
        exit(1);
    }

    for (int i = 0; i < tambah; i++) {
        cout << "menu ke-" << i + 1 << endl;
        cout << "Masukan ID Menu    : "; cin >> roti[i].id;
        cout << "Masukan Nama Menu  : "; cin >> roti[i].nama;
        cout << "Masukan Harga Menu : "; cin >> roti[i].harga;
        cout << "Masukan Stok       : "; cin >> roti[i].stok;

        fprintf(buka, "%d %s %d %d\n",
                roti[i].id, roti[i].nama,
                roti[i].harga, roti[i].stok);
    }

    fclose(buka);
}

void ascending() {
    int total = hitungData();

    identitasroti temp[100];
    for (int i = 0; i < total; i++) temp[i] = roti[i];

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (temp[j].harga > temp[j + 1].harga) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    cout << "\n==========================================" << endl;
    cout << "=========== Hasil Sorting ================" << endl;
    cout << "==========================================" << endl;
    cout << string(46, '-') << endl;
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Nama"
         << setw(12) << "Harga"
         << setw(8)  << "Stok" << endl;
    cout << string(46, '-') << endl;

    for (int i = 0; i < total; i++) {
        cout << left
             << setw(6)  << temp[i].id
             << setw(20) << temp[i].nama
             << setw(12) << temp[i].harga
             << setw(8)  << temp[i].stok << endl;
    }

    cout << "\nTekan Enter untuk kembali";
    cin.ignore();
    cin.get();
}

void tengah(identitasroti arr[], int kiri, int kanan) {
    int i     = kiri;
    int j     = kanan;
    int pivot = arr[(kiri + kanan) / 2].harga;

    do {
        while (arr[i].harga > pivot) i++;
        while (arr[j].harga < pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (kiri < j) tengah(arr, kiri, j);
    if (i < kanan) tengah(arr, i, kanan);
}

void descending() {
    int total = hitungData();
    int i = 0;

    FILE *menu = fopen("roti.txt", "r");
    if (menu == NULL) {
        cout << "Error Bang!!!" << endl;
        exit(1);
    }

    identitasroti temp[100];
    while (i < 100 &&
           fscanf(menu, "%d %s %d %d",
                  &temp[i].id,
                   temp[i].nama,
                  &temp[i].harga,
                  &temp[i].stok) == 4) {
        i++;
    }

    tengah(temp, 0, total - 1);

    cout << "-------------------------------------------------" << endl;
    cout << " ID   | NAMA                 |HARGA    | STOK    |" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int z = 0; z < total; z++) {
        cout << left
             << "|" << setw(6)  << temp[z].id
             << "|" << setw(21) << temp[z].nama
             << "|" << setw(9)  << temp[z].harga
             << "|" << setw(11) << temp[z].stok
             << "|" << endl;
    }

    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void menu2() {
    system("cls");

    int pilihsort;
    cout << "Jumlah menu roti : " << hitungData() << endl;
    cout << "1. Ascending"  << endl;
    cout << "2. Descending" << endl;
    cout << "> "; cin >> pilihsort;

    cin.ignore();

    if (pilihsort == 1) {
        ascending();
    } else if (pilihsort == 2) {
        descending();
    } else {
        cout << "Error pilih 1 ato 2 bang, jangan yang lain" << endl;
        cout << "Tekan enter untuk kembali" << endl;
        cin.get();
    }
}

void menu3() {
    system("cls");

    int total = hitungData();
    int cariID;

    cout << "Edit Menu roti" << endl;
    cout << "Masukkan ID menu yang ingin di edit : "; cin >> cariID;

    int ketemu = -1;
    for (int i = 0; i < total; i++) {
        if (roti[i].id == cariID) {
            ketemu = i;
            break;
        }
    }

    if (ketemu == -1) {
        cout << "ID yang bener mas, yang ada di menu aja" << endl;
        cin.ignore(); cin.get();
        return;
    }

    cout << "\nData ditemukan:" << endl;
    cout << "ID    : " << roti[ketemu].id    << endl;
    cout << "Nama  : " << roti[ketemu].nama  << endl;
    cout << "Harga : " << roti[ketemu].harga << endl;
    cout << "Stok  : " << roti[ketemu].stok  << endl;

    int pilihedit;
    cout << "\nApa yang ingin diedit?" << endl;
    cout << "1. Nama"  << endl;
    cout << "2. Harga" << endl;
    cout << "3. Stok"  << endl;
    cout << "> "; cin >> pilihedit;

    switch (pilihedit) {
        case 1:
            cout << "Nama baru  : ";
            cin >> roti[ketemu].nama;
            break;
        case 2:
            cout << "Harga baru : ";
            cin >> roti[ketemu].harga;
            break;
        case 3:
            cout << "Stok baru  : ";
            cin >> roti[ketemu].stok;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            cin.ignore(); cin.get();
            return;
    }

    FILE *simpan = fopen("roti.txt", "w");
    if (simpan == NULL) {
        cout << "Error menyimpan data!" << endl;
        exit(1);
    }

    for (int i = 0; i < total; i++) {
        fprintf(simpan, "%d %s %d %d\n",
                roti[i].id,
                roti[i].nama,
                roti[i].harga,
                roti[i].stok);
    }
    fclose(simpan);

    cout << "\nData berhasil diperbarui!" << endl;
    cout << "\nTekan enter untuk kembali" << endl;
    cin.ignore();
    cin.get();
}

void menukaryawan() {
    int pilihan;
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "             Menu Karyawan                  " << endl;
        cout << "============================================" << endl;
        cout << "  1. Tambah Menu Roti"       << endl;
        cout << "  2. Lihat Menu Roti"         << endl;
        cout << "  3. Edit Menu Roti"          << endl;
        cout << "  0. Kembali ke Menu Utama"   << endl;
        cout << "==========================================" << endl;
        cout << " > "; cin >> pilihan;

        cin.ignore();

        switch (pilihan) {
            case 1: menu1(); break;
            case 2: menu2(); break;
            case 3: menu3(); break;
            case 0: break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
                cin.get();
        }
    } while (pilihan != 0);
}


int hitung(int a, int b) {
    int total      = hitungData();
    int beli       = 0;
    int totalHarga = 0;
    bool found     = false;

    for (int i = 0; i < total; i++) {
        if (roti[i].id == a) {
            found = true;
            beli  = i;
            break;
        }
    }

    if (found) {
        if (roti[beli].stok >= b) {
            roti[beli].stok -= b;
            totalHarga = roti[beli].harga * b;

            FILE *menu = fopen("roti.txt", "w");
            for (int j = 0; j < total; j++) {
                fprintf(menu, "%d %s %d %d\n",
                        roti[j].id, roti[j].nama,
                        roti[j].harga, roti[j].stok);
            }
            fclose(menu);

            invoiceList[jumlahInvoice].idRoti     = roti[beli].id;
            invoiceList[jumlahInvoice].namaRoti   = roti[beli].nama;
            invoiceList[jumlahInvoice].harga      = roti[beli].harga;
            invoiceList[jumlahInvoice].jumlahBeli = b;
            invoiceList[jumlahInvoice].totalHarga = totalHarga;
            jumlahInvoice++;

            FILE *inv = fopen("invoice.txt", "a");
            fprintf(inv, "%d %s %d %d %d\n",
                    roti[beli].id,
                    roti[beli].nama,
                    roti[beli].harga,
                    b,
                    totalHarga);
            fclose(inv);

            cout << "Stok Diperbaharui!" << endl;
        } else {
            cout << "stok tidak mencukupi!" << endl;
        }
    }

    return totalHarga;
}


void sequensial() {
    system("cls");

    int  total = hitungData();
    char cariNama[30];
    bool found = false;

    if (total == 0) {
        cout << "Error, Kesalahan membuka file" << endl;
        cin.ignore(); cin.get();
        return;
    }

    cout << "Jumlah Data Roti : " << total << endl;
    cout << "Masukan Nama Roti yang ingin dicari : "; cin >> cariNama;

    for (int i = 0; i < total; i++) {
        if (strcmp(roti[i].nama, cariNama) == 0) {
            found = true;
            cout << "Roti Ditemukan!!" << endl;
            cout << "Nama Roti  : " << roti[i].nama  << endl;
            cout << "Harga Roti : " << roti[i].harga << endl;
            cout << "Stok Roti  : " << roti[i].stok  << endl;
            break;
        }
    }

    if (!found) cout << "Roti tidak ditemukan!" << endl;
    cin.ignore(); cin.get();
}

void partisiNama(int kiri, int kanan) {
    int  i = kiri, j = kanan;
    char pivot[30];
    strcpy(pivot, roti[(kiri + kanan) / 2].nama);

    do {
        while (strcmp(roti[i].nama, pivot) < 0) i++;
        while (strcmp(roti[j].nama, pivot) > 0) j--;

        if (i <= j) {
            swap(roti[i], roti[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (kiri < j) partisiNama(kiri, j);
    if (i < kanan) partisiNama(i, kanan);
}

void binary() {
    int total = hitungData();
    if (total == 0) return;

    partisiNama(0, total - 1);

    char cariNama[30];
    cout << "Masukan Nama Roti: "; cin >> cariNama;

    int  awal  = 0, akhir = total - 1, mid;
    bool found = false;

    while (awal <= akhir) {
        mid = (awal + akhir) / 2;
        int hasilCek = strcmp(roti[mid].nama, cariNama);

        if (hasilCek == 0) {
            found = true;
            cout << "\nRoti Ditemukan!" << endl;
            cout << "Nama  : " << roti[mid].nama  << endl;
            cout << "Harga : " << roti[mid].harga << endl;
            cout << "Stok  : " << roti[mid].stok  << endl;
            break;
        } else if (hasilCek < 0) {
            awal = mid + 1;
        } else {
            akhir = mid - 1;
        }
    }

    if (!found) cout << "Data tidak ditemukan." << endl;
    cin.ignore(); cin.get();
}

void cari() {
    int pilih;
    cout << "Pilih Metode Cari" << endl;
    cout << "1. Sequential"    << endl;
    cout << "2. Binary"        << endl;
    cout << "> : "; cin >> pilih;

    switch (pilih) {
        case 1: sequensial(); break;
        case 2: binary();     break;
        default:
            cout << "pilih 1/2" << endl;
            return;
    }
}


void beli() {
    system("cls");

    remove("invoice.txt");
    jumlahInvoice = 0;

    int jmlhbeli, idbeli;
    menu2();

    cout << "Masukkan ID yang ingin dibeli : "; cin >> idbeli;
    cout << "Masukkan Jumlah beli          : "; cin >> jmlhbeli;

    int total = hitung(idbeli, jmlhbeli);

    if (total > 0) {
        cout << "\nPembelian berhasil!" << endl;
        cout << "Total Harga : Rp " << total << endl;
        cout << "Silahkan ke menu invoice untuk mencetak" << endl;
    }

    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void invoice() {
    system("cls");

    FILE *inv = fopen("invoice.txt", "r");
    if (inv == NULL) {
        cout << "Belum ada transaksi!" << endl;
        cin.ignore(); cin.get();
        return;
    }

    int  idR, hargaR, jmlh, totalH;
    char namaR[50];
    int  grandTotal = 0;

    while (fscanf(inv, "%d %s %d %d %d",
                  &idR, namaR, &hargaR, &jmlh, &totalH) == 5) {
        cout << "======= STRUK PEMBELIAN =======" << endl;
        cout << "Nama Roti : " << namaR  << endl;
        cout << "Harga     : " << hargaR << endl;
        cout << "Jumlah    : " << jmlh   << endl;
        cout << "Total     : " << totalH << endl;
        cout << "================================" << endl;

        grandTotal += totalH;
    }
    fclose(inv);

    if (grandTotal > 0) {
        cout << "GRAND TOTAL : Rp " << grandTotal << endl;
        cout << "================================" << endl;
    }

    char pilih;
    cout << "\nkembali ke menu?(y/n)"; cin >> pilih;
    if (pilih == 'n' || pilih == 'N') {
        remove("invoice.txt");
        jumlahInvoice = 0;
        cout << "Invoice dihapus!" << endl;
        cin.ignore(); cin.get();
    }
}

void menupembeli() {
    int pilihan;
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "             Menu Pembeli                   " << endl;
        cout << "============================================" << endl;
        cout << "  1. Cari Roti"    << endl;
        cout << "  2. Beli Roti"    << endl;
        cout << "  3. Invoice Roti" << endl;
        cout << "  0. Kembali"      << endl;
        cout << "==========================================" << endl;
        cout << " > "; cin >> pilihan;

        cin.ignore();

        switch (pilihan) {
            case 1: cari();    break;
            case 2: beli();    break;
            case 3: invoice(); break;
            case 0: break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
                cin.get();
        }
    } while (pilihan != 0);
}

int main() {
    int pilih;
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "              Selamat Datang                " << endl;
        cout << "============================================" << endl;
        cout << "1. Masuk Sebagai Karyawan" << endl;
        cout << "2. Masuk Sebagai Pembeli"  << endl;
        cout << "Masukan Menu  : ";
        cin >> pilih;

        switch (pilih) {
            case 1: menulogin();   break;
            case 2: menupembeli(); break;
            default:
                cout << "Pilihan Tidak Valid" << endl
                     << "Silahkan Pilih Menu 1 atau 2" << endl;
                cin.get();
                break;
        }
    } while (pilih != 0);
}
