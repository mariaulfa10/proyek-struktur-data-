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

/* ================= QUEUE (ARRAY) ================= */
struct Queue {
    int data[100];
    int front, rear;

    Queue() {
        front = 0;
        rear = -1;
    }

    bool kosong() {
        return front > rear;
    }

    void enqueue(int x) {
        data[++rear] = x;
    }

    int dequeue() {
        return data[front++];
    }

    void insertFront(int x) { // penting untuk UNDO
        for (int i = rear + 1; i > front; i--)
            data[i] = data[i - 1];
        data[front] = x;
        rear++;
    }
} antrean;

/* ================= STACK UNDO (ARRAY) ================= */
struct Stack {
    int data[100];
    int top;

    Stack() { top = -1; }

    void push(int id) {
        data[++top] = id;
    }

    int pop() {
        return data[top--];
    }

    bool kosong() {
        return top == -1;
    }
} undoStack;

/* ================= TREE (BST) RIWAYAT ================= */
struct Node {
    int id;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* insertTree(Node* node, int id) {
    if (!node)
        return new Node{id, NULL, NULL};

    if (id < node->id)
        node->left = insertTree(node->left, id);
    else
        node->right = insertTree(node->right, id);

    return node;
}

void tampilTree(Node* node) {
    if (!node) return;
    tampilTree(node->left);
    cout << "Pasien ID " << node->id << " pernah dirawat\n";
    tampilTree(node->right);
}

/* ================= MAIN ================= */
int main() {
    initBed();
    int menu, idCounter = 1;

    do {
        system("cls");
        cout << "=== SISTEM RUMAH SAKIT ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Proses Rawat Inap\n";
        cout << "3. Lihat Bed\n";
        cout << "4. Undo\n";
        cout << "5. Lihat Data Pasien\n";
        cout << "6. Riwayat (Tree)\n";
        cout << "7. Keluar\n";
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

            cout << "Pasien ditambahkan (ID "
                 << idCounter << ")\n";
            idCounter++;
        }

        else if (menu == 2) {
            if (antrean.kosong()) {
                cout << "Antrean kosong.\n";
            } else {
                int id = antrean.dequeue();
                Pasien* p = cariPasien(id);

                cout << "Pasien dengan ID "
                     << p->id << " ("
                     << p->nama
                     << ") sedang memilih bed\n\n";

                tampilBed();

                int pilih;
                cout << "\nPilih bed: ";
                cin >> pilih;

                if (pilih < 1 || pilih > JUMLAH_BED) {
                    cout << "Bed tidak valid.\n";
                    antrean.insertFront(id);
                }
                else if (bedPemesan[pilih - 1] == -1) {
                    bedPemesan[pilih - 1] = id;
                    p->bed = pilih;
                    p->status = "Dirawat";

                    undoStack.push(id);
                    root = insertTree(root, id);

                    cout << "Pasien berhasil dirawat.\n";
                }
                else {
                    cout << "Bed sudah terisi.\n";
                    antrean.insertFront(id);
                }
            }
        }

        else if (menu == 3) {
            tampilBed();
        }

        else if (menu == 4) {
            if (undoStack.kosong()) {
                cout << "Tidak ada aksi undo.\n";
            } else {
                int id = undoStack.pop();
                Pasien* p = cariPasien(id);

                if (p->bed != -1)
                    bedPemesan[p->bed - 1] = -1;

                p->bed = -1;
                p->status = "Menunggu";

                antrean.insertFront(id);

                cout << "UNDO berhasil. Pasien dengan ID "
                     << id << " kembali ke antrean.\n";
            }
        }

        else if (menu == 5) {
            Pasien* p = head;
            while (p) {
                cout << "[" << p->id << "] "
                     << p->nama << " | Bed: ";

                if (p->bed == -1)
                    cout << "Belum ada";
                else
                    cout << p->bed;

                cout << " | Status: "
                     << p->status << endl;

                p = p->next;
            }
        }

        else if (menu == 6) {
            if (!root)
                cout << "Belum ada riwayat.\n";
            else
                tampilTree(root);
        }

        system("pause");
    } while (menu != 7);

    return 0;
}

