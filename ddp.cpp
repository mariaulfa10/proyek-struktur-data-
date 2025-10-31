#include <string>
#include <iostream>
#include <limits>
#include <iomanip>
#include <ctime>

using namespace std;

//  ! FAUZAN 
int pasien = 0;
int noantrian = 0;
int LoketA = 0, LoketB = 0, LoketC = 0, LoketD = 0;

struct BiodataPasien {
    int noantrian;
    string nama;
    string alamat;
    string telp;
    string umur;
    string jamdaftar;
    string pelayanan;
};

struct BiodataPasien arrpasien[200];

// ! ULFA

string waktudaftar() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void TekanEnter(){
    cout << "Tekan Enter Untuk Melanjutkan...";
    cin.ignore();
    cin.get();
}

//! HIYAR

void printStrukAntrian() {
    cout << "\n===================================================" << endl;
    cout << "=                 Struk Antrian                   =    " << endl;
    cout << "=         Rumah Sakit Cinta Kasih UAD             =    " << endl;
    cout << "===================================================" << endl;
    cout << "= Nomor Antrian       : " << setw(25) << arrpasien[pasien - 1].noantrian << " =" << endl;
    cout << "= Nama Pasien         : " << setw(25) << arrpasien[pasien - 1].nama << " =" << endl;
    cout << "= Umur                : " << setw(25) << arrpasien[pasien - 1].umur << " =" << endl;
    cout << "= Domisili            : " << setw(25) << arrpasien[pasien - 1].alamat << " =" << endl;
    cout << "= No Telepon          : " << setw(25) << arrpasien[pasien - 1].telp << " =" << endl;
    cout << "= Jenis Pelayanan     : " << setw(25) << arrpasien[pasien - 1].pelayanan << " =" << endl;
    cout << "= Tanggal dan Waktu   : " << setw(25) << arrpasien[pasien - 1].jamdaftar << " =" << endl;
    cout << "===================================================\n";
}

string pilihPelayanan(int pilihan) {

    switch (pilihan) {
        case 1: return "Pelayanan Rawat Inap";
        case 2: return "Pelayanan Rawat Jalan";
        case 3: return "Pelayanan Gawat Darurat";
        case 4: return "Pelayanan Radiologi";
        case 5: return "Pelayanan Bedah";
        case 6: return "Pelayanan Rehabilitasi";
        case 7: return "Pelayanan Kebidanan";
        case 8: return "Pelayanan peditri (umum)";
        case 9: return "Pelayanan Psikiatri";
        default: return "Pelayanan Tidak Valid";
    }
}

// ! FAUZAN
void inputpasien(){

    cout << "Masukan Nama Pasien : ";
    cin.ignore();
    getline(cin, arrpasien[pasien].nama);

    cout << "Masukan Umur Pasien : ";
    cin >> arrpasien[pasien].umur;

    cout << "Masukan Alamat Pasien : ";
    cin.ignore();
    getline(cin, arrpasien[pasien].alamat);

    cout << "Masukan No Telepon Pasien : ";
    cin >> arrpasien[pasien].telp;

    cout << "Pilih Jenis Pelayanan:" << endl;
    cout << "1. Pelayanan Rawat Inap\n2. Pelayanan Rawat Jalan\n3. Pelayanan Gawat Darurat\n4. Pelayanan Radiologi\n5. Pelayanan Bedah\n6. Pelayanan Rehabilitasi\n7. Pelayanan Kebidanan\n8. Pelayanan Pediatri (Umum)\n9. Pelayanan Psikiatri\n";
    cout << "Masukan Pilihan (1-9): ";
    
    int pilihanPelayanan;
    
    cin >> pilihanPelayanan;
    arrpasien[pasien].pelayanan = pilihPelayanan(pilihanPelayanan);

    arrpasien[pasien].noantrian = noantrian + 1;
    arrpasien[pasien].jamdaftar = waktudaftar();

    noantrian++;
    pasien++;

    cout << endl;

    printStrukAntrian();
    TekanEnter();
}

void displayDashboard() {
    cout << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ " << endl;

    cout << left << setw(15) << "|      Loket - A    | "
         << left << setw(15) << "|      Loket - B    | "
         << left << setw(15) << "|      Loket - C    | "
         << left << setw(15) << "|      Loket - D    | " << endl;

    cout << left << setw(16) << "|    NO.PAS - " << LoketA << "   | "
         << left << setw(16) << "|    NO.PAS - " << LoketB << "   | "
         << left << setw(16) << "|    NO.PAS - " << LoketC << "   | "
         << left << setw(16) << "|    NO.PAS - " << LoketD << "   | " << endl;

    cout << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ "
         << left << setw(15) << "+-------------------+ " << endl << endl;
}

// ! ULFA
void tampilkandataPasien(){
    if (pasien < 1){
        cout << " ========== DATA PASIEN RUMAH SAKIT CINTA KASIH ==========" << endl;
        cout << "!! DATA PASIEN RUMAH SAKIT CINTA KASIH MASIH KOSONG !!" << endl;
    } else {
        cout << "\n\t\t\t\t========== DATA PASIEN RUMAH SAKIT CINTA KASIH ==========" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(5) << "| No" 
        << left << setw(22) << "| Nama" 
        << left << setw(7) << "| Umur" 
        << left << setw(16) << "| Domisili"  
        << left << setw(17) << "| No.Telpon" 
        << left << setw(29) << "| Jenis Pelayanan" 
        << left << setw(10) << "| Waktu Pendaftaran    |" << endl;
        cout << "|----|---------------------|------|---------------|----------------|----------------------------|----------------------|" << endl;

        for (int i = 0; i < pasien; i++) {
            cout << "| " << left << setw(3) << arrpasien[i].noantrian
                << "| " << left << setw(20) << arrpasien[i].nama 
                << "| " << left << setw(5) << arrpasien[i].umur
                << "| " << left << setw(14) << arrpasien[i].alamat
                << "| " << left << setw(15) << arrpasien[i].telp 
                << "| " << left << setw(27) << arrpasien[i].pelayanan
                << "| " << left << setw(21) << arrpasien[i].jamdaftar
                << "|" << endl;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

// ! HIYAR
void PanggilPasien() {
    char pilih;
    int noantrianInput;

    if (pasien < 1) {
        cout << "!! DATA PASIEN RUMAH SAKIT CINTA KASIH MASIH KOSONG !!" << endl;
        TekanEnter();
        return;
    } else {
        cout << "=== Memanggil Pasien Dari Loket ===" << endl;
        cout << "Masukan Nomor Pasien Terdaftar (1-" << pasien << "): ";
        cin >> noantrianInput;

        if (noantrianInput < 1 || noantrianInput > pasien) {
            cout << "Nomor pasien tidak valid." << endl;
            TekanEnter();
            return;
        }

        int index = noantrianInput - 1;

        cout << "\nDetail Pasien:" << endl;
        cout << "No Antrian: " << arrpasien[index].noantrian << endl;
        cout << "Nama: " << arrpasien[index].nama << endl;
        cout << "Umur: " << arrpasien[index].umur << endl;
        cout << "Alamat: " << arrpasien[index].alamat << endl;
        cout << "No Telepon: " << arrpasien[index].telp << endl;
        cout << "Jenis Pelayanan: " << arrpasien[index].pelayanan << endl;

        cout << "Masukan Loket (A/B/C/D) : ";
        cin >> pilih;

        if (pilih == 'A' || pilih == 'a') {
            LoketA = arrpasien[index].noantrian;
        } else if (pilih == 'B' || pilih == 'b') {
            LoketB = arrpasien[index].noantrian;
        } else if (pilih == 'C' || pilih == 'c') {
            LoketC = arrpasien[index].noantrian;
        } else if (pilih == 'D' || pilih == 'd') {
            LoketD = arrpasien[index].noantrian;
        } else {
            cout << "Loket Tidak Tersedia" << endl;
            TekanEnter();
            return;
        }

        cout << "Pasien " << arrpasien[index].nama << " berhasil ditambahkan ke Loket " << pilih << " :)" << endl;
        TekanEnter();
    }
}



int main(){

    int pilih;

    do {
        system("cls");

        cout << "=====================================================================" << endl;
        cout << "\t\tProgram Antrean Rumah Sakit Cinta Kasih" << endl;
        cout << "\t\t\tUniversitas Ahmad Dahlan" << endl;
        cout << "=====================================================================" << endl << endl;
        cout << "Nomor Antrian Saat Ini    : " << noantrian << endl;
        cout << "Nomor Antrian Selanjutnya : " << noantrian + 1 << endl;
        cout << "Jumlah Pasien Terdaftar   : " << pasien << endl << endl;

        displayDashboard();

        cout << " --- Dashboard Admin ---" << endl;
        cout << "1. Menambahkan Data Pasien" << endl;
        cout << "2. Memanggil Pasien" << endl;
        cout << "3. Melihat Daftar Pasien" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukkan pilihan (1-4): ";
        cin >> pilih;

        switch(pilih){
            case 1:
                inputpasien();
                break;
            case 2:
                tampilkandataPasien();
                PanggilPasien();
                break;
            case 3:
                tampilkandataPasien();
                TekanEnter();
                break;
            case 4:
                cout << "Terimakasih Telah Menggunakan Program" << endl;
                cout << "Selamat Beristirahat" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilih != 4);

    return 0;
}
