#include <iostream>
#include <string>

using namespace std;

struct Buku {
    string judul;
    string pengarang;
    int tahunTerbit;
    bool tersedia;
};

const int MAX_BUKU = 5;

Buku daftarBuku[MAX_BUKU]; 
int jmlhBuku = 0;

void tambahBuku() {
    if (jmlhBuku < MAX_BUKU) {
        cout << "\nMasukkan Judul Buku: ";
        getline(cin, daftarBuku[jmlhBuku].judul);
        cout << "Masukkan Pengarang: ";
        getline(cin, daftarBuku[jmlhBuku].pengarang);
        cout << "Masukkan Tahun Terbit: ";
        cin >> daftarBuku[jmlhBuku].tahunTerbit;
        cin.ignore();
        daftarBuku[jmlhBuku].tersedia = true;
        jmlhBuku++;
        cout << "Buku berhasil ditambahkan!\n";
    } else {
        cout << "Kapasitas buku penuh!\n";
    }
}

void tampilkanBuku() {
    cout << "\n=== Daftar Buku ===\n";
    for (int i = 0; i < jmlhBuku; i++) {
        cout << i + 1 << ". " << daftarBuku[i].judul << " - " << daftarBuku[i].pengarang
             << " (" << daftarBuku[i].tahunTerbit << ") - "
             << (daftarBuku[i].tersedia ? "Tersedia" : "Dipinjam") << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== MENU PERPUSTAKAAN ===\n";
        cout << "1. Tambah Buku\n2. Tampilkan Buku\n3. Keluar\nPilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 3: cout << "Terima kasih telah menggunakan sistem perpustakaan!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);

    return 0;
}
