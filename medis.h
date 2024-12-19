#ifndef medis_h
#define medis_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <iomanip> // untuk peggunaan setw() 

using namespace std;

#define Info(L) ((L)->info)
#define First(L) (L.First)
#define Last(L) (L.Last)
#define nextPasien(L) ((L)->nextPasien)
#define nextDokter(L) ((L)->nextDokter)
#define prevPasien(L) ((L)->prevPasien)
#define prevDokter(L) ((L)->prevDokter)
#define nextPelayanan(L) ((L)->nextPelayanan)

typedef struct elemenDokter *adrDokter;
typedef struct elemenPasien *adrPasien;
typedef struct elemenPelayananMedis *adrPelayanan;

//Tipe bentukan untuk Data
struct dokter {
    int IDDokter;
    string Nama, Spesialisasi;
};

struct pasien {
    int IDPasien, umur;
    string Nama, Keluhan;
};

struct pelayananMedis {
    int IDPelayanan;
    string Tanggal, Waktu;
    adrPasien Pasien;
    adrDokter Dokter;
};

//Tipe bentukan untuk elemen pada List
struct elemenDokter{
    dokter info;
    adrDokter nextDokter;
};

struct elemenPasien {
    pasien info;
    adrPasien nextPasien;
    adrPasien prevPasien;
};

struct elemenPelayananMedis{
    pelayananMedis info;
    adrPelayanan nextPelayanan;
};

//Tipe bentukan List
struct listDokter{
    adrDokter First;
};

struct listPasien{
    adrPasien First;
    adrPasien Last;
};

struct listPelayananMedis{
    adrPelayanan First;
};

//Prosedur untuk menambahkan data dari file .txt
void loadDoctors(listDokter &listD, string &namafile);
void loadPatients(listPasien &listP, string &namafile);
void loadPelayananMedis(listPelayananMedis &listPM, listDokter &listD, listPasien &listP, string &namafile);

//Fungsi dan prosedur Primitif DOKTER
bool isEmptyDokter(listDokter &L);
void insertLastDokter(listDokter &L, dokter newData);
void deleteFirstDokter(listDokter &L, listPelayananMedis &LPM, adrDokter &temp);
void showDokter(listDokter L);
dokter inputDataDokter();

//Fungsi dan prosedur Non-Primtitf DOKTER
adrDokter findDokterByID(listDokter &L, int ID);

//Fungsi dan prosedur Primitif PASIEN
void insertFirstPasien(listPasien &L, pasien newData);
void showAllPasien(listPasien L);
adrPasien deleteLastPasien(listPasien &L, listPelayananMedis &LPM);
pasien inputDataPasien();

//Fungsi dan prosedur Non-Primtitf PASIEN
adrPasien deletePasien(listPasien &L, int IDPasien, listPelayananMedis &LPM);
adrPasien findPasienByID(listPasien &L, int ID);
void findPatientOnSpecificDocter(listPelayananMedis LPM, listDokter LD);

//Fungsi dan Prosedur Primitif RELASI
void insertRelasi(listPelayananMedis &L, listDokter LD, listPasien LP);
void insertRelasiWithData(listPelayananMedis &L, adrPelayanan newdata);
adrPelayanan deleteRelasi(listPelayananMedis &LPM, adrPelayanan &pred);

//Fungsi dan Prosedur Non-Primitif RELASI
void showAllRelasi(listPelayananMedis &L);
void deleteDokterWithAllThePatient(listPelayananMedis &LPM, listDokter &LD, listPasien &LP, int IDDokter);
void hubungkanDokterPasien(listPelayananMedis &listPelayanan, listDokter &LD, listPasien &LP, int IDDokter, int IDPasien);
adrPasien deletePasienDariDokter(listDokter &listD, listPasien &listP, listPelayananMedis &listPM, int IDPasien, int IDDokter);
int hitungPasienDokter(listPelayananMedis &LP, int IDDokter);

#endif /* medis_h */
