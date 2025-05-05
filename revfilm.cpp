#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

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

vector<Film> filmList;
stack<pair<int, Review>> historyUndo;

void tambahFilm(string judul, string genre) {
    filmList.push_back({judul, genre, 0.0, {}});
}

void tampilFilm() {
    for (int i = 0; i < filmList.size(); ++i) {
        cout << i + 1 << ". " << filmList[i].judul << " (" << filmList[i].genre
             << ") | Rating: " << filmList[i].rataRataRating << endl;
    }
}

void tambahReview(int idx) {
    if (idx < 0 || idx >= filmList.size()) {
        cout << "Nomor film tidak valid.\n";
        return;
    }

    Review r;
    cin.ignore();
    cout << "Nama: ";
    getline(cin, r.nama);
    cout << "Komentar: ";
    getline(cin, r.komentar);
    cout << "Rating (1-10): ";
    cin >> r.rating;

    filmList[idx].daftarReview.push_back(r);
    historyUndo.push({idx, r});

    float total = 0;
    for (auto& rev : filmList[idx].daftarReview) total += rev.rating;
    filmList[idx].rataRataRating = total / filmList[idx].daftarReview.size();

    cout << "Review berhasil ditambahkan!\n";
}

void lihatReview(int idx) {
    if (idx < 0 || idx >= filmList.size()) {
        cout << "Nomor film tidak valid.\n";
        return;
    }

    cout << "Review untuk " << filmList[idx].judul << ":\n";
    for (auto& r : filmList[idx].daftarReview) {
        cout << "- " << r.nama << ": " << r.komentar << " (Rating: " << r.rating << ")\n";
    }
}

void undoReview() {
    if (historyUndo.empty()) {
        cout << "Tidak ada review yang bisa di-undo.\n";
        return;
    }

    pair<int, Review> data = historyUndo.top();
    historyUndo.pop();

    int idx = data.first;
    Review rev = data.second;

    if (idx >= filmList.size()) return;

    auto& reviews = filmList[idx].daftarReview;
    reviews.erase(remove_if(reviews.begin(), reviews.end(), [&](Review& r) {
        return r.nama == rev.nama && r.komentar == rev.komentar && r.rating == rev.rating;
    }), reviews.end());

    float total = 0;
    for (auto& r : reviews) total += r.rating;
    filmList[idx].rataRataRating = reviews.empty() ? 0.0 : total / reviews.size();

    cout << "Review terakhir berhasil dihapus.\n";
}

void cariFilm(string keyword) {
    cout << "Hasil pencarian:\n";
    for (int i = 0; i < filmList.size(); ++i) {
        if (filmList[i].judul.find(keyword) != string::npos) {
            cout << i + 1 << ". " << filmList[i].judul << " (" << filmList[i].genre << ")\n";
        }
    }
}

void urutkanFilm() {
    sort(filmList.begin(), filmList.end(), [](Film& a, Film& b) {
        return a.rataRataRating > b.rataRataRating;
    });
    cout << "Film telah diurutkan berdasarkan rating tertinggi.\n";
}

int main() {
    tambahFilm("Inception", "Sci-Fi");
    tambahFilm("Spirited Away", "Fantasy");
    tambahFilm("Parasite", "Thriller");

    int pilihan;
    do {
        cout << "\nMenu:\n"
             << "1. Lihat Daftar Film\n"
             << "2. Tambah Review\n"
             << "3. Lihat Review\n"
             << "4. Undo Review\n"
             << "5. Cari Film\n"
             << "6. Urutkan Film\n"
             << "7. Keluar\n"
             << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilFilm(); break;
            case 2: {
                tampilFilm();
                cout << "Pilih nomor film: ";
                int idx; cin >> idx;
                tambahReview(idx - 1);
                break;
            }
            case 3: {
                tampilFilm();
                cout << "Pilih nomor film: ";
                int idx; cin >> idx;
                lihatReview(idx - 1);
                break;
            }
            case 4: undoReview(); break;
            case 5: {
                cin.ignore();
                cout << "Masukkan judul film: ";
                string key; getline(cin, key);
                cariFilm(key);
                break;
            }
            case 6: urutkanFilm(); break;
            case 7: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n"; break;
        }
    } while (pilihan != 7);

    return 0;
}
