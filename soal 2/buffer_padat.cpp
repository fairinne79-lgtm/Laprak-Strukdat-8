#ifdef VERSI_CIRCULAR
#error "Versi 2 harus dikompilasi tanpa -DVERSI_CIRCULAR"
#endif
#include "buffer.h"
#include <iostream>

void createBuffer(Buffer& b) {
    b.head = -1;
    b.tail = -1;
    b.nomorBerikut = 1;
    b.geser = 0;
}

bool isEmpty(const Buffer& b) { return b.head == -1; }

int ukuran(const Buffer& b) { return isEmpty(b) ? 0 : b.tail - b.head + 1; }

int ruang(const Buffer& b) { return KAP - ukuran(b); }

bool enqueue(Buffer& b, int nilai) {
    if (isEmpty(b)) {
        b.head = b.tail = 0;
    } else {
        if (b.tail == KAP - 1) {               // butuh ruang dan tail di indeks 5
            if (b.head == 0) return false;     // benar-benar penuh
            int n = ukuran(b);
            for (int i = 0; i < n; i++) {
                b.data[i] = b.data[b.head + i];
                b.geser++;
            }
            b.head = 0;
            b.tail = n - 1;
        }
        b.tail++;
    }
    b.data[b.tail].nomor = b.nomorBerikut++;
    b.data[b.tail].nilai = nilai;
    return true;
}

bool dequeue(Buffer& b, Rekaman& out) {
    if (isEmpty(b)) return false;
    out = b.data[b.head];
    if (b.head == b.tail) b.head = b.tail = -1;
    else b.head++;                              // hanya memajukan head
    return true;
}

Rekaman lihatKe(const Buffer& b, int i) { return b.data[b.head + i]; }

bool bacaFisik(const Buffer& b, int idx, Rekaman& out) {
    if (isEmpty(b) || idx < b.head || idx > b.tail) return false;
    out = b.data[idx];
    return true;
}

void cetakPenanda(const Buffer& b) {
    std::cout << "head = " << b.head << ", tail = " << b.tail << "\n";
}

void kosongkan(Buffer& b) { b.head = b.tail = -1; }

long long jumlahGeser(const Buffer& b) { return b.geser; }

int nomorBerikutnya(const Buffer& b) { return b.nomorBerikut; }