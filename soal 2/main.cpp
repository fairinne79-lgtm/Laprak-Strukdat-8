#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <climits>
#include "buffer.h"
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
    Buffer b;
    createBuffer(b);

    string baris;
    while (getline(cin, baris)) {
        istringstream in(baris);
        string cmd;
        if (!(in >> cmd)) continue;

        string arg[8], tok;
        int na = 0;
        while (in >> tok) {
            if (na < 8) arg[na] = tok;
            na++;
        }

        if (cmd == "SELESAI") {
            break;
        }
        else if (cmd == "TULIS") {
            int k;
            if (na < 1 || !parseInt(arg[0], k)) {
                cout << "DITOLAK: format TULIS k v1 ... vk\n"; continue;
            }
            if (k < 1 || k > KAP) { cout << "DITOLAK: k harus 1-" << KAP << "\n"; continue; }
            if (na - 1 != k) {
                cout << "DITOLAK: jumlah nilai (" << na - 1 << ") tidak sama dengan k\n"; continue;
            }
            int nilai[KAP];
            bool ok = true;
            for (int i = 0; i < k && ok; i++) {
                if (!parseInt(arg[i + 1], nilai[i])) {
                    cout << "DITOLAK: '" << arg[i + 1] << "' bukan bilangan bulat valid\n"; ok = false;
                } else if (nilai[i] < -1000 || nilai[i] > 1000) {
                    cout << "DITOLAK: nilai " << nilai[i] << " di luar rentang -1000..1000\n"; ok = false;
                }
            }
            if (!ok) continue;
            if (ruang(b) < k) {
                cout << "DITOLAK: ruang kosong hanya " << ruang(b) << "\n"; continue;
            }
            for (int i = 0; i < k; i++) enqueue(b, nilai[i]);
            cout << "Berhasil menulis " << k << " rekaman\n";
        }
        else if (cmd == "AMBIL") {
            int k;
            if (na != 1 || !parseInt(arg[0], k)) {
                cout << "DITOLAK: format AMBIL k\n"; continue;
            }
            if (k < 1 || k > KAP) { cout << "DITOLAK: k harus 1-" << KAP << "\n"; continue; }
            if (k > ukuran(b)) {
                cout << "DITOLAK: data hanya " << ukuran(b) << " rekaman\n"; continue;
            }
            for (int i = 0; i < k; i++) {
                Rekaman r;
                dequeue(b, r);
                cout << "Keluar " << r.nomor << ":" << r.nilai << "\n";
            }
        }
        else if (cmd == "LIHAT") {
            cout << "FIFO   : ";
            if (isEmpty(b)) cout << "(kosong)";
            for (int i = 0; i < ukuran(b); i++) {
                Rekaman r = lihatKe(b, i);
                cout << (i ? ", " : "") << r.nomor << ":" << r.nilai;
            }
            cout << "\nFisik  :\n";
            for (int i = 0; i < KAP; i++) {
                Rekaman r;
                cout << "  [" << i << "] ";
                if (bacaFisik(b, i, r)) cout << r.nomor << ":" << r.nilai << "\n";
                else cout << "-\n";
            }
            cout << "Penanda: "; cetakPenanda(b);
            cout << "Nomor berikutnya : " << nomorBerikutnya(b) << "\n";
            cout << "Total pergeseran : " << jumlahGeser(b) << " rekaman\n";
        }
        else if (cmd == "RINGKAS") {
            int n = ukuran(b);
            long long total = 0;
            int mn = 0, mx = 0;
            for (int i = 0; i < n; i++) {
                int v = lihatKe(b, i).nilai;
                total += v;
                if (i == 0 || v < mn) mn = v;
                if (i == 0 || v > mx) mx = v;
            }
            cout << "Jumlah   : " << n << "\n";
            cout << "Total    : " << total << "\n";
            if (n == 0) {
                cout << "Minimum  : TIDAK ADA\nMaksimum : TIDAK ADA\nRata-rata: TIDAK ADA\n";
            } else {
                cout << "Minimum  : " << mn << "\n";
                cout << "Maksimum : " << mx << "\n";
                cout << "Rata-rata: " << fixed << setprecision(2)
                     << static_cast<double>(total) / n << "\n";
            }
        }
        else if (cmd == "KOSONGKAN") {
            kosongkan(b);
            cout << "Buffer dikosongkan (nomor berikutnya " << nomorBerikutnya(b)
                 << ", pergeseran " << jumlahGeser(b) << " tetap)\n";
        }
        else {
            cout << "DITOLAK: perintah tidak dikenal\n";
        }
    }

    cout << "Program selesai. Total pergeseran: " << jumlahGeser(b) << " rekaman\n";
    return 0;
}