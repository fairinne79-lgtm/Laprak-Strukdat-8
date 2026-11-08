#include <iostream>
#include <sstream>
#include <string>
#include <climits>
#include "paket.h"
using namespace std;

static bool parseInt(const string& s, int& out) {
    try {
        size_t pos = 0;
        long long v = stoll(s, &pos);
        if (pos != s.size() || v < INT_MIN || v > INT_MAX) return false;
        out = static_cast<int>(v);
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    Queue A, B;
    createQueue(A);
    createQueue(B);
    long terkirimN = 0, terkirimGram = 0;

    string baris;
    while (getline(cin, baris)) {
        istringstream in(baris);
        string cmd;
        if (!(in >> cmd)) continue;

        string arg[3], tok;
        int na = 0;
        while (in >> tok) {
            if (na < 3) arg[na] = tok;
            na++;
        }

        if (cmd == "SELESAI") {
            break;
        }
        else if (cmd == "MASUK") {
            int berat;
            if (na != 2) { cout << "DITOLAK: format MASUK kode berat\n"; continue; }
            const string& kode = arg[0];
            if (kode.size() < 1 || kode.size() > 10) {
                cout << "DITOLAK: kode harus 1-10 karakter\n"; continue;
            }
            if (!parseInt(arg[1], berat) || berat < 1 || berat > 5000) {
                cout << "DITOLAK: berat harus bilangan bulat 1-5000\n"; continue;
            }
            if (findElm(A, kode) != nullptr || findElm(B, kode) != nullptr) {
                cout << "DITOLAK: kode " << kode << " sudah aktif\n"; continue;
            }
            Node* p = alokasi(kode, berat);
            if (p == nullptr) { cout << "DITOLAK: alokasi gagal\n"; continue; }
            enqueue(A, p);
            cout << "OK: " << kode << " masuk ke A\n";
        }
        else if (cmd == "PINDAH") {
            int n;
            if (na != 1 || !parseInt(arg[0], n)) {
                cout << "DITOLAK: format PINDAH n (n bilangan bulat)\n"; continue;
            }
            if (n <= 0) { cout << "DITOLAK: n harus positif\n"; continue; }
            if (n > nbList(A)) {
                cout << "DITOLAK: A hanya berisi " << nbList(A) << " paket\n"; continue;
            }
            for (int i = 0; i < n; i++) {
                Node* p = dequeue(A);
                enqueue(B, p);                 // node yang sama, alamat tetap
            }
            cout << "OK: " << n << " paket dipindah dari A ke B\n";
        }
        else if (cmd == "KIRIM") {
            int n;
            if (na != 1 || !parseInt(arg[0], n)) {
                cout << "DITOLAK: format KIRIM n (n bilangan bulat)\n"; continue;
            }
            if (n <= 0) { cout << "DITOLAK: n harus positif\n"; continue; }
            if (n > nbList(B)) {
                cout << "DITOLAK: B hanya berisi " << nbList(B) << " paket\n"; continue;
            }
            int gram = 0;
            for (int i = 0; i < n; i++) {
                Node* p = dequeue(B);
                cout << "Terkirim: " << p->info.kode << " (" << p->info.berat << " gram)\n";
                gram += p->info.berat;
                terkirimN++;
                terkirimGram += p->info.berat;
                dealokasi(p);
            }
            cout << "OK: " << n << " paket terkirim, " << gram << " gram\n";
        }
        else if (cmd == "CARI") {
            if (na != 1) { cout << "DITOLAK: format CARI kode\n"; continue; }
            char lok = 'A';
            Node* p = findElm(A, arg[0]);
            if (p == nullptr) { p = findElm(B, arg[0]); lok = 'B'; }
            if (p == nullptr) {
                cout << "TIDAK DITEMUKAN\n";
            } else {
                Queue& q = (lok == 'A') ? A : B;
                cout << p->info.kode << ": antrean " << lok
                     << ", posisi " << posisiElm(q, p)
                     << ", berat " << p->info.berat << " gram\n";
            }
        }
        else if (cmd == "ALAMAT") {   // bantu uji fFindElm
            if (na != 1) { cout << "DITOLAK: format ALAMAT kode\n"; continue; }
            Node* p = findElm(A, arg[0]);
            if (p == nullptr) p = findElm(B, arg[0]);
            if (p == nullptr) { cout << "TIDAK DITEMUKAN\n"; continue; }
            cout << arg[0] << ": alamat " << static_cast<const void*>(p)
                 << ", anggota A = " << (fFindElm(A, p) ? "ya" : "tidak")
                 << ", anggota B = " << (fFindElm(B, p) ? "ya" : "tidak") << "\n";
        }
        else if (cmd == "LIHAT") {
            cout << "A: "; printInfo(A);
            cout << "B: "; printInfo(B);
        }
        else if (cmd == "REKAP") {
            cout << "A       : " << nbList(A) << " paket, " << totalBerat(A) << " gram\n";
            cout << "B       : " << nbList(B) << " paket, " << totalBerat(B) << " gram\n";
            cout << "Terkirim: " << terkirimN << " paket, " << terkirimGram << " gram\n";
        }
        else if (cmd == "BERSIHKAN") {
            delAll(A);
            delAll(B);
            cout << "OK: A dan B dibersihkan (statistik terkirim tidak berubah)\n";
        }
        else {
            cout << "DITOLAK: perintah tidak dikenal\n";
        }
    }

    delAll(A);
    delAll(B);
    cout << "Program selesai.\n";
    return 0;
}