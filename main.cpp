#include "medis.h"
#include <iomanip> // untuk peggunaan setw()

using namespace std;

int main() {
    listDokter listD;
    listPasien listP;
    listPelayananMedis listPM;
    First(listD) = NULL;
    First(listP) = NULL;
    Last(listP) = NULL;

    string namafile = "data.txt";
    loadDoctors(listD, namafile);
    loadPatients(listP, namafile);
    loadPelayananMedis(listPM, listD, listP, namafile);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show Dokter\n";
        cout << "2. Show Pasien\n";
        cout << "3. Show Riwayat Pelayanan Medis\n";
        cout << "4. Delete Dokter\n";
        cout << "5. Delete Pasien\n";
        cout << "6. Delete Riwayat Pelayanan Medis\n";
        cout << "7. Insert Dokter\n";
        cout << "8. Insert Pasien\n";
        cout << "9. Insert Relasi\n";
        cout << "10. Menghapus dokter beserta semua pasien yang terhubung dengannya\n";
        cout << "11. Cari data Dokter berdasarkan ID\n";
        cout << "12. Cari data Pasien berdasarkan ID\n";
        cout << "13. Hubungkan Dokter dengan Pasien berdasarkan ID\n";
        cout << "14. Cari Pasien pada Dokter Tertentu\n";
        cout << "15. Menghapus pasien tertentu dari dokter tertentu beserta relasinya.\n";
        cout << "16. Hitung Jumlah Pasien dari Dokter Tertentu\n";
        cout << "17. Keluar dari aplikasi\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(); // Membersihkan buffer

        switch (choice) {
            case 1:
                cout << "List Dokter:" << endl;
                showDokter(listD);
                break;
            case 2:
                cout << "List Pasien:" << endl;
                showAllPasien(listP);
                break;
            case 3:
                cout << "List Riwayat Pelayanan Medis:" << endl;
                showAllRelasi(listPM);
                break;
            case 4: {
                adrDokter tempD;
                deleteFirstDokter(listD, listPM, tempD);
                delete tempD;
                break;
            }
            case 5: {
                adrPasien tempP;
                tempP = deleteLastPasien(listP, listPM);
                delete tempP;
                break;
            }
            case 6: {
                adrPelayanan tempPM = deleteRelasi(listPM, First(listPM));
                cout << "Riwayat pelayanan medis yang terakhir dimasukkan berhasil dihapus" << endl;
                delete tempPM;
                break;
            }
            case 7: {
                char lanjut;
                do {
                    dokter newDokter = inputDataDokter();
                    insertLastDokter(listD, newDokter);

                    cout << "Tambah dokter lagi? (y/n): ";
                    cin >> lanjut;
                    cin.ignore(); // Membersihkan buffer
                } while (lanjut == 'y' || lanjut == 'Y');
                break;
            }
            case 8: {
                char lanjut;
                do {
                    pasien newPasien = inputDataPasien();
                    insertFirstPasien(listP, newPasien);

                    cout << "Tambah pasien lagi? (y/n): ";
                    cin >> lanjut;
                    cin.ignore(); // Membersihkan buffer
                } while (lanjut == 'y' || lanjut == 'Y');
                break;
            }
            case 9: {
                char lanjut;
                do {
                    insertRelasi(listPM, listD, listP);

                    cout << "Tambah riwayat pelayanan lagi? (y/n): ";
                    cin >> lanjut;
                    cin.ignore(); // Membersihkan buffer
                } while (lanjut == 'y' || lanjut == 'Y');
                break;
            }
            case 10: {
                cout << "Ingin menghapus riwayat pelayanan dokter apa?";
                int input;
                cin >> input;
                deleteDokterWithAllThePatient(listPM, listD, listP, input);
                break;
            }
            case 11: {
                cout << "Ingin cari data Dokter dengan ID apa?: ";
                int input;
                cin >> input;
                adrDokter cari = findDokterByID(listD, input);

                cout << "-----------------------------------------------------------" << endl;
                cout << "| ID Dokter |        Nama         |     Spesialisasi      |" << endl;
                cout << "-----------------------------------------------------------" << endl;

                if (cari != NULL) { // Pastikan cari tidak NULL
                    cout << "| " << setw(9) << Info(cari).IDDokter << " | "
                         << setw(19) << Info(cari).Nama << " | "
                         << setw(21) << Info(cari).Spesialisasi << " | " << endl;
                } else {
                    cout << "Dokter dengan ID " << input << " tidak ditemukan." << endl;
                }

                cout << "-----------------------------------------------------------" << endl;
                break;
            }
            case 12: {
                cout << "Ingin cari data Pasien dengan ID apa?: ";
                int input;
                cin >> input;
                adrPasien cari = findPasienByID(listP, input);

                cout << "------------------------------------------------------------------" << endl;
                cout << "| ID Pasien |        Nama         | Umur |        Keluhan        |" << endl;
                cout << "------------------------------------------------------------------" << endl;

                if (cari != NULL) { // Pastikan cari tidak NULL
                    cout << "| " << setw(9) << Info(cari).IDPasien << " | "
                         << setw(19) << Info(cari).Nama << " | "
                         << setw(4) << Info(cari).umur << " | "
                         << setw(21) << Info(cari).Keluhan << " | " << endl;
                } else {
                    cout << "Pasien dengan ID " << input << " tidak ditemukan." << endl;
                }

                cout << "------------------------------------------------------------------" << endl;
                break;
            }
            case 13: { //masih salah {untuk pencarian id-id}
                cout << "Ingin menghubungkan Dokter ke Pasien apa?" << endl;
                int idD, idP;
                cout << "Masukkan ID Dokter: ";
                cin >> idD;
                cout << "Masukkan ID Pasien: ";
                cin >> idP;
                hubungkanDokterPasien(listPM, listD, listP, idD, idP);
                break;
            }
            case 14: {
                findPatientOnSpecificDocter(listPM, listD);
                break;
            }
            case 15: {
                cout << "Ingin menghapus Pasien dari Dokter apa?" << endl;

                int idD, idP;
                cout << "Masukkan ID Dokter: ";
                cin >> idD;
                cout << "Masukkan ID Pasien: ";
                cin >> idP;
                adrPasien hapus = deletePasienDariDokter(listD, listP, listPM, idP, idD);
                if (hapus != NULL) {
                    printf("Pasien dengan ID %d pada Dokter dengan ID %d berhasil dihapus", idP, idD);
                }
                delete hapus;
                break;
            }
            case 16: {
                cout << "Ingin menghitung jumlah Pasien dari Dokter dengan ID apa? " << endl;
                cout << "Masukkan ID Dokter: ";
                int idD;
                cin >> idD;
                cout << "Jumlah Pasien pada Dokter dengan ID "<< idD << "adalah "<< hitungPasienDokter(listPM, idD)<< endl;
                break;
            }
            case 17: {
                cout << "Keluar dari program." << endl;
                break;
            }
            default:
                cout << "Masukan invalid, coba lagi!" << endl;
        }
    } while (choice != 17);
}
