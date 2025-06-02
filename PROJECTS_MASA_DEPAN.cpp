#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void simpanKeFile();
// Struktur data untuk menyimpan data buku
struct Buku {
    string kode;
    string judul;
    string pengarang;
    int tahunTerbit;
    bool tersedia;
    string peminjam;
};

int pilih;
string back;
bool ascending, invalid;
bool kode = false;
bool judul = false;
bool tahun = false;
bool bubblesort = false;
bool shelsort = false;
const int MAX_BUKU = 100; // Jumlah maksimum buku
Buku daftarBuku[MAX_BUKU]; 
int jmlhBuku = 0;

// Fungsi untuk menambahkan buku
void tambahBuku() {
    int jumlah;
    
    cout << "=============================================\n";
    cout << "Masukan Jumlah Buku yang ingin dimasukan : ";
    cin >> jumlah;
    cin.ignore();
    
    for(int i = 0; i < jumlah; i++) {
        cout << "\n==========";
        cout << "\nBuku ke-" << i + 1;
        cout << "\n==========\n";
        cout << "Masukkan Kode Buku    : "; getline(cin, daftarBuku[jmlhBuku].kode);
        cout << "Masukkan Judul Buku   : "; getline(cin, daftarBuku[jmlhBuku].judul);
        cout << "Masukkan Pengarang    : "; getline(cin, daftarBuku[jmlhBuku].pengarang);
        cout << "Masukkan Tahun Terbit : "; cin >> daftarBuku[jmlhBuku].tahunTerbit;

        cin.ignore();
        daftarBuku[jmlhBuku].tersedia = true;
        daftarBuku[jmlhBuku].peminjam = "-";
        jmlhBuku++;
    }
    cout << "\n==========================\n";
    cout << "Buku berhasil ditambahkan!\n";
    cout << "==========================\n\n";

    simpanKeFile();
}

void simpanKeFile() {
    ofstream file("data_buku.txt");

    if (file.is_open()) {
        // Header
        file << left << setw(10) << "Kode"
             << setw(30) << "Judul"
             << setw(25) << "Pengarang"
             << setw(15) << "Tahun"
             << setw(12) << "Tersedia"
             << setw(20) << "Peminjam" << endl;
        file << string(112, '=') << endl;

        // Isi data buku
        for (int i = 0; i < jmlhBuku; i++) {
            file << left << setw(10) << daftarBuku[i].kode
                 << setw(30) << daftarBuku[i].judul
                 << setw(25) << daftarBuku[i].pengarang
                 << setw(15) << daftarBuku[i].tahunTerbit
                 << setw(12) << (daftarBuku[i].tersedia ? "Ya" : "Tidak")
                 << setw(20) << daftarBuku[i].peminjam << endl;
        }

        file.close();
        cout << "Data berhasil disimpan ke file dalam format tabel.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
}

// Baca file
void bacaDariFile() {
    ifstream file("data_buku.txt");
    if (file.is_open()) {
        file >> jmlhBuku;
        file.ignore();
        for (int i = 0; i < jmlhBuku; i++) {
            getline(file, daftarBuku[i].kode);
            getline(file, daftarBuku[i].judul);
            getline(file, daftarBuku[i].pengarang);
            file >> daftarBuku[i].tahunTerbit;
            file >> daftarBuku[i].tersedia;
            file.ignore();
            getline(file, daftarBuku[i].peminjam);
        }
        file.close();
        cout << "Data berhasil dibaca dari file.\n";
    } else {
        cout << "File tidak ditemukan. Memulai dengan data kosong.\n";
    }
}

// Fungsi untuk menampilkan daftar buku
void tampilkanBuku() {

    if (jmlhBuku == 0) {
        cout << "\nTidak ada data buku.\n\n";
        return;
    }

    // Header tabel
    cout << "\n===================================  Daftar Buku Perpustakaan  ===================================\n";
    cout << left
         << setw(5) << "No" // Kolom No
         << setw(15) << "Kode Buku" // Kolom Kode Buku
         << setw(20) << "Judul Buku" // Kolom Judul Buku
         << setw(20) << "Pengarang" // Kolom Pengarang
         << setw(15) << "Tahun Terbit" // Kolom Tahun Terbit
         << setw(15) << "Status" // Kolom Status
         << endl;

    cout << "--------------------------------------------------------------------------------------------------\n";

    // Menampilkan data buku
    for (int i = 0; i < jmlhBuku; i++) {
        cout << setw(5) << i + 1  // Nomor urut
             << setw(15) << daftarBuku[i].kode // Kode Buku
             << setw(20) << daftarBuku[i].judul // Judul Buku
             << setw(20) << daftarBuku[i].pengarang // Pengarang
             << setw(15) << daftarBuku[i].tahunTerbit // Tahun Terbit
             << setw(15) << (daftarBuku[i].tersedia ? "Tersedia" : "Dipinjam oleh " + daftarBuku[i].peminjam) // Status
             << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------\n\n ";
}

// Fungsi untuk meminjam buku
void pinjamBuku() {
    tampilkanBuku();
    string kodeCari;
    string namaPeminjam;
    bool ditemukan = false;

    cout << "======================================================\n";
    cout << "Masukkan nama peminjam : ";
    getline(cin, namaPeminjam);
    cout << "Masukkan kode buku yang ingin dipinjam : ";
    getline(cin, kodeCari);

    for (int i = 0; i < jmlhBuku; i++) {
        if (daftarBuku[i].kode == kodeCari) {
            ditemukan = true;
            if (daftarBuku[i].tersedia) {
                daftarBuku[i].peminjam = namaPeminjam;
                daftarBuku[i].tersedia = false;
                cout << "Buku dengan judul \"" << daftarBuku[i].judul << "\" berhasil dipinjam oleh " << namaPeminjam << "!\n";
                cout << "======================================================\n\n";
            } else {
                cout << "Maaf, buku sedang dipinjam oleh " << daftarBuku[i].peminjam << "!\n\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "Buku dengan kode \"" << kodeCari << "\" tidak ditemukan.\n\n";
    }

    simpanKeFile();
}

// Update buku dari file
void updateBuku() {
    string input;
    bool ditemukan = false;

    cout << "\n========== Update Buku ==========\n";
    cout << "1. Update berdasarkan Kode Buku\n";
    cout << "2. Update berdasarkan Judul Buku\n";
    cout << "Pilih: ";
    cin >> pilih;
    cin.ignore();

    if (pilih == 1) {
        cout << "Masukkan kode buku yang ingin diperbarui: ";
        getline(cin, input);
        for (int i = 0; i < jmlhBuku; i++) {
            if (daftarBuku[i].kode == input) {
                ditemukan = true;
                cout << "Masukkan data baru untuk buku:\n";
                cout << "Judul Buku Baru    : "; getline(cin, daftarBuku[i].judul);
                cout << "Pengarang Baru     : "; getline(cin, daftarBuku[i].pengarang);
                cout << "Tahun Terbit Baru  : "; cin >> daftarBuku[i].tahunTerbit;
                cin.ignore();
                cout << "Data buku berhasil diperbarui!\n";
                break;
            }
        }
    } else if (pilih == 2) {
        cout << "Masukkan judul buku yang ingin diperbarui: ";
        getline(cin, input);
        for (int i = 0; i < jmlhBuku; i++) {
            if (daftarBuku[i].judul == input) {
                ditemukan = true;
                cout << "Masukkan data baru untuk buku:\n";
                cout << "Kode Buku Baru     : "; getline(cin, daftarBuku[i].kode);
                cout << "Pengarang Baru     : "; getline(cin, daftarBuku[i].pengarang);
                cout << "Tahun Terbit Baru  : "; cin >> daftarBuku[i].tahunTerbit;
                cin.ignore();
                cout << "Data buku berhasil diperbarui!\n";
                break;
            }
        }
    } else {
        cout << " Pilihan tidak valid!\n";
        return;
    } 
    if (!ditemukan) {
        cout << "Buku tidak ditemukan!\n";
    } else {
        simpanKeFile(); // Simpan hasil update ke file
    }
}

// Fungsi untuk mengembalikan buku
void kembalikanBuku() {

    if (jmlhBuku == 0) {
        cout << "\nTidak ada data buku.\n";
        return;
    }

    string kode;
    bool ditemukan = false;

    cout << "\nMasukkan kode buku yang ingin dikembalikan: ";
    // cin.ignore();
    getline(cin, kode);

    for (int i = 0; i < jmlhBuku; i++) {
        if (daftarBuku[i].kode == kode) {
            ditemukan = true;
            if (!daftarBuku[i].tersedia) {
                daftarBuku[i].tersedia = true;
                daftarBuku[i].peminjam = "-";
                cout << "Buku berhasil dikembalikan!\n";
            } else {
                cout << "Buku ini belum dipinjam.\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "Buku dengan kode \"" << kode << "\" tidak ditemukan.\n";
    }

    simpanKeFile(); // Update file setelah pengembalian
}

// bubble sort berdasarkan Judul
void bubbleSortJudul(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    int i, j;
    string temp;

    for (int i = 0; i < jmlhBuku - 1; i++) {
        for (int j = 0; j < jmlhBuku - i - 1; j++) {
            if ((ascending && daftarBuku[j].judul > daftarBuku[j + 1].judul ) || 
                (!ascending && daftarBuku[j].judul < daftarBuku[j + 1].judul)) {
                swap(daftarBuku[j], daftarBuku[j + 1]);
                }
        }
    }
    cout << "Daftar buku berhasil diurutkan berdasarkan judul!\n";
}

// bubble sort berdasarkan tahun
void bubbleSortTahun(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    if(ascending) {
        for (int i = 0; i < jmlhBuku - 1; i++) {
            for (int j = 0; j < jmlhBuku - i - 1; j++) {
                if (daftarBuku[j].tahunTerbit > daftarBuku[j + 1].tahunTerbit) {
                    swap(daftarBuku[j], daftarBuku[j + 1]);
                }
            }
        }
    } else {
        for (int i = 0; i < jmlhBuku - 1; i++) {
            for (int j = 0; j < jmlhBuku - i - 1; j++) {
                if (daftarBuku[j].tahunTerbit < daftarBuku[j + 1].tahunTerbit) {
                    swap(daftarBuku[j], daftarBuku[j + 1]);
                }
            }
        }
    }
    cout << "Daftar buku berhasil diurutkan berdasarkan tahun terbit!\n";
}

// bubble sort berdasarkan kode
void bubbleSortKode(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    for (int i = 0; i < jmlhBuku - 1; i++) {
        for (int j = 0; j < jmlhBuku - i - 1; j++) {
            if ((ascending && daftarBuku[j].kode > daftarBuku[j + 1].kode) ||
                (!ascending && daftarBuku[j].kode < daftarBuku[j + 1].kode)) {
                swap(daftarBuku[j], daftarBuku[j + 1]);
            }
        }
    }
    cout << "Daftar buku berhasil diurutkan berdasarkan Kode!\n";
}

// Shell sort berdasarkan judul
void shellSortJudul(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    for (int gap = jmlhBuku / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jmlhBuku; i++) {
            Buku temp = daftarBuku[i];
            int j;
            for (j = i; j >= gap && ((ascending && daftarBuku[j - gap].judul > temp.judul) ||
                                     (!ascending && daftarBuku[j - gap].judul < temp.judul)); j -= gap) {
                daftarBuku[j] = daftarBuku[j - gap];
            }
            daftarBuku[j] = temp;
        }
    }
}

// Shell sort berdasarkan kode
void shellSortKode(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    for (int gap = jmlhBuku / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jmlhBuku; i++) {
            Buku temp = daftarBuku[i];
            int j;
            for (j = i; j >= gap && ((ascending && daftarBuku[j - gap].kode > temp.kode) ||
                                     (!ascending && daftarBuku[j - gap].kode < temp.kode)); j -= gap) {
                daftarBuku[j] = daftarBuku[j - gap];
            }
            daftarBuku[j] = temp;
        }
    }
    cout << "Daftar buku berhasil diurutkan berdasarkan Kode!\n";
}

// Shell sort berdasarkan tahun
void shellSortTahun(Buku daftarBuku[], int jmlhBuku, bool ascending) {
    for (int gap = jmlhBuku / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jmlhBuku; i++) {
            Buku temp = daftarBuku[i];
            int j;
            for (j = i; j >= gap && ((ascending && daftarBuku[j - gap].tahunTerbit > temp.tahunTerbit) ||
                                     (!ascending && daftarBuku[j - gap].tahunTerbit < temp.tahunTerbit)); j -= gap) {
                daftarBuku[j] = daftarBuku[j - gap];
            }
            daftarBuku[j] = temp;
        }
    }
    cout << "Daftar buku berhasil diurutkan berdasarkan Tahun Terbit!\n";
}

// Pilihan metode sorting
void pilMetode() {
    cout << "Pilih metode sorting yang ingin digunakan:\n";
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    cout << "Masukan metode yang dipilih: ";
    cin >> pilih;

    ascending = (pilih == 1);

    if (bubblesort) {
        if (judul) bubbleSortJudul(daftarBuku, jmlhBuku, ascending);
        else if (tahun) bubbleSortTahun(daftarBuku, jmlhBuku, ascending);
        else if (kode) bubbleSortKode(daftarBuku, jmlhBuku, ascending);
    } else if (shelsort) {
        if (judul) shellSortJudul(daftarBuku, jmlhBuku, ascending);
        else if (tahun) shellSortTahun(daftarBuku, jmlhBuku, ascending);
        else if (kode) shellSortKode(daftarBuku, jmlhBuku, ascending);
    }

    tampilkanBuku();

    // Reset flags
    bubblesort = shelsort = kode = judul = tahun = invalid = false;
}

// Fungsi jika memilih sorting dari judul
void pilUrut( ) {
    
    do {
        cout << "=========== MENU URUTKAN BUKU ===========\n";
        cout << "1. Bubble sort\n";
        cout << "2. Shell sort\n";
        cout << "Silahkan pilih kriteria sorting: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
            bubblesort = true;
            pilMetode();
            break;
            case 2:
            shelsort = true;
            pilMetode();
            break;
            default:
            cout << "Pilihan tidak valid\n\n";
            invalid = true;
            break;
        }
    }while(invalid);
}

// Fungsi untuk memilih jenis pengurutan
void urutkanBuku() {
    do {
        cout << "\n=========== MENU URUTKAN BUKU ===========\n";
        cout << "Silakan pilih kriteria pengurutan:\n";
        cout << "1. Berdasarkan Kode Buku\n";
        cout << "2. Berdasarkan Judul\n";
        cout << "3. Berdasarkan Tahun Terbit\n";
        cout << "==========================================\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                kode = true;
                pilUrut();
                break;
            case 2:
                judul = true;
                pilUrut();
                break;
            case 3:
                tahun = true;
                pilUrut();
                break;
            default:
                invalid = true;
                cout << "Pilihan tidak valid!\n";
                system("pause");
        }   
    }while(invalid);
}

// Searching buku menggunakan binary
void binarySearch(int pil) {
    string kataKunci;
    int tahunKunci;
    int kiri = 0, kanan = jmlhBuku - 1, tengah;
    bool ditemukan = false;

    if (pil == 1) {
        cout << "Masukkan kode buku: ";
        getline(cin, kataKunci);
        bubbleSortKode(daftarBuku, jmlhBuku, true);
    } else if (pil == 2) {
        cout << "Masukkan judul buku: ";
        getline(cin, kataKunci);
        bubbleSortJudul(daftarBuku, jmlhBuku, true);
    } else if (pil == 3) {
        cout << "Masukkan tahun terbit: ";
        cin >> tahunKunci;
        bubbleSortTahun(daftarBuku, jmlhBuku, true);
    }

    // Binary Search untuk menemukan satu
    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;
        if ((pil == 1 && daftarBuku[tengah].kode == kataKunci) ||
            (pil == 2 && daftarBuku[tengah].judul == kataKunci) ||
            (pil == 3 && daftarBuku[tengah].tahunTerbit == tahunKunci)) {
            ditemukan = true;
            break;
        }

        if (pil == 1) {
            if (daftarBuku[tengah].kode < kataKunci)
                kiri = tengah + 1;
            else
                kanan = tengah - 1;
        } else if (pil == 2) {
            if (daftarBuku[tengah].judul < kataKunci)
                kiri = tengah + 1;
            else
                kanan = tengah - 1;
        } else if (pil == 3) {
            if (daftarBuku[tengah].tahunTerbit < tahunKunci)
                kiri = tengah + 1;
            else
                kanan = tengah - 1;
        }
    }

    if (!ditemukan) {
        cout << "\nData tidak ditemukan.\n";
        return;
    }

    // Tampilkan semua yang cocok (cek kiri dan kanan)
    cout << "\nHasil pencarian:\n";
    int k = tengah;

    // Cek ke kiri
    while (k >= 0) {
        if ((pil == 1 && daftarBuku[k].kode != kataKunci) ||
            (pil == 2 && daftarBuku[k].judul != kataKunci) ||
            (pil == 3 && daftarBuku[k].tahunTerbit != tahunKunci)) {
            break;
        }
        k--;
    }
    k++; // geser balik ke indeks pertama yang cocok

    // Cetak semua dari kiri ke kanan selama masih cocok
    while (k < jmlhBuku) {
        if ((pil == 1 && daftarBuku[k].kode == kataKunci) ||
            (pil == 2 && daftarBuku[k].judul == kataKunci) ||
            (pil == 3 && daftarBuku[k].tahunTerbit == tahunKunci)) {
            cout << "---------------------------------\n";
            cout << "Kode     : " << daftarBuku[k].kode << "\n";
            cout << "Judul    : " << daftarBuku[k].judul << "\n";
            cout << "Pengarang: " << daftarBuku[k].pengarang << "\n";
            cout << "Tahun    : " << daftarBuku[k].tahunTerbit << "\n";
        } else {
            break;
        }
        k++;
    }
}

// Searching buku menggunakan sequential
void sequentialSearch(int pil) {
    string search;
    int searchTahun;
    bool ditemukan = false;

    if (pil == 1) {
        cout << "Masukkan kode buku: ";
        getline(cin, search);
    } else if (pil == 2) {
        cout << "Masukkan judul buku: ";
        getline(cin, search);
    } else if (pil == 3) {
        cout << "Masukkan tahun terbit: ";
        cin >> searchTahun;
    }

    cout << "\nHasil pencarian:\n";
    for (int i = 0; i < jmlhBuku; i++) {
        if ((pil == 1 && daftarBuku[i].kode == search) ||
            (pil == 2 && daftarBuku[i].judul == search) ||
            (pil == 3 && daftarBuku[i].tahunTerbit == searchTahun)) {
            ditemukan = true;
            cout << "---------------------------------\n";
            cout << "Kode     : " << daftarBuku[i].kode << "\n";
            cout << "Judul    : " << daftarBuku[i].judul << "\n";
            cout << "Pengarang: " << daftarBuku[i].pengarang << "\n";
            cout << "Tahun    : " << daftarBuku[i].tahunTerbit << "\n";
        }
    }

    if (!ditemukan)
        cout << "Data tidak ditemukan.\n";
}

// Mencari buku
void searchBuku() {
    int pil, metode;

    cout << "\n========= MENU SEARCHING =========\n";
    cout << "1. Kode Buku\n";
    cout << "2. Judul Buku\n";
    cout << "3. Tahun Terbit\n";
    cout << "Pilih menu searching: ";
    cin >> pil;
    cout << "======== METODE SEARCHING ========";
    cout << "\nPilih metode pencarian:\n";
    cout << "1. Sequential Search\n";
    cout << "2. Binary Search\n";
    cout << "Pilihan metode: ";
    cin >> metode;
    cin.ignore();

    if (metode == 1)
        sequentialSearch(pil);
    else if (metode == 2)
        binarySearch(pil);
    else
        cout << "Metode tidak valid!\n";
}

// Menghapus buku
void hapusBuku() {
    string input;
    bool ditemukan = false;

    cout << "\n========== Hapus Buku ==========\n";
    cout << "1. Hapus Buku Berdasarkan Kode\n";
    cout << "2. Hapus Buku Berdasarkan Judul\n";
    cout << "Pilih: ";
    cin >> pilih;
    cin.ignore();  // untuk membersihkan newline setelah input angka

    if (pilih == 1) {
        cout << "Masukkan kode buku yang ingin dihapus: ";
        getline(cin, input);

        // Mencari dan menghapus buku berdasarkan kode
        for (int i = 0; i < jmlhBuku; i++) {
            if (daftarBuku[i].kode == input) {
                // Menggeser buku setelah buku yang dihapus
                for (int j = i; j < jmlhBuku - 1; j++) {
                    daftarBuku[j] = daftarBuku[j + 1];
                }
                jmlhBuku--;  // Mengurangi jumlah buku
                ditemukan = true;
                cout << "Buku dengan kode " << input << " berhasil dihapus!\n";
                break;
            }
        }
    } else if (pilih == 2) {
        cout << "Masukkan judul buku yang ingin dihapus: ";
        getline(cin, input);

        // Mencari dan menghapus buku berdasarkan judul
        for (int i = 0; i < jmlhBuku; i++) {
            if (daftarBuku[i].judul == input) {
                // Menggeser buku setelah buku yang dihapus
                for (int j = i; j < jmlhBuku - 1; j++) {
                    daftarBuku[j] = daftarBuku[j + 1];
                }
                jmlhBuku--;  // Mengurangi jumlah buku
                ditemukan = true;
                cout << "Buku dengan judul \"" << input << "\" berhasil dihapus!\n";
                break;
            }
        }
    } else {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    if (!ditemukan) {
        cout << "Buku tidak ditemukan!\n";
    }

    simpanKeFile(); // Update file setelah pengembalian
}

// Menu utama
int main() {
    int number, pilihan;

    string nama, pass;
    int chance = 3;
    bool login = false;

    do {
        system("cls");
        cout << left
             << "=======================\n"
             << "        WELCOME\n"
             << "  PERPUSTAKAAN NEGARA\n"
             << "    PLEASE LOGIN!!\n"
             << "=======================\n";
        cout << "Username : "; cin >> nama;
        cout << "Password : "; cin >> pass;

        // Pengecekan login yang benar
        if ((nama == "adil" && pass == "221") || (nama == "liu" && pass == "223")) {
            system("cls");
            // cout << "===============\n Welcome!\n " << nama << " || " << pass << "\n===============\n";
            login = true;
            break; // Jika berhasil login, keluar dari loop
        }
        // Pengecekan jika username dan password keduanya salah
        else if ((nama != "adil" && nama != "liu") && (pass != "221" && pass != "223")) {
            cout << "Username dan password yang anda masukan salah!!\n";
            chance--;
        }
        // Pengecekan jika hanya password yang salah
        else if (nama == "adil" && pass != "221" || nama == "liu" && pass != "223") {
            cout << "password yang anda masukan salah!!\n";
            chance--;
        }
        // Pengecekan jika hanya username yang salah
        else if (nama != "adil" && nama != "liu") {
            cout << "Username yang anda masukan salah!!\n";
            chance--;
        }

        // Menampilkan kesempatan yang tersisa setelah pengurangan
        if (chance > 0) {
            cout << "Kamu punya " << chance << " kali kesempatan untuk login ulang\n\n";
        } else {
            cout << "Login gagal, kamu tidak punya kesempatan lagi untuk login\n\n";
            break; // Jika kesempatan habis, keluar dari loop
        }
        system("pause");
    } while (chance > 0);

    // Jika login tidak berhasil
    if (!login) {
        return 0;
    }

    do {
        cout << "===================================\n";
        cout << "~ PERPUSTAKAAN KERAHASIAAN NEGARA ~\n";
        cout << "===================================\n";
        cout << "1. Tambah Buku (Input)\n";
        cout << "2. Tampilkan Buku\n";
        cout << "3. Urutkan Buku (Sorting)\n";
        cout << "4. Pinjam Buku \n";
        cout << "5. Kembalikan Buku\n";
        cout << "6. Cari Buku (Searching)\n";
        cout << "7. Hapus Buku\n";
        cout << "8. Simpan Data ke File\n";
        cout << "9. Baca Data File\n";
        cout << "10. Update Buku File\n";
        // cout << "11. Hapus Buku Langsung dari File\n";
        cout << "0. Keluar\n";
        cout << "===================================\n";
        
        cout << "Pilih : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahBuku(); break;     //Tambah Buku
            case 2: tampilkanBuku(); break;  //Tampilkan Buku
            case 3: urutkanBuku(); break;    //
            case 4: pinjamBuku(); break;     //
            case 5: kembalikanBuku(); break; //
            case 6: searchBuku(); break;     //
            case 7: hapusBuku(); break;      //
            case 8: simpanKeFile(); break;   //
            case 9: bacaDariFile(); break;   //
            case 10: updateBuku(); break;    //
            // case 11: hapusDariFile(); break;  //
            case 0: cout << "Terima kasih telah menggunakan sistem perpustakaan!\n"; break;
            default:
            cout << "Pilihan tidak valid!\n\n";
        }
    } while (pilihan != 0);

    return 0;
}