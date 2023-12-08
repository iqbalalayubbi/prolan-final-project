// command execute 
// g++ finalProject.cpp -o finalProject && .\finalProject
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include "TextTable.h"

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

const int TOTAL_DATA = 10;

void createTable(json headers_column, json body_column, int total, bool multi_arr=true){
    TextTable t( '-', '|', '+' );

    for (int i = 0; i < headers_column.size(); i++)
        t.add(headers_column[i]);
    t.endOfRow();


    for (int i = 0; i < total; i++)
    {
        if (multi_arr)
            for (int j = 0; j < headers_column.size(); j++)
                t.add(body_column[i][j]);   
        else   
            t.add(body_column[i]);
        t.endOfRow();
    }

    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t;
}

void loadData(){
    float divider = 100.0;
    AngkatanKerja Data_AK[TOTAL_DATA];

    // read json file
    ifstream f("data.json");
    json data = json::parse(f);
    for (int i=0; i<TOTAL_DATA; i++){
        Data_AK[i].min_umur = data[i]["min_umur"];
        Data_AK[i].max_umur = data[i]["max_umur"];
        Data_AK[i].bekerja = data[i]["bekerja"];
        Data_AK[i].pengangguran = data[i]["pengangguran"];
        Data_AK[i].angkatan_kerja = Data_AK[i].bekerja + Data_AK[i].pengangguran;
        Data_AK[i].bekerja_ak = round(((double)Data_AK[i].bekerja / (double)Data_AK[i].angkatan_kerja)*100.0*divider)/divider;
    }

    json dataArray = json::array();

    for (int i=0; i<TOTAL_DATA; i++){
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

    json dataFound = json::array();
    json header = json::array({"Golongan Umur", "Bekerja", "Pengangguran", "Angkatan Kerja (AK)", "Bekerja per AK"});

    if (age < 15) cout << "umur anda tidak masuk ke dalam AK";
    else{
        for (int i=0; i<TOTAL_DATA; i++){
            int min_age = allData[i]["min_umur"];
            int max_age = allData[i]["max_umur"];
            string range_umur;

            if (age >= min_age && age <= max_age && age < 60){
                range_umur = to_string(allData[i]["min_umur"])+" - "+to_string(allData[i]["max_umur"]);
                dataFound.push_back({
                    range_umur,
                    to_string(allData[i]["bekerja"]), 
                    to_string(allData[i]["pengangguran"]), 
                    to_string(allData[i]["angkatan_kerja"]), 
                    to_string(allData[i]["bekerja_ak"])
                });
                break;
            }

            if (age > 60){
                range_umur = "60 +";
                dataFound.push_back({
                    range_umur,
                    to_string(allData[i]["bekerja"]), 
                    to_string(allData[i]["pengangguran"]), 
                    to_string(allData[i]["angkatan_kerja"]), 
                    to_string(allData[i]["bekerja_ak"])
                });
                break;
            }
        }
    }
    createTable(header, dataFound, 1);
}

void sortDataByAK(){
    ifstream f("allData.json");
    json allData = json::parse(f);

    for (int i=0; i<TOTAL_DATA; i++){
        int idx = i;
        json min_ak = allData[i];

        for (int j=i; j<TOTAL_DATA; j++){
            if (allData[j]["angkatan_kerja"] < min_ak["angkatan_kerja"]){
                idx = j;
                min_ak = allData[j];
            }
        }

        allData[idx] = allData[i];
        allData[i] = min_ak;

    }

    json header = json::array({"Golongan Umur", "Bekerja", "Pengangguran", "Angkatan Kerja (AK)", "Bekerja per AK"});
    json body_cols = json::array();

    for (int i = 0; i < TOTAL_DATA; i++)
    {
        string range_umur;

        if (allData[i]["min_umur"] < 60){
            range_umur = to_string(allData[i]["min_umur"])+" - "+to_string(allData[i]["max_umur"]);
        }else{
            range_umur = "60 +";
        }
        body_cols.push_back({
            range_umur,
            to_string(allData[i]["bekerja"]), 
            to_string(allData[i]["pengangguran"]), 
            to_string(allData[i]["angkatan_kerja"]), 
            to_string(allData[i]["bekerja_ak"])
        });
    }
    
    createTable(header, body_cols, TOTAL_DATA);
}

void showAgeByAK(){
    ifstream f("allData.json");
    json allData = json::parse(f);

    double persentaseAK;
    json dataFound = json::array();
    cout << "Masukkan persentase bekerja per AK : ";
    cin >> persentaseAK;

    for (int i = 0; i < TOTAL_DATA; i++){
        string range_umur;

        if (allData[i]["bekerja_ak"] > persentaseAK){
            if (allData[i]["min_umur"] < 60)
                range_umur = to_string(allData[i]["min_umur"]) + " - " + to_string(allData[i]["max_umur"]);
            else
                range_umur = "60 +";

            dataFound.push_back(range_umur);
        }
    }    

    json header = json::array({"Golongan Umur"});
    createTable(header, dataFound, dataFound.size(), false);
}

int main() {
}


