#ifdef VERSI_CIRCULAR
#error "Versi 1 harus dikompilasi tanpa -DVERSI_CIRCULAR"
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
    if (b.tail == KAP - 1) return false;       // penuh (head selalu 0)
    if (isEmpty(b)) b.head = b.tail = 0;
    else b.tail++;
    b.data[b.tail].nomor = b.nomorBerikut++;
    b.data[b.tail].nilai = nilai;
    return true;
}

bool dequeue(Buffer& b, Rekaman& out) {
    if (isEmpty(b)) return false;
    out = b.data[b.head];                      // head == 0
    if (b.tail == b.head) {                    // elemen terakhir
        b.head = b.tail = -1;
        return true;
    }
    for (int i = b.head + 1; i <= b.tail; i++) {
        b.data[i - 1] = b.data[i];
        b.geser++;                             // satu rekaman dipindah satu kali
    }
    b.tail--;
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