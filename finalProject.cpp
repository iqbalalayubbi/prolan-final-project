// command execute 
// g++ finalProject.cpp -o finalProject && .\finalProject
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
using json = nlohmann::json;

struct AngkatanKerja{
    int min_umur;
    int max_umur;
    int bekerja;
    int pengangguran;
    int angkatan_kerja;
    double bekerja_ak;
};

void loadData(){
    float divider = 100.0;
    AngkatanKerja Data_AK[10];

    // read json file
    ifstream f("data.json");
    json data = json::parse(f);
    for (int i=0; i<10; i++){
        Data_AK[i].min_umur = data[i]["min_umur"];
        Data_AK[i].max_umur = data[i]["max_umur"];
        Data_AK[i].bekerja = data[i]["bekerja"];
        Data_AK[i].pengangguran = data[i]["pengangguran"];
        Data_AK[i].angkatan_kerja = Data_AK[i].bekerja + Data_AK[i].pengangguran;
        Data_AK[i].bekerja_ak = round(((double)Data_AK[i].bekerja / (double)Data_AK[i].angkatan_kerja)*100.0*divider)/divider;
    }

    json dataArray = json::array();

    for (int i=0; i<10; i++){
        json obj = {
            {"min_umur", Data_AK[i].min_umur},
            {"max_umur", Data_AK[i].max_umur},
            {"bekerja", Data_AK[i].bekerja},
            {"pengangguran", Data_AK[i].pengangguran},
            {"angkatan_kerja", Data_AK[i].angkatan_kerja},
            {"bekerja_ak", Data_AK[i].bekerja_ak}
        };
        dataArray.push_back(obj);
    }
    ofstream o("allData.json");
    o << setw(4) << dataArray << endl;
}

void showDataByAge(){
    int age;
    ifstream f("allData.json");
    json allData = json::parse(f);
    cout << "Masukkan umur anda : ";
    cin >> age;

    if (age < 15) cout << "umur anda tidak masuk ke dalam AK";
    else{
        for (int i=0; i<10; i++){
            int min_age = allData[i]["min_umur"];
            int max_age = allData[i]["max_umur"];

            if (age >= min_age && age <= max_age && age < 60){
                cout << "Golongan Umur : " << allData[i]["min_umur"] << " - " << allData[i]["max_umur"] << endl;
                cout << "Bekerja : " << allData[i]["bekerja"] << endl;
                cout << "Pengangguran : " << allData[i]["pengangguran"] << endl;
                cout << "Angkatan Kerja : " << allData[i]["angkatan_kerja"] << endl;
                cout << "Bekerja per AK : " << allData[i]["bekerja_ak"] << endl;
            }

            if (age > 60){
                cout << "Golongan Umur : " << "60 +" << endl;
                cout << "Bekerja : " << allData[i]["bekerja"] << endl;
                cout << "Pengangguran : " << allData[i]["pengangguran"] << endl;
                cout << "Angkatan Kerja : " << allData[i]["angkatan_kerja"] << endl;
                cout << "Bekerja per AK : " << allData[i]["bekerja_ak"] << endl;
            }
        }
    }
}

int main() {
    showDataByAge();
// c.	Tampilkan golongan umur yang memiliki persentase (bekerja per AK) > dari x
// d.	Urutkan data berdasarkan presentase AK
// e.	Tampilkan data berdasarkan kelompok range usia Anda (done)
}


