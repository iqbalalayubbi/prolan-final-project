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

int main() {
    ifstream f("allData.json");
    json allData = json::parse(f);

    // cout << min_umur+max_umur << endl;

    // struct AngkatanKerja Data[2] = {100,200};

    // write json file
    // json data = json::array({ {"currency", "USD"}, {"value", 42.99} });
    // json data = json::object({Data});
    // j["bekerja"] = 5142340;
    // j["pengangguran"] = 1954126;
    // j["angkatan_kerja"] = 7096466;
    // ofstream o("pretty.json");
    // o << setw(4) << data << endl;

    // cout << Data[0].bekerja << endl;
}


