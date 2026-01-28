#include <iostream>
#include <string>
using namespace std;

/* ================= ARRAY BED ================= */
const int JUMLAH_BED = 10;
int bedPemesan[JUMLAH_BED];

void initBed() {
    for (int i = 0; i < JUMLAH_BED; i++)
        bedPemesan[i] = -1;
}

void tampilBed() {
    for (int i = 0; i < JUMLAH_BED; i++) {
        if (bedPemesan[i] == -1)
            cout << "Bed " << i + 1 << " (Kosong)\n";
        else
            cout << "Bed " << i + 1 << " (Terisi Pasien ID "
                 << bedPemesan[i] << ")\n";
    }
}

/* ================= LINKED LIST PASIEN ================= */
struct Pasien {
    int id;
    string nama;
    int bed;
    string status;
    Pasien* next;
};

Pasien* head = NULL;

void tambahPasien(string nama, int id) {
    Pasien* p = new Pasien{id, nama, -1, "Menunggu", NULL};
    if (!head) head = p;
    else {
        Pasien* t = head;
        while (t->next) t = t->next;
        t->next = p;
    }
}

Pasien* cariPasien(int id) {
    Pasien* p = head;
    while (p) {
        if (p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

/* ================= QUEUE ================= */
struct Queue {
    int data[100];
    int front, rear;

    Queue() { front = 0; rear = -1; }
    bool kosong() { return front > rear; }

    void enqueue(int x) { data[++rear] = x; }
    int dequeue() { return data[front++]; }

    void insertFront(int x) {
        for (int i = rear + 1; i > front; i--)
            data[i] = data[i - 1];
        data[front] = x;
        rear++;
    }
} antrean;

/* ================= STACK UNDO ================= */
struct Stack {
    int data[100];
    int top;
    Stack() { top = -1; }

    void push(int x) { data[++top] = x; }
    int pop() { return data[top--]; }
    bool kosong() { return top == -1; }
} undoStack;

/* ================= LINKED LIST RIWAYAT ================= */
struct Riwayat {
    int id;
    Riwayat* next;
};

Riwayat* headRiwayat = NULL;

void tambahRiwayat(int id) {
    Riwayat* r = new Riwayat{id, NULL};
    if (!headRiwayat) headRiwayat = r;
    else {
        Riwayat* t = headRiwayat;
        while (t->next) t = t->next;
        t->next = r;
    }
}

void tampilRiwayat() {
    if (!headRiwayat) {
        cout << "Belum ada riwayat.\n";
        return;
    }

    Riwayat* r = headRiwayat;
    while (r) {
        cout << "Pasien ID " << r->id << " pernah dirawat\n";
        r = r->next;
    }
}

void hapusRiwayat(int id) {
    if (!headRiwayat) return;

    if (headRiwayat->id == id) {
        Riwayat* temp = headRiwayat;
        headRiwayat = headRiwayat->next;
        delete temp;
        return;
    }

    Riwayat* prev = headRiwayat;
    Riwayat* curr = headRiwayat->next;

    while (curr) {
        if (curr->id == id) {
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/* ================= BST UNTUK SEARCH RIWAYAT ================= */
struct NodeBST {
    int id;
    NodeBST* left;
    NodeBST* right;
};

NodeBST* rootBST = NULL;

NodeBST* insertBST(NodeBST* node, int id) {
    if (!node)
        return new NodeBST{id, NULL, NULL};

    if (id < node->id)
        node->left = insertBST(node->left, id);
    else
        node->right = insertBST(node->right, id);

    return node;
}

bool searchBST(NodeBST* node, int id) {
    if (!node) return false;
    if (id == node->id) return true;
    if (id < node->id)
        return searchBST(node->left, id);
    else
        return searchBST(node->right, id);
}

NodeBST* findMinBST(NodeBST* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

NodeBST* deleteBST(NodeBST* node, int id) {
    if (!node) return NULL;

    if (id < node->id)
        node->left = deleteBST(node->left, id);
    else if (id > node->id)
        node->right = deleteBST(node->right, id);
    else {
        if (!node->left) {
            NodeBST* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            NodeBST* temp = node->left;
            delete node;
            return temp;
        }

        NodeBST* temp = findMinBST(node->right);
        node->id = temp->id;
        node->right = deleteBST(node->right, temp->id);
    }
    return node;
}

/* ================= MAIN ================= */
int main() {
    initBed();
    int menu, idCounter = 1;

    do {
        system("cls");
        cout << "=== SISTEM RAWAT INAP RS ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Proses Rawat Inap\n";
        cout << "3. Lihat Bed\n";
        cout << "4. Undo\n";
        cout << "5. Lihat Data Pasien\n";
        cout << "6. Riwayat\n";
        cout << "7. Cari Riwayat (BST)\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;
        system("cls");

        if (menu == 1) {
            string nama;
            cout << "Nama pasien: ";
            cin.ignore();
            getline(cin, nama);

            tambahPasien(nama, idCounter);
            antrean.enqueue(idCounter);

            cout << "Pasien ditambahkan (ID " << idCounter << ")\n";
            idCounter++;
        }

        else if (menu == 2) {
            if (antrean.kosong()) {
                cout << "Antrean kosong.\n";
            } else {
                int id = antrean.dequeue();
                Pasien* p = cariPasien(id);

                // === TAMPILAN TAMBAHAN SESUAI PERMINTAAN ===
                cout << "====================================\n";
                cout << "Pasien dengan ID " << p->id
                     << " (" << p->nama
                     << ") sedang memilih bed\n";
                cout << "====================================\n\n";

                tampilBed();

                int pilih;
                cout << "\nPilih bed: ";
                cin >> pilih;

                if (pilih < 1 || pilih > JUMLAH_BED) {
                    antrean.insertFront(id);
                }
                else if (bedPemesan[pilih - 1] == -1) {
                    bedPemesan[pilih - 1] = id;
                    p->bed = pilih;
                    p->status = "Dirawat";

                    undoStack.push(id);
                    tambahRiwayat(id);
                    rootBST = insertBST(rootBST, id);

                    cout << "Pasien berhasil dirawat.\n";
                }
                else {
                    antrean.insertFront(id);
                }
            }
        }

        else if (menu == 3) tampilBed();

        else if (menu == 4) {
            if (!undoStack.kosong()) {
                int id = undoStack.pop();
                Pasien* p = cariPasien(id);

                bedPemesan[p->bed - 1] = -1;
                p->bed = -1;
                p->status = "Menunggu";

                hapusRiwayat(id);
                rootBST = deleteBST(rootBST, id);
                antrean.insertFront(id);

                cout << "UNDO berhasil.\n";
            }
        }

        else if (menu == 5) {
            Pasien* p = head;
            while (p) {
                cout << "[" << p->id << "] "
                     << p->nama << " | Bed: "
                     << (p->bed == -1 ? 0 : p->bed)
                     << " | Status: " << p->status << endl;
                p = p->next;
            }
        }

        else if (menu == 6) tampilRiwayat();

        else if (menu == 7) {
            int cariID;
            cout << "Masukkan ID pasien yang ingin dicari: ";
            cin >> cariID;

            if (searchBST(rootBST, cariID)) {
                Pasien* p = cariPasien(cariID);
                if (p) {
                    cout << "=== DATA PASIEN DI RIWAYAT ===\n";
                    cout << "ID     : " << p->id << endl;
                    cout << "Nama   : " << p->nama << endl;
                    cout << "Bed    : ";
                    if (p->bed == -1) cout << "-\n";
                    else cout << p->bed << endl;
                    cout << "Status : " << p->status << endl;
                }
            } else {
                cout << "Pasien tidak ditemukan di riwayat.\n";
            }
        }

        system("pause");
    } while (menu != 8);

    return 0;
}

