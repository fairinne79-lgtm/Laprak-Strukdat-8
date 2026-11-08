#ifndef BUFFER_H
#define BUFFER_H

const int KAP = 6;

struct Rekaman {
    int nomor;
    int nilai;
};

struct Buffer {
    Rekaman data[KAP];
    int head;
#ifdef VERSI_CIRCULAR
    int count;          // versi 3: head + count, tanpa tail
#else
    int tail;           // versi 1 dan 2: head + tail
#endif
    int nomorBerikut;
    long long geser;    // banyak rekaman yang dipindahkan karena pergeseran
};

void createBuffer(Buffer& b);
bool isEmpty(const Buffer& b);
int  ukuran(const Buffer& b);
int  ruang(const Buffer& b);
bool enqueue(Buffer& b, int nilai);            // false jika penuh
bool dequeue(Buffer& b, Rekaman& out);         // false jika kosong
Rekaman lihatKe(const Buffer& b, int i);       // rekaman ke-i urutan FIFO (0-based)
bool bacaFisik(const Buffer& b, int idx, Rekaman& out); // true jika indeks fisik terisi
void cetakPenanda(const Buffer& b);            // head/tail atau head/count
void kosongkan(Buffer& b);                     // tidak mereset nomor & penghitung geser
long long jumlahGeser(const Buffer& b);
int  nomorBerikutnya(const Buffer& b);

#endif