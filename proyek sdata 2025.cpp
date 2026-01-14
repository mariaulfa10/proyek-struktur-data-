#include <iostream>
#include <string>
#include <ctime>
using namespace std;

/* ================================
   ARRAY – Data Pasien
   ================================ */

struct BiodataPasien {
    int noantrian;
    string nama, alamat, telp, umur;
    string jamdaftar;
    string pelayanan;
};

BiodataPasien arrpasien[200];
int pasien = 0;
int noantrian = 0;

/* ================================
   QUEUE – Antrian Pasien (FIFO)
   ================================ */

int queueAntrian[200];
int front = 0, rear = -1;

void enqueue(int no) {
    queueAntrian[++rear] = no;
}

int dequeue() {
    return queueAntrian[front++];
}

/* ================================
   STACK – Riwayat Pasien (LIFO)
   ================================ */

int stackRiwayat[200];
int top = -1;

void push(int no) {
    stackRiwayat[++top] = no;
}

/* ================================
   LINKED LIST – Data Dinamis
   ================================ */

struct Node {
    BiodataPasien data;
    Node* next;
};

Node* head = NULL;

void tambahLinkedList(BiodataPasien p) {
    Node* baru = new Node();
    baru->data = p;
    baru->next = head;
    head = baru;
}

/* ================================
   TREE – Struktur Poli
   ================================ */

struct Poli {
    string nama;
    Poli* kiri;
    Poli* kanan;
};

Poli* buatPoli(string nama) {
    Poli* p = new Poli();
    p->nama = nama;
    p->kiri = NULL;
    p->kanan = NULL;
    return p;
}

/* ================================
   JAM & TANGGAL
   ================================ */

string waktudaftar() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

/* ================================
   PILIH PELAYANAN
   ================================ */

string pilihPelayanan(int p) {
    switch (p) {
        case 1: return "Rawat Inap";
        case 2: return "Rawat Jalan";
        case 3: return "Gawat Darurat";
        case 4: return "Radiologi";
        case 5: return "Bedah";
        default: return "Tidak Valid";
    }
}

/* ================================
   FUNGSI UMUM
   ================================ */

void tekanEnter() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

/* ================================
   INPUT PASIEN
   ================================ */

void inputPasien() {
    cin.ignore();
    cout << "Nama Pasien : ";
    getline(cin, arrpasien[pasien].nama);

    cout << "Umur        : ";
    cin >> arrpasien[pasien].umur;

    cin.ignore();
    cout << "Alamat      : ";
    getline(cin, arrpasien[pasien].alamat);

    cout << "No Telepon  : ";
    cin >> arrpasien[pasien].telp;

    cout << "\nPilih Pelayanan\n";
    cout << "1. Rawat Inap\n";
    cout << "2. Rawat Jalan\n";
    cout << "3. Gawat Darurat\n";
    cout << "4. Radiologi\n";
    cout << "5. Bedah\n";
    cout << "Pilihan : ";

    int p;
    cin >> p;

    arrpasien[pasien].pelayanan = pilihPelayanan(p);
    arrpasien[pasien].noantrian = ++noantrian;
    arrpasien[pasien].jamdaftar = waktudaftar();

    enqueue(arrpasien[pasien].noantrian);
    tambahLinkedList(arrpasien[pasien]);

    pasien++;

    cout << "\nPasien berhasil ditambahkan!";
    tekanEnter();
}

/* ================================
   PANGGIL PASIEN
   ================================ */

void panggilPasien() {
    if (front > rear) {
        cout << "Antrian kosong!";
        tekanEnter();
        return;
    }

    int no = dequeue();
    push(no);

    cout << "\nMemanggil Pasien No Antrian : " << no;
    tekanEnter();
}

/* ================================
   TAMPILKAN DATA PASIEN
   ================================ */

void tampilPasien() {
    cout << "\n===== DATA PASIEN =====\n";

    for (int i = 0; i < pasien; i++) {
        cout << "\nNo Antrian : " << arrpasien[i].noantrian;
        cout << "\nNama       : " << arrpasien[i].nama;
        cout << "\nPelayanan  : " << arrpasien[i].pelayanan;
        cout << "\nWaktu      : " << arrpasien[i].jamdaftar;
        cout << "\n---------------------------";
    }

    tekanEnter();
}

/* ================================
   MAIN PROGRAM
   ================================ */

int main() {

    Poli* root = buatPoli("Rumah Sakit");
    root->kiri = buatPoli("Poli Umum");
    root->kanan = buatPoli("Poli Spesialis");

    int pilih;
    do {
        system("cls");
        cout << "====================================\n";
        cout << " SISTEM ANTRIAN RUMAH SAKIT\n";
        cout << "====================================\n";
        cout << "1. Input Pasien\n";
        cout << "2. Panggil Pasien\n";
        cout << "3. Lihat Data Pasien\n";
        cout << "4. Keluar\n";
        cout << "Pilih Menu : ";
        cin >> pilih;

        switch (pilih) {
            case 1: inputPasien(); break;
            case 2: panggilPasien(); break;
            case 3: tampilPasien(); break;
            case 4: cout << "\nTerima kasih 💙\n"; break;
            default: cout << "Menu tidak valid!"; tekanEnter();
        }

    } while (pilih != 4);

    return 0;
}
