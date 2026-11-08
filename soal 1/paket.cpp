#include "paket.h"
#include <iostream>
#include <new>

void createQueue(Queue& q) {
    q.head = nullptr;
    q.tail = nullptr;
}

bool isEmptyQueue(const Queue& q) {
    return q.head == nullptr;
}

Node* alokasi(const std::string& kode, int berat) {
    Node* p = new (std::nothrow) Node;
    if (p != nullptr) {
        p->info.kode = kode;
        p->info.berat = berat;
        p->next = nullptr;
    }
    return p;
}

void dealokasi(Node*& p) {
    delete p;
    p = nullptr;
}

void enqueue(Queue& q, Node* p) {
    if (p == nullptr) return;
    p->next = nullptr;              // node baru selalu jadi ujung
    if (isEmptyQueue(q)) {
        q.head = p;
        q.tail = p;
    } else {
        q.tail->next = p;
        q.tail = p;
    }
}

Node* dequeue(Queue& q) {
    if (isEmptyQueue(q)) return nullptr;
    Node* p = q.head;
    q.head = p->next;
    if (q.head == nullptr) q.tail = nullptr;   // queue jadi kosong
    p->next = nullptr;                          // node lepas
    return p;
}

Node* findElm(const Queue& q, const std::string& kode) {
    for (Node* cur = q.head; cur != nullptr; cur = cur->next)
        if (cur->info.kode == kode) return cur;
    return nullptr;
}

bool fFindElm(const Queue& q, const Node* p) {
    if (p == nullptr) return false;
    for (const Node* cur = q.head; cur != nullptr; cur = cur->next)
        if (cur == p) return true;              // hanya bandingkan alamat
    return false;
}

int nbList(const Queue& q) {
    int n = 0;
    for (Node* cur = q.head; cur != nullptr; cur = cur->next) n++;
    return n;
}

int posisiElm(const Queue& q, const Node* p) {
    int pos = 1;
    for (const Node* cur = q.head; cur != nullptr; cur = cur->next, pos++)
        if (cur == p) return pos;
    return 0;
}

int totalBerat(const Queue& q) {
    int total = 0;
    for (Node* cur = q.head; cur != nullptr; cur = cur->next)
        total += cur->info.berat;
    return total;
}

void printInfo(const Queue& q) {
    if (isEmptyQueue(q)) {
        std::cout << "(kosong)\n";
        return;
    }
    for (Node* cur = q.head; cur != nullptr; cur = cur->next) {
        std::cout << cur->info.kode << "(" << cur->info.berat << "g)";
        if (cur->next != nullptr) std::cout << " -> ";
    }
    std::cout << "\n";
}

void delAll(Queue& q) {
    while (!isEmptyQueue(q)) {
        Node* p = dequeue(q);
        dealokasi(p);
    }
}