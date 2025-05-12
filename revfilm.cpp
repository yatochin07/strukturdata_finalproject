#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Deklarasi fungsi-fungsi sebelum main
void clearScreen();
void pause();
void tambahFilm(string judul, string genre);
void tampilFilm();
void tambahReview(int idx);
void lihatReview(int idx);
void undoReview();
void cariFilm(string keyword);
void urutkanFilm();
void beliTiket();
void lihatTiketSaya();
void tontonFilm();

// Struktur data
struct Review {
    string nama;
    string komentar;
    int rating;
};

struct Film {
    string judul;
    string genre;
    float rataRataRating;
    vector<Review> daftarReview;
};

// Global variable
vector<Film> filmList;
map<string, int> tiketSaya;
stack<pair<int, Review>> historyUndo;
map<string, string> jadwalFilm = {
    {"Inception", "10:00 WIB"}, {"Interstellar", "12:00 WIB"}, {"The Matrix", "14:00 WIB"},
    {"Spirited Away", "10:30 WIB"}, {"Howl's Moving Castle", "13:00 WIB"}, {"Harry Potter", "15:30 WIB"},
    {"Parasite", "11:00 WIB"}, {"Gone Girl", "13:30 WIB"}, {"Joker", "16:00 WIB"},
    {"The Conjuring", "17:00 WIB"}, {"Insidious", "18:30 WIB"}, {"Hereditary", "20:00 WIB"}
};
map<string, int> hargaFilm = {
    {"Inception", 50000}, {"Interstellar", 50000}, {"The Matrix", 50000},
    {"Spirited Away", 45000}, {"Howl's Moving Castle", 45000}, {"Harry Potter", 45000},
    {"Parasite", 55000}, {"Gone Girl", 55000}, {"Joker", 55000},
    {"The Conjuring", 60000}, {"Insidious", 60000}, {"Hereditary", 60000}
};

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void tambahFilm(string judul, string genre) {
    filmList.push_back({judul, genre, 0.0, {}});
}

void tampilFilm() {
    clearScreen();
    cout << "Daftar Film:\n";
    for (int i = 0; i < filmList.size(); ++i)
        cout << i + 1 << ". " << filmList[i].judul << " (" << filmList[i].genre << ") | Rating: " << filmList[i].rataRataRating << endl;
    pause();
}

void tambahReview(int idx) {
    clearScreen();
    if (idx < 0 || idx >= filmList.size()) {
        cout << "Nomor film tidak valid.\n";
        pause(); return;
    }

    Review r;
    cin.ignore();
    cout << "Nama: "; getline(cin, r.nama);
    cout << "Komentar: "; getline(cin, r.komentar);
    cout << "Rating (1-10): "; cin >> r.rating;

    filmList[idx].daftarReview.push_back(r);
    historyUndo.push({idx, r});

    float total = 0;
    for (auto& rev : filmList[idx].daftarReview) total += rev.rating;
    filmList[idx].rataRataRating = total / filmList[idx].daftarReview.size();

    cout << "Review berhasil ditambahkan!\n";
    pause();
}

void lihatReview(int idx) {
    clearScreen();
    if (idx < 0 || idx >= filmList.size()) {
        cout << "Nomor film tidak valid.\n";
        pause(); return;
    }

    cout << "Review untuk " << filmList[idx].judul << ":\n";
    for (auto& r : filmList[idx].daftarReview)
        cout << "- " << r.nama << ": " << r.komentar << " (Rating: " << r.rating << ")\n";
    pause();
}

void undoReview() {
    clearScreen();
    if (historyUndo.empty()) {
        cout << "Tidak ada review yang bisa di-undo.\n";
        pause(); return;
    }

    pair<int, Review> data = historyUndo.top(); historyUndo.pop();
    int idx = data.first; Review rev = data.second;

    auto& reviews = filmList[idx].daftarReview;
    reviews.erase(remove_if(reviews.begin(), reviews.end(), [&](Review& r) {
        return r.nama == rev.nama && r.komentar == rev.komentar && r.rating == rev.rating;
    }), reviews.end());

    float total = 0;
    for (auto& r : reviews) total += r.rating;
    filmList[idx].rataRataRating = reviews.empty() ? 0.0 : total / reviews.size();

    cout << "Review terakhir berhasil dihapus.\n";
    pause();
}

void cariFilm(string keyword) {
    clearScreen();
    cout << "Hasil pencarian:\n";
    for (int i = 0; i < filmList.size(); ++i) {
        if (filmList[i].judul.find(keyword) != string::npos)
            cout << i + 1 << ". " << filmList[i].judul << " (" << filmList[i].genre << ")\n";
    }
    pause();
}

void urutkanFilm() {
    clearScreen();
    int pilihan;
    cout << "Urutkan berdasarkan:\n1. Rating Tertinggi\n2. Rating Terendah\nPilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        sort(filmList.begin(), filmList.end(), [](Film& a, Film& b) { return a.rataRataRating > b.rataRataRating; });
    } else if (pilihan == 2) {
        sort(filmList.begin(), filmList.end(), [](Film& a, Film& b) { return a.rataRataRating < b.rataRataRating; });
    } else {
        cout << "Pilihan tidak valid.\n";
        pause(); return;
    }

    tampilFilm();
}

void beliTiket() {
    clearScreen();
    set<string> genreSet;
    for (auto& f : filmList) genreSet.insert(f.genre);
    vector<string> genreList(genreSet.begin(), genreSet.end());

    cout << "Pilih genre film:\n";
    for (int i = 0; i < genreList.size(); ++i) cout << i + 1 << ". " << genreList[i] << endl;

    int genreIdx;
    cout << "Masukkan nomor genre: ";
    cin >> genreIdx;

    if (genreIdx < 1 || genreIdx > genreList.size()) {
        cout << "Pilihan tidak valid.\n";
        pause(); return;
    }

    string genreDipilih = genreList[genreIdx - 1];
    vector<Film> pilihan;
    for (auto& f : filmList)
        if (f.genre == genreDipilih) pilihan.push_back(f);

    cout << "Film tersedia:\n";
    for (int i = 0; i < pilihan.size(); ++i)
        cout << i + 1 << ". " << pilihan[i].judul << " | Harga: Rp. " << hargaFilm[pilihan[i].judul] << endl;

    int idx;
    cout << "Pilih nomor film: ";
    cin >> idx;

    if (idx < 1 || idx > pilihan.size()) {
        cout << "Pilihan tidak valid.\n";
        pause(); return;
    }

    string filmDipilih = pilihan[idx - 1].judul;
    cout << "Konfirmasi beli " << filmDipilih << " seharga Rp. " << hargaFilm[filmDipilih] << "? (y/n): ";
    char konfirmasi; cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        tiketSaya[filmDipilih]++;
        cout << "Tiket berhasil dibeli!\n";
    } else {
        cout << "Pembelian dibatalkan.\n";
    }
    pause();
}

void lihatTiketSaya() {
    clearScreen();
    if (tiketSaya.empty()) {
        cout << "Belum ada tiket yang dibeli.\n";
    } else {
        cout << "Tiket yang sudah dibeli:\n";
        int nomor = 1;
        for (auto& tiket : tiketSaya) {
            int totalHarga = tiket.second * hargaFilm[tiket.first];
            cout << nomor++ << ". " << tiket.first << " x" << tiket.second << " | Total Harga: Rp. " << totalHarga << endl;
        }
    }
    pause();
}

void tontonFilm() {
    clearScreen();
    if (tiketSaya.empty()) {
        cout << "Tidak ada tiket tersedia.\n";
    } else {
        srand(time(0));
        int nomor = 1;
        for (auto& tiket : tiketSaya) {
            for (int i = 0; i < tiket.second; ++i) {
                int kursi = rand() % 100 + 1;
                cout << nomor++ << ". " << tiket.first << " | Jadwal: " << jadwalFilm[tiket.first] << " | Kursi: " << kursi << endl;
            }
        }
    }
    pause();
}

int main() {
    tambahFilm("Inception", "Sci-Fi");
    tambahFilm("Interstellar", "Sci-Fi");
    tambahFilm("The Matrix", "Sci-Fi");
    tambahFilm("Spirited Away", "Fantasy");
    tambahFilm("Howl's Moving Castle", "Fantasy");
    tambahFilm("Harry Potter", "Fantasy");
    tambahFilm("Parasite", "Thriller");
    tambahFilm("Gone Girl", "Thriller");
    tambahFilm("Joker", "Thriller");
    tambahFilm("The Conjuring", "Horror");
    tambahFilm("Insidious", "Horror");
    tambahFilm("Hereditary", "Horror");

    int pilihan;
    do {
        clearScreen();
        cout << "===== BIOSKOP MENU =====\n";
        cout << "1. Beli Tiket\n2. Tiket Saya\n3. Tonton Film\n4. Lihat Daftar Film\n";
        cout << "5. Tambah Review\n6. Lihat Review\n7. Undo Review\n8. Cari Film\n9. Urutkan Film\n10. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: beliTiket(); break;
            case 2: lihatTiketSaya(); break;
            case 3: tontonFilm(); break;
            case 4: tampilFilm(); break;
            case 5: {
                tampilFilm();
                int idx; cout << "Pilih nomor film: "; cin >> idx;
                tambahReview(idx - 1); break;
            }
            case 6: {
                tampilFilm();
                int idx; cout << "Pilih nomor film: "; cin >> idx;
                lihatReview(idx - 1); break;
            }
            case 7: undoReview(); break;
            case 8: {
                cin.ignore();
                string key; cout << "Judul: "; getline(cin, key);
                cariFilm(key); break;
            }
            case 9: urutkanFilm(); break;
            case 10: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n"; pause(); break;
        }

    } while (pilihan != 10);

    return 0;
}
