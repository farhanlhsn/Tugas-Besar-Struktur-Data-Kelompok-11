#include "medis.h"

//Load Data Awal
void loadDoctors(listDokter &listD, string &namafile) 
/*I.S. List dokter listD sembarang, namafile adalah nama file yang berisi data dokter dalam format yang benar.
F.S. Membaca data dokter dari file yang ditunjuk oleh namafile. Jika bagian "DOCTORS" ditemukan, elemen dokter baru ditambahkan ke dalam list listD menggunakan fungsi insertLastDokter. Jika file tidak ada atau tidak dapat dibaca, tidak ada perubahan pada listD.*/
{
    ifstream file(namafile);
    if (!file.is_open()) {
        cout << "File tidak bisa diakses! Silahkan periksa kembali file-nya" << namafile << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line == "DOCTORS") {
            while (getline(file, line) && !line.empty()) {
                stringstream ss(line);
                dokter newDokter;
                string id, nama, specialization;
                getline(ss, id, ',');
                getline(ss, nama, ',');
                getline(ss, specialization, ',');
                newDokter.IDDokter = stoi(id);
                newDokter.Nama = nama;
                newDokter.Spesialisasi = specialization;
                insertLastDokter(listD, newDokter);
            }
        }
    }
}

void loadPatients(listPasien &listP, string &namafile) 
/*I.S. List pasien listP sembarang, namafile adalah nama file yang berisi data pasien dalam format yang benar.
F.S. Membaca data pasien dari file yang ditunjuk oleh namafile. Jika bagian "PATIENTS" ditemukan, elemen pasien baru ditambahkan ke dalam list listP menggunakan fungsi insertFirstPasien. Jika file tidak ada atau tidak dapat dibaca, tidak ada perubahan pada listP.*/
{
    ifstream file(namafile);
    if (!file.is_open()) {
        cout << "File tidak bisa diakses! Silahkan periksa kembali file-nya" << namafile << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line == "PATIENTS") {
            while (getline(file, line) && !line.empty()) {
                stringstream ss(line);
                pasien newPatient;
                string id, umur, nama, keluhan;
                getline(ss, id, ',');
                getline(ss, umur, ',');
                getline(ss, nama, ',');
                getline(ss, keluhan, ',');
                newPatient.IDPasien = stoi(id);
                newPatient.umur = stoi(umur);
                newPatient.Nama = nama;
                newPatient.Keluhan = keluhan;
                insertFirstPasien(listP, newPatient);
            }
        }
    }
}

void loadPelayananMedis(listPelayananMedis &listPM, listDokter &listD, listPasien &listP, string &namafile) 
/*I.S. List pelayanan medis listPM sembarang, listD dan listP adalah list dokter dan pasien yang mungkin kosong, namafile adalah nama file yang berisi data pelayanan medis dalam format yang benar.
F.S. Membaca data pelayanan medis dari file yang ditunjuk oleh namafile. Jika bagian "PELAYANAN_MEDIS" ditemukan, elemen pelayanan medis baru ditambahkan ke dalam list listPM menggunakan fungsi insertRelasi. Jika file tidak ada atau tidak dapat dibaca, tidak ada perubahan pada listPM.*/
{
    ifstream file(namafile);
    if (!file.is_open()) {
        cout << "File tidak bisa diakses! Silahkan periksa kembali file-nya" << namafile << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line == "PELAYANAN_MEDIS") {
            while (getline(file, line) && !line.empty()) {
                stringstream ss(line);
                adrPelayanan newPelayanan = new elemenPelayananMedis;
                string idPelayanan, tanggal, waktu, idPasien, idDokter;

                getline(ss, idPelayanan, ',');
                getline(ss, tanggal, ',');
                getline(ss, waktu, ',');
                getline(ss, idPasien, ',');
                getline(ss, idDokter, ',');

                Info(newPelayanan).IDPelayanan = stoi(idPelayanan);
                Info(newPelayanan).Tanggal = tanggal;
                Info(newPelayanan).Waktu = waktu;

                Info(newPelayanan).Dokter = findDokterByID(listD, stoi(idDokter));
                Info(newPelayanan).Pasien = findPasienByID(listP, stoi(idPasien));

                insertRelasiWithData(listPM, newPelayanan);
            }
        }
    }
}


//Dokter
//============================================================================
bool isEmptyDokter(listDokter &L)
//Mengembalikan true jika list dokter kosong, false jika tidak.
{
    return (First(L) == NULL);
}

dokter inputDataDokter() 
//Mengembalikan struct dokter yang berisi data dokter yang diinput oleh pengguna
{
    string input;

    cout << "Masukkan data dokter (format: ID, Nama, Spesialisasi): ";
    getline(cin, input); // Membaca seluruh input dalam satu baris

    stringstream ss(input);
    dokter newDokter;
    string id, nama, spesialisasi;

    // Memisahkan input berdasarkan koma
    getline(ss, id, ',');
    getline(ss, nama, ',');
    getline(ss, spesialisasi, ',');

    // Membersihkan spasi yang mungkin ada setelah pemisahan
    newDokter.IDDokter = stoi(id);
    newDokter.Nama = nama;
    newDokter.Spesialisasi = spesialisasi;

    return newDokter;
}

void insertLastDokter(listDokter &L, dokter newData) 
/*I.S. Terdefinisi list dokter L, newData adalah data dokter yang valid.
F.S. Menambahkan elemen baru newData di akhir list dokter L.*/
{ 
    adrDokter D = new elemenDokter;
    Info(D) = newData;
    nextDokter(D) = NULL;

    if (isEmptyDokter(L)) {
        // Jika list kosong
        First(L) = D;
    } else {
        adrDokter cek = First(L);
        while (nextDokter(cek) != NULL) {
            cek = nextDokter(cek);
        }
        nextDokter(cek) = D;
    }
}

void deleteFirstDokter(listDokter &L, listPelayananMedis &LPM, adrDokter &temp) 
/*I.S. List dokter L sembarang, temp adalah pointer untuk menyimpan elemen yang dihapus.
F.S. Menghapus elemen pertama dari list dokter L dan menyimpan alamat elemen yang dihapus ke dalam temp. Jika list kosong, menampilkan pesan bahwa list kosong.*/
{
    if (isEmptyDokter(L)) {
        cout << "List Dokter Kosong" << endl;
    } else {
        adrDokter D = First(L);
        temp = D;
        if (nextDokter(D) == NULL) {
            First(L) = NULL;
        } else {
            First(L) = nextDokter(D);
            nextDokter(temp) = NULL;
        }

        adrPelayanan pel = First(LPM);
        while (pel != NULL) {
            adrPelayanan nextPel = nextPelayanan(pel);
            if (Info(pel).Dokter == temp) {
                adrPelayanan deletedPel = deleteRelasi(LPM, pel);
                delete deletedPel;
            }
            pel = nextPel;
        }
        cout << "Dokter pertama berhasil di hapus" << endl;
    }
}

void showDokter(listDokter L)
/*I.S. List dokter L sembarang.
F.S. Menampilkan semua informasi dokter dalam list L. Jika list kosong, menampilkan pesan bahwa list kosong.*/
{
    cout << "-----------------------------------------------------------" << endl;
    cout << "| ID Dokter |        Nama         |     Spesialisasi      |" << endl;
    cout << "-----------------------------------------------------------" << endl;

    if (First(L) == NULL) {
        cout << "List Dokter kosong" << endl;
    }

    adrDokter P = First(L);
    while (P != NULL) {
        // Menampilkan data pasien dalam format tabel
        cout << "| " << setw(9) << Info(P).IDDokter << " | "
             << setw(19) << Info(P).Nama << " | "
             << setw(21) << Info(P).Spesialisasi << " | " << endl;
        cout << "-----------------------------------------------------------" << endl;
        P = nextDokter(P);
    }
}

adrDokter findDokterByID(listDokter &L, int ID)
/*I.S. List dokter L terdefinisi, ID adalah ID dokter yang dicari
F.S. Mengembalikan address dokter dengan ID yang sesuai, atau NULL jika tidak ditemukan*/
{
    adrDokter Q = First(L);
    while (Q!=NULL) {
        if (Info(Q).IDDokter == ID) {
            return Q;
        }
        Q = nextDokter(Q);
    }
    return NULL;
}

//Pasien
//==========================================================
pasien inputDataPasien() 
//Mengembalikan struct pasien yang berisi data pasien yang diinput oleh pengguna
{
    pasien newData;
    string input;
    cout << "Masukkan data pasien (format: ID, Umur, Nama, Keluhan): ";
    getline(cin, input); // Read the entire line for patient details

    stringstream ssPatient(input);
    string id, umur, nama, keluhan;
    getline(ssPatient, id, ',');
    getline(ssPatient, umur, ',');
    getline(ssPatient, nama, ',');
    getline(ssPatient, keluhan, ',');

    newData.IDPasien = stoi(id);
    newData.umur = stoi(umur);
    newData.Nama = nama;
    newData.Keluhan = keluhan;
    return newData;
}

void insertFirstPasien(listPasien &L, pasien newData)
/*I.S. List pasien L sembarang, newData adalah data pasien yang valid.
F.S. Menambahkan elemen baru newData di awal list pasien L.*/
{
    adrPasien P = new elemenPasien;
    Info(P) = newData;
    nextPasien(P) = NULL;
    prevPasien(P) = NULL;

    if (First(L) == NULL) { // Jika list kosong
        First(L) = P;
        Last(L) = P;
    } else { // Insert di awal
        nextPasien(P) = First(L);
        prevPasien(First(L)) = P;
        First(L) = P;
    }

}

adrPasien deleteLastPasien(listPasien &L, listPelayananMedis &LPM)
/* Menghapus elemen terakhir dari list pasien L dan mengembalikan alamat elemen yang dihapus. Jika list kosong, menampilkan pesan bahwa list kosong. Juga menghapus semua relasi pelayanan medis yang terkait. */
{
    adrPasien temp = NULL;
    if (First(L) == NULL) {
        cout << "List Pasien Kosong" << endl;
        return NULL;
    } else {
        temp = Last(L);
        if (First(L) == Last(L)) {
            First(L) = NULL;
            Last(L) = NULL;
        } else {
            Last(L) = prevPasien(temp);
            nextPasien(Last(L)) = NULL;
        }

        // Hapus semua pelayanan medis yang terkait dengan pasien ini
        adrPelayanan pel = First(LPM);
        while (pel != NULL) {
            adrPelayanan nextPel = nextPelayanan(pel);
            if (Info(pel).Pasien == temp) {
                deleteRelasi(LPM, pel);
            }
            pel = nextPel;
        }
        cout << "Pasien terakhir berhasil dihapus" << endl;
    }
    return temp;
}

adrPasien deletePasien(listPasien &L, int IDPasien, listPelayananMedis &LPM)
/*Menghapus pasien dengan IDPasien dari list L dan mengembalikan alamat elemen yang dihapus. Jika pasien tidak ditemukan, menampilkan pesan yang sesuai.*/
{
    if (First(L) == NULL) {
        cout << "List kosong, tidak ada pasien yang dapat dihapus." << endl;
        return NULL;
    }

    adrPasien P = First(L);

    while (P != NULL && Info(P).IDPasien != IDPasien) {
        P = nextPasien(P);
    }

    if (P == NULL) {
        cout << "Pasien dengan ID " << IDPasien << " tidak ditemukan." << endl;
        return NULL;
    }

    // Jika pasien ditemukan
    if (P == First(L)) {
        First(L) = nextPasien(P);
        if (First(L) != NULL) {
            prevPasien(First(L)) = NULL;
        }
    } else if (P == Last(L)) {
        adrPasien temp = deleteLastPasien(L, LPM);
        delete temp;
    } else {
        nextPasien(prevPasien(P)) = nextPasien(P);
        prevPasien(nextPasien(P)) = prevPasien(P);
    }
    nextPasien(P) = NULL;
    prevPasien(P) = NULL;
    return P;
}

void showAllPasien(listPasien L)
/*I.S. List pasien L sembarang.
F.S. Menampilkan semua informasi pasien dalam list L. Jika list kosong, menampilkan pesan bahwa list kosong.*/
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "| ID Pasien |        Nama         | Umur |        Keluhan        |" << endl;
    cout << "------------------------------------------------------------------" << endl;

    if (First(L) == NULL) {
        cout << "List pasien kosong" << endl;
    }

    adrPasien P = First(L);
    while (P != NULL) {
        // Menampilkan data pasien dalam format tabel
        cout << "| " << setw(9) << Info(P).IDPasien << " | "
             << setw(19) << Info(P).Nama << " | "
             << setw(4) << Info(P).umur << " | "
             << setw(21) << Info(P).Keluhan << " | " << endl;
        cout << "------------------------------------------------------------------" << endl;
        P = nextPasien(P);
    }
}

int hitungPasienDokter(listPelayananMedis &LP, int IDDokter)
/* Menghitung dan menampilkan jumlah pasien yang dirawat oleh dokter dengan IDDokter tertentu. */
{
    int count = 0;
    adrPelayanan P = First(LP);

    while (P != NULL) {
        if (Info(P).Dokter->info.IDDokter == IDDokter) { 
            count++;
        }
        P = nextPelayanan(P);
    }
    return count;
}

adrPasien findPasienByID(listPasien &L, int ID)
/* Mengembalikan alamat elemen pasien yang memiliki ID sama dengan ID yang dicari.
    Jika tidak ditemukan, mengembalikan NULL.
*/
{
    adrPasien P = First(L);
    while (P!=NULL) {
        if (Info(P).IDPasien == ID) {
            return P;
        }
        P = nextPasien(P);
    }
    return NULL;
}

//relasi
//==================================================================
adrPelayanan createRelasi(listDokter LD, listPasien LP) 
/*I.S. List dokter LD dan list pasien LP terdefinisi
F.S. Mengembalikan address baru pelayanan medis dengan data yang diinput, 
    jika pasien atau dokter tidak ditemukan, data baru akan ditambahkan ke list*/
{
    string input;
    cout << "Masukkan data riwayat pelayanan medis (format: IDPelayanan,Tanggal,Waktu,IDPasien,IDDokter):";

    getline(cin, input); // Ambil input user

    stringstream ss(input);
    cout << "Full input: " << input << endl;
    adrPelayanan newPelayanan = new elemenPelayananMedis;
    string idPelayanan, tanggal, waktu, idPasien, idDokter;

    getline(ss, idPelayanan, ',');
    getline(ss, tanggal, ',');
    getline(ss, waktu, ',');
    getline(ss, idPasien, ',');
    getline(ss, idDokter, ',');

    Info(newPelayanan).IDPelayanan = stoi(idPelayanan);
    Info(newPelayanan).Tanggal = tanggal;
    Info(newPelayanan).Waktu = waktu;

    Info(newPelayanan).Dokter = findDokterByID(LD, stoi(idDokter));
    Info(newPelayanan).Pasien = findPasienByID(LP, stoi(idPasien));

    // Tambahkan pasien atau dokter jika tidak ditemukan
    if (Info(newPelayanan).Pasien == NULL) {
        cout << "Pasien tidak ditemukan. Masukkan data Pasien (ID, umur, Nama, Keluhan): ";
        pasien newData = inputDataPasien();
        insertFirstPasien(LP, newData);
        Info(newPelayanan).Pasien = findPasienByID(LP, newData.IDPasien);
    }

    if (Info(newPelayanan).Dokter == NULL) {
        cout << "Dokter tidak ditemukan. Masukkan data Dokter (ID, Nama, Spesialisasi): ";
        dokter newDokter = inputDataDokter();
        insertLastDokter(LD, newDokter);
        Info(newPelayanan).Dokter = findDokterByID(LD, newDokter.IDDokter);
    }

    nextPelayanan(newPelayanan) = NULL;
    return newPelayanan;
}

void insertRelasiWithData(listPelayananMedis &L, adrPelayanan newdata) 
/*I.S. List pelayanan medis L sembarang, newdata adalah address pelayanan medis yang valid
F.S. Menambahkan newdata ke awal list pelayanan medis L*/
{
    if (First(L) == NULL) {
        First(L) = newdata; 
    } else {
        nextPelayanan(newdata) = First(L); 
        First(L) = newdata;
    }
}

void insertRelasi(listPelayananMedis &L, listDokter LD, listPasien LP) 
/*I.S. List pelayanan medis L, list dokter LD, dan list pasien LP terdefinisi
F.S. Menambahkan data relasi pelayanan medis baru ke awal list L setelah input data*/
{
    adrPelayanan newdata = createRelasi(LD, LP); 
    if (First(L) == NULL) {
        First(L) = newdata; 
    } else {
        nextPelayanan(newdata) = First(L); 
        First(L) = newdata;
    }
}

void showAllRelasi(listPelayananMedis &L)
/*I.S. List Pelayanan Medis L sembarang.
F.S. Menampilkan semua informasi Riwayat Pelayanan Medis dalam list L. Jika list kosong, menampilkan pesan bahwa list kosong.*/
{
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "| ID Pelayanan |    Tanggal    |  Waktu  |     Nama Pasien     |     Nama Dokter     |" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;

    if (First(L) == NULL) {
        cout << "List pasien kosong" << endl;
    }

    adrPelayanan P = First(L);
    while (P != NULL) {
        // Menampilkan data pasien dalam format tabel
        cout << "| " << setw(12) << Info(P).IDPelayanan << " | "
             << setw(13) << Info(P).Tanggal << " | "
             << setw(7) << Info(P).Waktu << " | "
             << setw(19) << Info(P).Pasien->info.Nama << " | "
             << setw(19) << Info(P).Dokter->info.Nama << " | " << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        P = nextPelayanan(P);
    }
}

void deleteDokterWithAllThePatient(listPelayananMedis &LPM, listDokter &LD, listPasien &LP, int IDDokter)
/*I.S. List pelayanan medis LPM, list dokter LD, list pasien LP terdefinisi, IDDokter adalah ID dokter yang akan dihapus
F.S. Dokter dengan IDDokter beserta semua pasien dan riwayat pelayanan medis terkait telah dihapus dari list*/
{
    adrDokter D = findDokterByID(LD, IDDokter);
    if (D == NULL) {
        cout << "Dokter tidak ditemukan!" << endl;
        return;
    }
    adrPelayanan PM = First(LPM);
    while (PM != NULL) {
        adrPelayanan nextPM = nextPelayanan(PM);
        if (Info(PM).Dokter == D) {
            adrPasien tempP = deletePasien(LP, Info(PM).Pasien->info.IDPasien, LPM);
            delete tempP;
            adrPelayanan tempPPPP = deleteRelasi(LPM, PM);
            delete tempPPPP;
        }
        PM = nextPM;
    }

    //hapus dokter
    if (D == First(LD)) { //Jika dokter ada pada awal list Dokter
        deleteFirstDokter(LD, LPM, D);
    } else { //Selain itu
        adrDokter D_now = First(LD);
        while (D_now != NULL) {
            if (nextDokter(D_now) == D) {
                nextDokter(D_now) = nextDokter(D);
                break; 
            }
            D_now = nextDokter(D_now);
        }
    }
    cout << "Dokter beserta Pasien dan Riwayat Pelayanan berhasil dihapus!" << endl;
}

adrPelayanan deleteRelasi(listPelayananMedis &LPM, adrPelayanan &pred) 
/*I.S. List pelayanan medis LPM dan address pred terdefinisi
F.S. Menghapus elemen relasi yang ditunjuk oleh pred dari list LPM dan mengembalikan address elemen yang dihapus*/
{
    if (pred == NULL || First(LPM) == NULL) {
        return NULL;
    }

    adrPelayanan temp = NULL;

    if (pred == First(LPM)) {
        temp = pred;
        First(LPM) = nextPelayanan(pred);
        nextPelayanan(temp) = NULL;
    } else {
        adrPelayanan p = First(LPM);
        while (p != NULL && nextPelayanan(p) != pred) {
            p = nextPelayanan(p);
        }

        if (p != NULL && nextPelayanan(p) == pred) {
            temp = pred;
            nextPelayanan(p) = nextPelayanan(pred);
            nextPelayanan(temp) = NULL;
        } else {
        }
    }

    return temp;
}

void findPatientOnSpecificDocter(listPelayananMedis LPM, listDokter LD) 
/*I.S. List pelayanan medis LPM dan list dokter LD terdefinisi
F.S. Menampilkan informasi pasien dengan nama tertentu yang dilayani oleh dokter dengan ID tertentu, atau pesan jika tidak ditemukan*/
{
    adrPelayanan PM = First(LPM);

    // Input nama pasien
    cout << "Ingin mencari pasien dengan nama siapa?: ";
    string namaP;
    getline(cin, namaP);

    // Input ID dokter
    cout << "Ingin mencari pasien pada dokter dengan ID apa?: ";
    int idD;
    cin >> idD;

    // Cari dokter berdasarkan ID
    adrDokter D = findDokterByID(LD, idD);
    if (D == NULL) {
        cout << "Dokter dengan ID " << idD << " tidak ditemukan." << endl;
        return;
    }

    // Cari pasien dengan nama tertentu yang dilayani oleh dokter tertentu
    bool ketemu = false;

    cout << "-----------------------------------" << endl;
    cout << "|     Nama Pasien     | ID Dokter |" << endl;
    cout << "-----------------------------------" << endl;

    while (PM != NULL) {
        // Cek apakah dokter pada pelayanan ini sama dan nama pasien cocok
        if (Info(PM).Dokter == D && Info(PM).Pasien->info.Nama == namaP) {
            ketemu = true;
            // Menampilkan hasil dalam format tabel
            cout << "| " << setw(19) << Info(PM).Pasien->info.Nama << " | "
                 << setw(9) << Info(D).IDDokter << " | " << endl;
            break;
        }
        PM = nextPelayanan(PM);
    }

    if (!ketemu) {
        cout << "Tidak ditemukan! Tidak benar bahwa pasien dengan nama " << namaP
             << " dilayani oleh dokter dengan ID " << idD << "." << endl;
    } else {
        cout << "-----------------------------------" << endl;
    }
}

void hubungkanDokterPasien(listPelayananMedis &listPelayanan, listDokter &LD, listPasien &LP, int IDDokter, int IDPasien) 
/*  I.S. List pelayanan medis, list dokter, dan list pasien terdefinisi.
    IDDokter adalah ID dokter yang ingin dihubungkan, IDPasien adalah ID pasien yang ingin dihubungkan.
    F.S. Jika dokter dan pasien ditemukan, relasi baru ditambahkan ke list pelayanan medis.
    Jika tidak ditemukan, pesan kesalahan ditampilkan.
*/
{
    // Mencari dokter berdasarkan ID
    adrDokter dokter = findDokterByID(LD, IDDokter);
    cout << Info(dokter).Nama << endl;
    if (dokter == NULL) {
        cout << "Dokter dengan ID " << IDDokter << " tidak ditemukan." << endl;
        return;
    }

    // Mencari pasien berdasarkan ID
    adrPasien pasien = findPasienByID(LP, IDPasien);
    cout << Info(pasien).Nama << endl;
    if (pasien == NULL) {
        cout << "Pasien dengan ID " << IDPasien << " tidak ditemukan." << endl;
        return;
    }

    adrPelayanan newPelayanan = new elemenPelayananMedis;

    cin.ignore();
    string tempIDPelayanan, tempTanggal, tempWaktu;

    cout << "Masukkan ID Pelayanan: ";
    getline(cin, tempIDPelayanan);
    Info(newPelayanan).IDPelayanan = stoi(tempIDPelayanan);

    // Mengisi tanggal dan waktu secara manual
    cout << "Masukkan Tanggal Pelayanan (YYYY-MM-DD): ";
    getline(cin, tempTanggal);
    Info(newPelayanan).Tanggal = tempTanggal;

    cout << "Masukkan Waktu Pelayanan (HH:MM): ";
    getline(cin, tempWaktu);
    Info(newPelayanan).Waktu = tempWaktu;

    Info(newPelayanan).Dokter = dokter;
    Info(newPelayanan).Pasien = pasien;
    nextPelayanan(newPelayanan) = NULL;
    
    insertRelasiWithData(listPelayanan, newPelayanan);

    // Menambahkan relasi ke list pelayanan medis
    cout << "Dokter " << dokter->info.Nama << " telah terhubung dengan pasien " << pasien->info.Nama << "." << endl;
}

adrPasien deletePasienDariDokter(listDokter &listD, listPasien &listP, listPelayananMedis &listPM, int IDPasien, int IDDokter) {
/*  Kembalikan Jika dokter dan pasien ditemukan, relasi dihapus dari list pelayanan medis dan pasien dihapus 
    dari list pasien. jika tidak ditemukan, pesan kesalahan ditampilkan.
*/

    // Mencari dokter berdasarkan ID
    adrDokter dokter = findDokterByID(listD, IDDokter);
    if (dokter == NULL) {
        cout << "Dokter tidak ditemukan." << endl;
        return NULL;
    }

    // Mencari pasien berdasarkan ID
    adrPasien pasien = findPasienByID(listP, IDPasien);
    if (pasien == NULL) {
        cout << "Pasien tidak ditemukan." << endl;
        return NULL;
    }

    // Menghapus relasi dari listPelayananMedis
    adrPelayanan Pel = First(listPM);
    while (Pel != NULL) {
        if (Info(Pel).Pasien == pasien && Info(Pel).Dokter == dokter) {
            deleteRelasi(listPM, Pel);
            break;
        }
        Pel = nextPelayanan(Pel);
    }
    
    // Menghapus pasien dari listPasien
    adrPasien deleted = deletePasien(listP, IDPasien, listPM);
    return deleted;
}

void showDokterWithPasien(listDokter &listD, listPelayananMedis &listPM)
/* I.S. List dokter dan list pelayanan medis terdefinisi.
   F.S. Menampilkan informasi dokter beserta pasien yang terhubung dengan dokter tersebut.
*/
{
    adrDokter Dok = First(listD);
    while (Dok != NULL) {
        cout << "Dokter ID: " << Info(Dok).IDDokter << endl;
        cout << "Nama: " << Info(Dok).Nama << endl;
        cout << "Spesialisasi: " << Info(Dok).Spesialisasi << endl;
        cout << "Pasien yang terhubung:" << endl;

        // Mencari pasien yang terhubung dengan dokter ini
        adrPelayanan Pas = First(listPM);
        while (Pas != NULL) {
            if (Info(Pas).Dokter == Dok) {
                cout << " - Pasien ID: " << Info(Pas).Pasien->info.IDPasien << endl;
                cout << "   Nama: " << Info(Pas).Pasien->info.Nama << endl;
                cout << "   Keluhan: " << Info(Pas).Pasien->info.Keluhan << endl;
            }
            Pas = nextPelayanan(Pas);
        }
        cout << endl;
        Dok = nextDokter(Dok);
    }
}
