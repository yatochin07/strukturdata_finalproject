#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUK = 100;

struct Produk {
    int id;
    string nama;
    string kategori;
    int stok;
    double harga;
};

void inputProduk(Produk barang[], int &jumlah) {
    cout << "Masukkan jumlah produk: ";
    int tambah;
    cin >> tambah;

    for (int i = 0; i < tambah; i++) {
        Produk p;
        cout << "\nProduk ke-" << jumlah + 1 << ":\n";
        cout << "ID: ";
        cin >> p.id;
        cin.ignore();
        cout << "Nama: ";
        getline(cin, p.nama);
        cout << "Kategori: ";
        getline(cin, p.kategori);
        cout << "Stok: ";
        cin >> p.stok;
        cout << "Harga: ";
        cin >> p.harga;

        barang[jumlah++] = p;
    }
}

void tampilkanSemua(Produk barang[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data produk.\n";
        return;
    }
    cout << "\nDaftar Produk:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID: " << barang[i].id << ", ";
        cout << "Nama: " << barang[i].nama << ", ";
        cout << "Kategori: " << barang[i].kategori << ", ";
        cout << "Stok: " << barang[i].stok << ", ";
        cout << "Harga: Rp" << barang[i].harga << endl;
    }
}

void cariProduk(Produk barang[], int jumlah, int idCari) {
    for (int i = 0; i < jumlah; i++) {
        if (barang[i].id == idCari) {
            cout << "\nData Produk Ditemukan:\n";
            cout << "ID: " << barang[i].id << endl;
            cout << "Nama: " << barang[i].nama << endl;
            cout << "Kategori: " << barang[i].kategori << endl;
            cout << "Stok: " << barang[i].stok << endl;
            cout << "Harga: Rp" << barang[i].harga << endl;
            return;
        }
    }
    cout << "Produk dengan ID " << idCari << " tidak ditemukan.\n";
}

void sortingProduk(Produk barang[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (barang[j].harga > barang[j + 1].harga) {
                swap(barang[j], barang[j + 1]);
            }
        }
    }
    cout << "Data produk telah diurutkan berdasarkan harga (termurah ke termahal).\n";
}

int main() {
    Produk daftarBarang[MAX_PRODUK];
    int jumlah = 0, pilihan, idCari;

    do {
        cout << "\n--- Menu Toko Pak Bejo (Sorting) ---\n";
        cout << "1. Input Data Produk\n";
        cout << "2. Tampilkan Semua Produk\n";
        cout << "3. Cari Produk Berdasarkan ID\n";
        cout << "4. Urutkan Produk Berdasarkan Harga (Ascending)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputProduk(daftarBarang, jumlah);
                break;
            case 2:
                tampilkanSemua(daftarBarang, jumlah);
                break;
            case 3:
                cout << "Masukkan ID produk yang dicari: ";
                cin >> idCari;
                cariProduk(daftarBarang, jumlah, idCari);
                break;
            case 4:
                sortingProduk(daftarBarang, jumlah);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}
