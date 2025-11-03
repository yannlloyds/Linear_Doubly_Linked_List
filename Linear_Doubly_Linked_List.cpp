#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Mahasiswa {
    string NIM;
    string NAMA;
    float NILAI;
    Mahasiswa* LEFT;
    Mahasiswa* RIGHT;
};

Mahasiswa* FIRST = NULL;
Mahasiswa* LAST = NULL;

// Membuat simpul baru
Mahasiswa* buatSimpul(string nim, string nama, float nilai) {
    Mahasiswa* P = new Mahasiswa;
    P->NIM = nim;
    P->NAMA = nama;
    P->NILAI = nilai;
    P->LEFT = NULL;
    P->RIGHT = NULL;
    return P;
}

// Menyisipkan simpul berdasarkan nilai (ascending)
void insertData(string nim, string nama, float nilai) {
    Mahasiswa* P = buatSimpul(nim, nama, nilai);

    if (FIRST == NULL) {
        FIRST = LAST = P;
        return;
    }

    // Jika nilai lebih kecil dari FIRST
    if (nilai < FIRST->NILAI) {
        P->RIGHT = FIRST;
        FIRST->LEFT = P;
        FIRST = P;
        return;
    }

    // Jika nilai lebih besar dari LAST
    if (nilai >= LAST->NILAI) {
        LAST->RIGHT = P;
        P->LEFT = LAST;
        LAST = P;
        return;
    }

    // Sisipkan di tengah
    Mahasiswa* Q = FIRST;
    while (Q != NULL && Q->NILAI < nilai)
        Q = Q->RIGHT;

    P->RIGHT = Q;
    P->LEFT = Q->LEFT;
    Q->LEFT->RIGHT = P;
    Q->LEFT = P;
}

// Menampilkan seluruh data
void tampilkanData() {
    Mahasiswa* P = FIRST;
    cout << left << setw(15) << "NIM" << setw(20) << "NAMA" << setw(10) << "NILAI" << endl;
    cout << "---------------------------------------------" << endl;
    while (P != NULL) {
        cout << left << setw(15) << P->NIM << setw(20) << P->NAMA << setw(10) << P->NILAI << endl;
        P = P->RIGHT;
    }
}

// Menampilkan data dengan nilai = 90
void tampilkanNilai90() {
    Mahasiswa* P = FIRST;
    bool found = false;
    cout << "\nData dengan NILAI = 90:\n";
    while (P != NULL) {
        if (P->NILAI == 90) {
            cout << "NIM: " << P->NIM << ", NAMA: " << P->NAMA << ", NILAI: " << P->NILAI << endl;
            found = true;
        }
        P = P->RIGHT;
    }
    if (!found) cout << "Tidak ada data dengan nilai 90.\n";
}

// Menghapus data berdasarkan NIM
void hapusData(string nim) {
    Mahasiswa* P = FIRST;
    while (P != NULL && P->NIM != nim)
        P = P->RIGHT;

    if (P == NULL) {
        cout << "Data dengan NIM " << nim << " tidak ditemukan.\n";
        return;
    }

    if (P == FIRST && P == LAST) {
        FIRST = LAST = NULL;
    } else if (P == FIRST) {
        FIRST = P->RIGHT;
        FIRST->LEFT = NULL;
    } else if (P == LAST) {
        LAST = P->LEFT;
        LAST->RIGHT = NULL;
    } else {
        P->LEFT->RIGHT = P->RIGHT;
        P->RIGHT->LEFT = P->LEFT;
    }

    delete P;
    cout << "Data dengan NIM " << nim << " berhasil dihapus.\n";
}

// Menghitung rata-rata nilai
void hitungRataRata(string nama, string nim) {
    Mahasiswa* P = FIRST;
    float total = 0;
    int count = 0;

    while (P != NULL) {
        total += P->NILAI;
        count++;
        P = P->RIGHT;
    }

    if (count > 0) {
        float rata = total / count;
        cout << "\nNilai rata-rata kelas: " << rata << endl;
    } else {
        cout << "\nTidak ada data untuk dihitung rata-rata.\n";
    }

    cout << "\nProgram dibuat oleh:\n";
    cout << "Nama: " << nama << endl;
    cout << "NIM: " << nim << endl;
}

// Menu utama
int main() {
    string namaAnda, nimAnda;
    cout << "Masukkan Nama Anda: ";
    getline(cin, namaAnda);
    cout << "Masukkan NIM Anda: ";
    getline(cin, nimAnda);

    int pilihan;
    do {
        cout << "\n=== MENU DATA MAHASISWA ===\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Tampilkan Data dengan Nilai = 90\n";
        cout << "4. Hapus Data berdasarkan NIM\n";
        cout << "5. Hitung Rata-Rata Nilai Kelas\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); // membersihkan buffer

        if (pilihan == 1) {
            string nim, nama;
            float nilai;
            cout << "\nMasukkan NIM: ";
            getline(cin, nim);
            cout << "Masukkan Nama: ";
            getline(cin, nama);
            cout << "Masukkan Nilai: ";
            cin >> nilai;
            cin.ignore();
            insertData(nim, nama, nilai);
            cout << "Data berhasil ditambahkan!\n";
        }
        else if (pilihan == 2) {
            cout << "\n=== DATA MAHASISWA ===\n";
            tampilkanData();
        }
        else if (pilihan == 3) {
            tampilkanNilai90();
        }
        else if (pilihan == 4) {
            string nim;
            cout << "Masukkan NIM yang ingin dihapus: ";
            getline(cin, nim);
            hapusData(nim);
        }
        else if (pilihan == 5) {
            hitungRataRata(namaAnda, nimAnda);
        }
        else if (pilihan == 0) {
            cout << "Program selesai.\n";
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}