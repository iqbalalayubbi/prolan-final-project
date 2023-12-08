# Prolan Final Project

## Problems

<p align="center">
    <img src="angkatan kerja Indonesia 2017.jpg" width="400" alt="Godot Engine logo">
</p>

-   [x] Simpan data diatas ke dalam struct, tetapi data Angkatan Kerja (AK) dan Bekerja per AK tidak diinput oleh user melainkan dihitung di program
-   [x] Kemudian simpan ke dalam file dan dapat ditampilkan kembali
-   [x] Tampilkan golongan umur yang memiliki prosentase bekerja per AK lebih besar dari nilai tertentu
-   [x] Urutkan data berdasarkan prosentase AK
-   [x] Tampilkan data berdasarkan kelompok range usia Anda

## Library

-   [TextTable](https://github.com/haarcuba/cpp-text-table)
-   [nlohmann json](https://github.com/nlohmann/json)

## How To Solve

-   clone this project

```bash
  git clone https://github.com/iqbalalayubbi/prolan-final-project.git
```

-   before running other function make sure data be load

```bash
  loadData();
```

-   running the program

```bash
  g++ finalProject.cpp -o finalProject && .\finalProject
```

-   show age by AK persentase

```bash
  showAgeByAK();
```

-   sort data by angkatan kerja (using selection sort)

```bash
  sortDataByAK();
```

-   show data by user age

```bash
  showDataByAge();
```
