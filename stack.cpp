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

struct Stack {
    Produk data[MAX_PRODUK];
    int top = -1;

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_PRODUK - 1;
    }

    void push(Produk p) {
        if (!isFull()) {
            data[++top] = p;
        } else {
            cout << "Stack penuh, tidak bisa menambahkan data.\n";
        }
    }

    Produk pop() {
        if (!isEmpty()) {
            return data[top--];
        } else {
            cout << "Stack kosong.\n";
            return {};
        }
    }

    void tampilkanStack() {
        if (isEmpty()) {
            cout << "Stack kosong.\n";
            return;
        }
        cout << "\nData di Stack (dari atas):\n";
        for (int i = top; i >= 0; i--) {
            cout << "- " << data[i].nama << " (ID: " << data[i].id << ")\n";
        }
    }

    void hapusTop() {
        if (!isEmpty()) {
            cout << "Menghapus produk teratas: " << data[top].nama << " (ID: " << data[top].id << ")\n";
            top--;
        } else {
            cout << "Stack kosong, tidak ada data yang bisa dihapus.\n";
        }
    }
};

void inputProduk(Produk barang[], int &jumlah, Stack &s) {
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
        s.push(p);
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

void tampilkanSemua(Produk barang[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data produk.\n";
        return;
    }
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
    Stack stackBarang;

    do {
        cout << "\n--- Menu Toko Pak Bejo ---\n";
        cout << "1. Input Data Produk (masuk Stack)\n";
        cout << "2. Tampilkan Semua Produk\n";
        cout << "3. Cari Produk Berdasarkan ID\n";
        cout << "4. Tampilkan Stack Produk\n";
        cout << "5. Hapus Produk  dari Stack\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputProduk(daftarBarang, jumlah, stackBarang);
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
                stackBarang.tampilkanStack();
                break;
            case 5:
                stackBarang.hapusTop();
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
