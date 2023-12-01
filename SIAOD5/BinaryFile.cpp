#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include "BinaryFile.h"

using namespace std;

/*создание двоичного файла из текстового*/
void BinaryFile::FromTextToBin() {
    vector<Staff> records;
    ifstream inputfile("MyTextFile.txt");

    if (!inputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyTextFile.txt" << endl;
        exit(1);
    }

    Staff record;
    while (inputfile >> record.IDNumber >> record.FullName >> record.EDU) {
        records.push_back(record);
        inputfile.ignore();
    }

    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary);

    if (!outputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }

    outputfile.close();
}

/*добавить запись в двоичный файл*/
void BinaryFile::addBin(const string& FullName, bool EDU) {
    ifstream inputfile("MyBinFile.bin", ios::binary | ios::in);
    vector<Staff> records;

    if (!inputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "Добавляем запись" << " в файл:\n";

    ifstream midlefile("MyBinFile.bin", ios::binary | ios::in);
    Staff record;
    while (midlefile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //приведение указателя на объект record к указателю на символ (char). 
        records.push_back(record);
    }
    midlefile.close();

    //ищем запись с самым большим идексом
    int max = records[0].IDNumber; 
    for (int i = 1; i < FILESIZE; i++) {
        if (records[i].IDNumber > max) {
            max = records[i].IDNumber; 
        }
    }

    Staff newRecord;
    newRecord.IDNumber = max + 1;
    strncpy_s(newRecord.FullName, FullName.c_str(), sizeof(newRecord.FullName));
    newRecord.EDU = EDU;

    records.push_back(newRecord);
    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary | ios::out);

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }

    outputfile.close();
}

//удалить запись с заданным ключом из файла
void BinaryFile::delBinIndex(int index) {
    vector<Staff> records;
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "Удаляем запись по индексу " << index << " из файла:\n";

    Staff record;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) {
        records.push_back(record);
    }
    inputfile.close();

    //Это кусок удаления по индексу(позиции в файле), если понадобится
    if (index < records.size() - 1)
    {
        for (index; index < records.size()-1; index++)
        {
            records[index] = records[index + 1];
        }
        records.pop_back();
    }
    else if(index > records.size() - 1)
    {
        cerr << "Записи с таким ключом не существует!" << endl;
        return;
    }

    // Заново открываем файл для записи (с указанием ios::out | ios::trunc)
    fstream outputfile("MyBinFile.bin", ios::binary | ios::out | ios::trunc);

    if (!outputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        return;
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }
    outputfile.close();

    // Теперь изменяем размер файла
    if (filesystem::exists("MyBinFile.bin")) {
        try {
            // Вычисляем размер файла после записи записей
            int size = records.size() * sizeof(Staff);
            filesystem::resize_file("MyBinFile.bin", size);
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "Ошибка при изменении размера файла: " << e.what() << endl;
        }
    }
    else {
        cerr << "Файл не существует: " << "MyBinFile.bin" << endl;
    }
}

void BinaryFile::delBinIDNumber(int key){
    vector<Staff> records;
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "Удаляем запись по ключу " << key << " из файла:\n";

    Staff record;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) {
        records.push_back(record);
    }
    inputfile.close();

    //Это кусок удаления по ключу(IDNumber в файле), если понадобится
    int counter = 0;
    for (int i = 0; i < FILESIZE; i++)
    {
        if (records[i].IDNumber == key)
        {
            counter = i;
            break;
        }
    }
    for (counter; counter < records.size() - 1; counter++)
    {
        records[counter] = records[counter + 1];
    }
    records.pop_back();

    // Заново открываем файл для записи (с указанием ios::out | ios::trunc)
    fstream outputfile("MyBinFile.bin", ios::binary | ios::out);

    if (!outputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        return;
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }
    outputfile.close();

    // Теперь изменяем размер файла
    if (filesystem::exists("MyBinFile.bin")) {
        try {
            // Вычисляем размер файла после записи записей
            int size = records.size() * sizeof(Staff);
            filesystem::resize_file("MyBinFile.bin", size);
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "Ошибка при изменении размера файла: " << e.what() << endl;
        }
    }
    else {
        cerr << "Файл не существует: " << "MyBinFile.bin" << endl;
    }
}

/*прочитать запись файла по заданному номеру записи*/
Staff BinaryFile::findBin(int index) {
    vector<Staff> records;
    ifstream file("MyBinFile.bin", ios::binary);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        return Staff();
    }
    cout << "Ищем запись " << index << " в файле:\n";

    Staff record;
    int x = 0;
    const auto start{ std::chrono::steady_clock::now() }; //начало замера времени
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //приведение указателя на объект record к указателю на символ (char). 
        records.push_back(record); x++;
    }

    file.close();
    for (int i = 0; i < x; i++)
    {
        if (records[i].IDNumber == index)
        {
            const auto end{ std::chrono::steady_clock::now() }; //конец замера времени (вычисление хеш-функции, рехеширование, чтение из файла)
            const std::chrono::duration<double> elapsed_seconds{ end - start };
            //check file
                cout << "Время линейного поиска: " << elapsed_seconds << endl;
            return records[i];
        }
    }
    cerr << "Записи с таким ключом не существует!" << endl;
    return Staff();
}

/*вывод записи по известному адресу в файле*/
Staff BinaryFile::findBinDir(int address)
{
    vector<Staff> records;
    Staff record;
    ifstream file("MyBinFile.bin", ios::binary);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        return Staff();
    }
    cout << "Ищем запись по адресу " << address << " в файле:\n";

    /*проверка на верность адреса
    размер струкуры (одной записи в файле) равен 105
    Поэтому если адрес не делится без остатка на 105 или больше длины файла помноженного на кол-во структур,
    то адрес можно считать неверным*/
    if (address % 105 != 0 || address > FILESIZE * 105)
    {
        return record;
    }
    file.seekg(address, ios::beg);

    // Прочитать запись
    file.read(reinterpret_cast<char*>(&record), sizeof(Staff)); 
    file.close();
    return record;
}

void BinaryFile::testBinF()
{
    setlocale(LC_ALL, "Russian");
    BinaryFile BF;
    int FILESIZE = 10;
    Staff StaffRecordStruct1;
    //Тест функции FromTextToBin
    BF.FromTextToBin();
    fstream fs1("MyBinFile.bin", ios::in | ios::binary);
    if (!fs1.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // Возврат с ошибкой
    }
    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs1.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    }
    cout << "======================================\n\n";
    fs1.close();

    //Тест функции findBin
    StaffRecordStruct1 = BF.findBin(5);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";

    //Тест функции addBin
    BF.addBin("Mike_Thompson", 1);
    FILESIZE++;
    fstream fs2("MyBinFile.bin", ios::in | ios::binary);
    if (!fs2.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // Возврат с ошибкой
    }

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs2.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    }
    cout << "======================================\n\n";
    fs2.close();

    //Тест функции delBin
    BF.delBinIndex(1);
    FILESIZE--;
    fstream fs3("MyBinFile.bin", ios::in | ios::binary);
    if (!fs3.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // Возврат с ошибкой
    }

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs3.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    }
    cout << "======================================\n\n";
    fs3.close();

    //Тест функции findBinDir
    StaffRecordStruct1 = BF.findBinDir(420);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";
    cout << sizeof(StaffRecordStruct1);
}