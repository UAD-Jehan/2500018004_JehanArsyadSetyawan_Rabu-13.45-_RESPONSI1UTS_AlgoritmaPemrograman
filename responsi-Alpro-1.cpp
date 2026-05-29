#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define n 100

struct Kendaraan {
    string namaPemilik;
    string jenisKendaraan;
    string nomorKendaraan;
    int lamaParkir;

    string statusParkir;
    string metodePembayaran;
    string statusPembayaran;

    int totalBayar;
};

Kendaraan dataParkir[n];
int jumlahData = 0;


// LOGIN
bool login() {

    string username, password;

    cout << "===== LOGIN PETUGAS =====\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    if (username == "admin" && password == "nim") {

        cout << "\nLogin berhasil!\n";
        return true;

    } else {

        cout << "\nLogin gagal!\n";
        return false;
    }
}


// TARIF
int getTarif(string jenis) {

    if (jenis == "Motor" || jenis == "motor") {

        return 3000;

    } else if (jenis == "Mobil" || jenis == "mobil") {

        return 5000;

    } else if (jenis == "Truk" || jenis == "truk") {

        return 8000;
    }

    return 0;
}


// REKURSIF
int hitungRekursif(int jam, int tarif) {

    if (jam == 0) {

        return 0;
    }

    return tarif + hitungRekursif(jam - 1, tarif);
}


// STATUS PARKIR
string tentukanStatusParkir(int lamaParkir) {

    if (lamaParkir > 5) {

        return "Parkir Lama";

    } else {

        return "Parkir Biasa";
    }
}


// TAMBAH DATA
void tambahKendaraan() {

    if (jumlahData >= n) {

        cout << "\nData parkir penuh!\n";
        return;
    }

    Kendaraan k;

    cin.ignore(1000, '\n');

    cout << "\n===== TAMBAH DATA KENDARAAN =====\n";

    cout << "Nama Pemilik : ";
    getline(cin, k.namaPemilik);

    cout << "Jenis Kendaraan (Motor/Mobil/Truk) : ";
    getline(cin, k.jenisKendaraan);

    cout << "Nomor Kendaraan : ";
    getline(cin, k.nomorKendaraan);

    cout << "Lama Parkir (jam) : ";
    cin >> k.lamaParkir;

    k.statusParkir = tentukanStatusParkir(k.lamaParkir);

    int tarif = getTarif(k.jenisKendaraan);

    k.totalBayar = hitungRekursif(k.lamaParkir, tarif);

    int pilihBayar;

    cout << "\nMetode Pembayaran\n";
    cout << "1. Tunai\n";
    cout << "2. Transfer Bank\n";
    cout << "3. E-Wallet\n";
    cout << "Pilih : ";
    cin >> pilihBayar;

    switch (pilihBayar) {

        case 1:
            k.metodePembayaran = "Tunai";
            break;

        case 2:
            k.metodePembayaran = "Transfer Bank";
            break;

        case 3:
            k.metodePembayaran = "E-Wallet";
            break;

        default:
            k.metodePembayaran = "Tidak Diketahui";
    }

    char status;

    cout << "Apakah sudah dibayar? (y/n) : ";
    cin >> status;

    if (status == 'y' || status == 'Y') {

        k.statusPembayaran = "Sudah Bayar";

    } else {

        k.statusPembayaran = "Belum Bayar";
    }

    dataParkir[jumlahData] = k;

    jumlahData++;

    cout << "\nData kendaraan berhasil ditambahkan!\n";
}


// TAMPILKAN DATA
void tampilkanData() {

    cout << "\n===== DATA KENDARAAN PARKIR =====\n";

    if (jumlahData == 0) {

        cout << "Belum ada data kendaraan.\n";
        return;
    }

    for (int i = 0; i < jumlahData; i++) {

        cout << "\nData Ke-" << i + 1 << endl;

        cout << "Nama Pemilik      : "
             << dataParkir[i].namaPemilik << endl;

        cout << "Jenis Kendaraan   : "
             << dataParkir[i].jenisKendaraan << endl;

        cout << "Nomor Kendaraan   : "
             << dataParkir[i].nomorKendaraan << endl;

        cout << "Lama Parkir       : "
             << dataParkir[i].lamaParkir << " jam" << endl;

        cout << "Status Parkir     : "
             << dataParkir[i].statusParkir << endl;

        cout << "Metode Pembayaran : "
             << dataParkir[i].metodePembayaran << endl;

        cout << "Status Pembayaran : "
             << dataParkir[i].statusPembayaran << endl;

        cout << "Total Bayar       : Rp"
             << dataParkir[i].totalBayar << endl;
    }
}


// CETAK STRUK
void cetakStruk(Kendaraan k) {

    string namaFile = k.nomorKendaraan + "_struk.txt";

    ofstream file(namaFile);

    if (!file.is_open()) {

        cout << "Gagal membuat file!\n";
        return;
    }

    file << "===== STRUK PARKIR =====\n";
    file << "Nama Pemilik      : " << k.namaPemilik << endl;
    file << "Jenis Kendaraan   : " << k.jenisKendaraan << endl;
    file << "Nomor Kendaraan   : " << k.nomorKendaraan << endl;
    file << "Lama Parkir       : " << k.lamaParkir << " jam" << endl;
    file << "Status Parkir     : " << k.statusParkir << endl;
    file << "Metode Pembayaran : " << k.metodePembayaran << endl;
    file << "Status Pembayaran : " << k.statusPembayaran << endl;
    file << "Total Bayar       : Rp" << k.totalBayar << endl;
    file << "========================\n";

    file.close();

    cout << "Struk berhasil dibuat : " << namaFile << endl;
}


// HAPUS DATA
void hapusKendaraan() {

    if (jumlahData == 0) {

        cout << "\nData kosong!\n";
        return;
    }

    tampilkanData();

    int index;

    cout << "\nMasukkan nomor data yang ingin dihapus : ";
    cin >> index;

    if (index < 1 || index > jumlahData) {

        cout << "Data tidak valid!\n";
        return;
    }

    cetakStruk(dataParkir[index - 1]);

    for (int i = index - 1; i < jumlahData - 1; i++) {

        dataParkir[i] = dataParkir[i + 1];
    }

    jumlahData--;

    cout << "Data kendaraan berhasil dihapus!\n";
}


// MENU
void menu() {

    int pilihan;

    do {

        cout << "\n===== SISTEM INFORMASI PARKIR =====\n";

        cout << "1. Tambah Kendaraan\n";
        cout << "2. Lihat Data Kendaraan\n";
        cout << "3. Hapus Kendaraan Keluar\n";
        cout << "4. Keluar\n";

        cout << "Pilih Menu : ";
        cin >> pilihan;

        switch (pilihan) {

            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilkanData();
                break;

            case 3:
                hapusKendaraan();
                break;

            case 4:
                cout << "\nTerima kasih!\n";
                break;

            default:
                cout << "\nMenu tidak tersedia!\n";
        }

    } while (pilihan != 4);
}


// MAIN
int main() {

    bool berhasilLogin = login();

    if (berhasilLogin) {

        menu();
    }

    return 0;
}
