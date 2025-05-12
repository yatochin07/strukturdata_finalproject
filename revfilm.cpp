
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

// Deklarasi fungsi
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

vector<Film> filmList;
map<string, int> tiketSaya;
stack<pair<int, Review>> historyUndo;
map<string, string> jadwalFilm = {
    {"Inception", "10:00 WIB"},
    {"Interstellar", "12:00 WIB"},
    {"The Matrix", "14:00 WIB"},
    {"Spirited Away", "10:30 WIB"},
    {"Howl's Moving Castle", "13:00 WIB"},
    {"Harry Potter", "15:30 WIB"},
    {"Parasite", "11:00 WIB"},
    {"Gone Girl", "13:30 WIB"},
    {"Joker", "16:00 WIB"},
    {"The Conjuring", "17:00 WIB"},
    {"Insidious", "18:30 WIB"},
    {"Hereditary", "20:00 WIB"}
};
map<string, int> hargaFilm = {
    {"Inception", 50000},
    {"Interstellar", 50000},
    {"The Matrix", 50000},
    {"Spirited Away", 45000},
    {"Howl's Moving Castle", 45000},
    {"Harry Potter", 45000},
    {"Parasite", 55000},
    {"Gone Girl", 55000},
    {"Joker", 55000},
    {"The Conjuring", 60000},
    {"Insidious", 60000},
    {"Hereditary", 60000}
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

// (Function bodies for tampilFilm, tambahReview, lihatReview, undoReview, cariFilm,
// urutkanFilm, beliTiket, lihatTiketSaya, tontonFilm, and main() will be filled here.)