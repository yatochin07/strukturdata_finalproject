#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUK = 100;

struct Produk {
    int id;                 // ID produk
    string nama;            // Nama produk
    string kategori;        // Kategori produk
    int stok;               // Jumlah stok
    double harga;           // Harga produk
};

void inputProduk(Produk barang[], int &jumlah) {
    cout << "Masukkan jumlah produk: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++) {
        cout << "\nProduk ke-" << i+1 << ":\n";
        cout << "ID: ";
        cin >> barang[i].id;
        cin.ignore(); // untuk menghindari masalah dengan getline
        cout << "Nama: ";
        getline(cin, barang[i].nama);
        cout << "Kategori: ";
        getline(cin, barang[i].kategori);
        cout << "Stok: ";
        cin >> barang[i].stok;
        cout << "Harga: ";
        cin >> barang[i].harga;
    }
}

void cariProduk(Produk barang[], int jumlah, int idCari) {
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (barang[i].id == idCari) {
            cout << "\nData Produk Ditemukan:\n";
            cout << "ID: " << barang[i].id << endl;
            cout << "Nama: " << barang[i].nama << endl;
            cout << "Kategori: " << barang[i].kategori << endl;
            cout << "Stok: " << barang[i].stok << endl;
            cout << "Harga: Rp" << barang[i].harga << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Produk dengan ID " << idCari << " tidak ditemukan.\n";
    }
}

void tampilkanSemua(Produk barang[], int jumlah) {
    cout << "\nDaftar Seluruh Produk:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID: " << barang[i].id << ", ";
        cout << "Nama: " << barang[i].nama << ", ";
        cout << "Kategori: " << barang[i].kategori << ", ";
        cout << "Stok: " << barang[i].stok << ", ";
        cout << "Harga: Rp" << barang[i].harga << endl;
    }
}

int main() {
    Produk daftarBarang[MAX_PRODUK];
    int jumlah = 0, pilihan, idCari;

    do {
        cout << "\n--- Menu Toko Pak Bejo ---\n";
        cout << "1. Input Produk\n";
        cout << "2. Tampil Produk\n";
        cout << "3. Cari ID Produk\n";
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
            case 0:
                cout << "Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
