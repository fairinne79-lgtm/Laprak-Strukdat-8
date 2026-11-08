#ifndef VERSI_CIRCULAR
#error "Versi 3 harus dikompilasi dengan -DVERSI_CIRCULAR"
#endif
#include "buffer.h"
#include <iostream>

void createBuffer(Buffer& b) {
    b.head = 0;
    b.count = 0;
    b.nomorBerikut = 1;
    b.geser = 0;
}

bool isEmpty(const Buffer& b) { return b.count == 0; }

int ukuran(const Buffer& b) { return b.count; }

int ruang(const Buffer& b) { return KAP - b.count; }

bool enqueue(Buffer& b, int nilai) {
    if (b.count == KAP) return false;
    int pos = (b.head + b.count) % KAP;         // posisi tulis
    b.data[pos].nomor = b.nomorBerikut++;
    b.data[pos].nilai = nilai;
    b.count++;
    return true;
}

bool dequeue(Buffer& b, Rekaman& out) {
    if (isEmpty(b)) return false;
    out = b.data[b.head];
    b.head = (b.head + 1) % KAP;
    b.count--;
    if (b.count == 0) b.head = 0;               // keadaan kosong: head = count = 0
    return true;
}

Rekaman lihatKe(const Buffer& b, int i) { return b.data[(b.head + i) % KAP]; }

bool bacaFisik(const Buffer& b, int idx, Rekaman& out) {
    if ((idx - b.head + KAP) % KAP >= b.count) return false;
    out = b.data[idx];
    return true;
}

void cetakPenanda(const Buffer& b) {
    std::cout << "head = " << b.head << ", count = " << b.count
              << " (indeks data terakhir = "
              << (b.count == 0 ? -1 : (b.head + b.count - 1) % KAP) << ")\n";
}

void kosongkan(Buffer& b) { b.head = 0; b.count = 0; }

long long jumlahGeser(const Buffer& b) { return b.geser; }

int nomorBerikutnya(const Buffer& b) { return b.nomorBerikut; }