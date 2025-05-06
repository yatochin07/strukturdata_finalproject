#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Barang {
    int id;
    string nama;
    double harga;
    int stock;
};

const int maks_barang = 100;
Barang db[maks_barang];
int front = 0;
int rear = -1;

void add_barang();
void hapus_barang();
void show_barang();
void detail_barang();
void bersihkan_barang();
void sort_barang();
char get_menu();

int main() {
    while(true) {
        char select = get_menu();
        if(select == '1')
            add_barang();
        else if(select == '2')
            hapus_barang();
        else if(select == '3')
            show_barang();
        else if(select == '4')
            bersihkan_barang();
        else if(select == '5')
            detail_barang();
        else if(select == '6')
            sort_barang();
        else if(select == '7')
            break;
    }
    return 0;
}

void add_barang() {
    system("cls");
    cout << "Add new barang\n";
    if (rear >= maks_barang - 1) {
        cout << "Queue barang penuh!\n";
        system("pause");
        return;
    }
    rear++;
    db[rear].id = rear + 1;

    cout << "- Nama : ";
    getline(cin, db[rear].nama);

    cout << "- Harga : ";
    cin >> db[rear].harga;
    cin.ignore();

    cout << "- Stock : ";
    cin >> db[rear].stock;
    cin.ignore();

    cout << "Data " << db[rear].id << " masuk ke queue\n";
    system("pause");
}

void hapus_barang() {
    system("cls");
    cout << "Hapus data pertama (queue)\n";
    if (rear < front) {
        cout << "Queue kosong, tidak ada data untuk dihapus!\n";
    } else {
        cout << "Data " << db[front].id << " (" << db[front].nama << ") dihapus dari queue.\n";
        front++;
    }
    system("pause");
}

void show_barang() {
    system("cls");
    cout << "Show Barang (Queue)\n";
    if (rear < front) {
        cout << "Queue kosong!\n";
    } else {
        cout << setw(5) << "ID"
             << setw(20) << "Nama"
             << setw(20) << "Harga"
             << setw(10) << "Stock" << endl;
        for(int i = front; i <= rear; i++) {
            cout << setw(5) << db[i].id
                 << setw(20) << db[i].nama
                 << setw(10) << db[i].harga
                 << setw(10) << db[i].stock << endl;
        }
    }
    system("pause");
}

void detail_barang() {
    system("cls");
    int cari_id;
    cout << "Lihat detail barang\n";
    cout << "Masukkan ID barang: ";
    cin >> cari_id;
    cin.ignore();

    bool ditemukan = false;
    for(int i = front; i <= rear; i++) {
        if (db[i].id == cari_id) {
            cout << "Detail barang: \n";
            cout << "- ID    : " << db[i].id << endl;
            cout << "- Nama  : " << db[i].nama << endl;
            cout << "- Harga : " << db[i].harga << endl;
            cout << "- Stock : " << db[i].stock << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Barang dengan ID tersebut tidak ditemukan\n";
    }
    system("pause");
}

void bersihkan_barang() {
    system("cls");
    front = 0;
    rear = -1;
    cout << "Semua data di queue telah dibersihkan.\n";
    system("pause");
}

void sort_barang() {
    system("cls");
    cout << "Mengurutkan barang berdasarkan harga (ascending)...\n";
    if (rear < front) {
        cout << "Queue kosong!\n";
        system("pause");
        return;
    }

    // Bubble Sort sederhana
    for (int i = front; i < rear; ++i) {
        for (int j = front; j < rear - (i - front); ++j) {
            if (db[j].harga > db[j + 1].harga) {
                swap(db[j], db[j + 1]);
            }
        }
    }
    cout << "Barang berhasil diurutkan.\n";
    system("pause");
}

char get_menu() {
    system("cls");
    cout << "Queue Barang\n";
    cout << " [1] Add barang\n";
    cout << " [2] Hapus barang (dequeue)\n";
    cout << " [3] Tampilkan barang\n";
    cout << " [4] Bersihkan semua barang\n";
    cout << " [5] Detail barang\n";
    cout << " [6] Urutkan barang berdasarkan harga\n";
    cout << " [7] Keluar\n";
    cout << "Masukkan Pilihan anda: ";
    string pilih;
    getline(cin, pilih);
    return pilih[0];
}
