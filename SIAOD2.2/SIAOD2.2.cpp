#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct FlightRecord {
    int key = -1;
    char departureLocation[100];
    char flightNumber[100];
    char arrivalDate[100];
    char arrivalTime[100];
    float delayHours;
};

// Функция для формирования нового двоичного файла с задержанными рейсами по указанной дате
void createDelayedFlightsBinaryFile(const vector<FlightRecord>& records, const string& outputFileName, const string& targetDate) {

    ofstream outputFile(outputFileName, ios::binary);

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла: " << outputFileName << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        if (record.arrivalDate == targetDate && record.delayHours > 0.0f) {
            outputFile.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecord));
        }
    }

    outputFile.close();
}



/*Данный метод больше не работает так как мы пытаемся присвоить новое значение (record.arrivalTime = newTime)
символьному массиву (char arrivalTime[100]) с использованием =, что в C++ не разрешено.
В результате возникала ошибка "E0137 expression must be a modifiable lvalue"

// Функция для изменения времени прилета для заданного рейса
void changeArrivalTime(vector<FlightRecord>& records, const string& flightNumber, const string& newTime) {
    for (FlightRecord& record : records) {
        if (record.flightNumber == flightNumber) {
            record.arrivalTime = newTime;
        }
    }
}*/




// Функция для изменения времени прилета для заданного рейса
void changeArrivalTime(vector<FlightRecord>& records, const string& flightNumber, const string& newTime) {
    for (FlightRecord& record : records) {
        if (strcmp(record.flightNumber, flightNumber.c_str()) == 0) { //Функция strcmp сравнивает две строки и возвращает 0, если они равны
            strncpy_s(record.arrivalTime, newTime.c_str(), sizeof(record.arrivalTime));//Функция strncpy_s предназначена для безопасного копирования строк, чтобы предотвратить переполнение буфера и сохранить целостность данных
        }//Метод c_str полезен, когда вам нужно передать данные из объекта string функциям или библиотекам, которые ожидают нуль-терминированные строки типа const char*
    }
}

// Функция для удаления записи с заданным номером в векторе
void deleteRecordByIndex(vector<FlightRecord>& records, size_t index) {
    if (index < records.size()) {
        records[index] = records.back(); // Копируем последнюю запись вместо найденной записи
        records.pop_back(); // Удаляем последнюю запись
    }
}

// Функция для чтения записей из текстового файла и преобразования их в структуры
vector<FlightRecord> readRecordsFromFile(const string& filename) {
    vector<FlightRecord> records;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return records;
    }

    FlightRecord record;
    while (file >> record.key >> record.departureLocation >> record.flightNumber >> record.arrivalDate >> record.arrivalTime >> record.delayHours) {
        records.push_back(record);
        file.ignore();
    }

    file.close();
    return records;
}

// Функция для записи записей в двоичный файл
void writeRecordsToBinaryFile(const vector<FlightRecord>& records, const string& filename) {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecord));
    }

    file.close();
}

// Функция для чтения записей из двоичного файла и преобразования их в структуры
vector<FlightRecord> readRecordsFromBinaryFile(const string& filename) {
    vector<FlightRecord> records;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return records;
    }

    FlightRecord record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(FlightRecord))) { //приведение указателя на объект record к указателю на символ (char). 
        records.push_back(record);
    }

    file.close();
    return records;
}

// Функция для записи записей из вектора в текстовый файл
void writeRecordsToTextFile(const vector<FlightRecord>& records, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        file << record.departureLocation << " " << record.flightNumber << " " << record.arrivalDate << " " << record.arrivalTime << " " << record.delayHours << "\n";
    }

    file.close();
}

int main() {
    /*

        // Прочитать записи из текстового файла
        vector<FlightRecord> records = readRecordsFromFile(inputTextFileName);

        // Записать записи в двоичный файл
        writeRecordsToBinaryFile(records, binaryFileName);

        // Прочитать записи из двоичного файла
        vector<FlightRecord> binaryRecords = readRecordsFromBinaryFile(binaryFileName);

        // Записать записи из двоичного файла в текстовый файл (для проверки)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);


        // Формировать новый двоичный файл с задержанными рейсами по указанной дате
        createDelayedFlightsBinaryFile(records, delayedFlightsFileName, "2023-10-05");

        // Прочитать записи из двоичного файла
        binaryRecords = readRecordsFromBinaryFile(delayedFlightsFileName);

        // Записать записи из двоичного файла в текстовый файл (для проверки)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);


        // Изменить время прилета для заданного рейса
        changeArrivalTime(records, "SY101", "12:30");

        // Записать записи в двоичный файл
        writeRecordsToBinaryFile(records, binaryFileName);

        // Прочитать записи из двоичного файла
        binaryRecords = readRecordsFromBinaryFile(binaryFileName);

        // Записать записи из двоичного файла в текстовый файл (для проверки)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);

    */



    /******************************************Для преподователя:
    Файл flight_records.txt теперь считается образцовым и во избежание его последующего редактирования доступ пользователя к нему ограничен.
    То есть из него можно только читать данные, но не видоизменять*/

    setlocale(LC_ALL, "Russian");
    vector<FlightRecord> records;
    vector<FlightRecord> binaryRecords;
    string inputTextFileName = "flight_records";
    string binaryFileName = "flight_records";
    string outputTextFileName = "flight_records_output";
    string delayedFlightsFileName = "delayed_flights";
    string delayedTextFlightsFileName = "delayed_flights";
    while (1) {
        cout << "Меню:\n" <<
            "1. Преобразование тестовых данных из текстового файла в двоичный файл.\n" <<
            "2. Преобразование данных из двоичного файла в текстовый.\n" <<
            "3. Вывод всех записей двоичного файла.\n" <<
            "4. Доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле.\n" <<
            "5. Удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись.\n" <<
            "6. Сформировать в новом двоичном файле информацию по рейсам, задержанным в указанную дату.\n" <<
            "7. Изменить время прилета для заданного рейса на новое значение.\n";
        int var;
        int opt;
        string delayedDate;
        string PlaneName;
        string FileName;
        cin >> var;
        switch (var) {

        case 1:
            cout << "Введите название двоичного файла, в который будут записаны данные из текстового файла: ";
            cin >> binaryFileName; //"flight_records.bin";

            // Прочитать записи из текстового файла
            records = readRecordsFromFile(inputTextFileName + ".txt");//"flight_records.txt";
            // Записать записи в двоичный файл
            writeRecordsToBinaryFile(records, binaryFileName + ".bin");
            break;

        case 2:
            cout << "Введите название файла, в который будут записаны данные из бинарного файла: ";
            cin >> outputTextFileName;//"flight_records_output.txt"
            if (outputTextFileName == "flight_records")
            {
                cout << "Извините, данное название зарезервированно, выберете другое.\n" << 
                    "Например flight_records_output" << endl;
                break;
            }
            // Прочитать записи из двоичного файла
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

            // Записать записи из двоичного файла в текстовый файл 
            writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            break;

        case 3:
            cout << "Введите название файла, из котороого будут взяты данные: ";
            cin >> binaryFileName;
            // Прочитать записи из двоичного файла
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");
            for (const FlightRecord& record : binaryRecords) {
                cout << "Пункт вылета: " << record.departureLocation << endl;
                cout << "Номер рейса: " << record.flightNumber << endl;
                cout << "Дата прилета: " << record.arrivalDate << endl;
                cout << "Время прилета: " << record.arrivalTime << endl;
                cout << "Задержка (часы): " << record.delayHours << endl;
                cout << "------------------------" << endl;
            }
            break;

        case 4:
            cout << "Введите название файла, над которым будут происходить манипуляции: ";
            cin >> binaryFileName;
            cout << "Введите порядковый номер записи в файле: ";
            cin >> opt;

            // Прочитать записи из двоичного файла
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

            cout << "Пункт вылета: " << binaryRecords[opt - 1].departureLocation << endl;
            cout << "Номер рейса: " << binaryRecords[opt - 1].flightNumber << endl;
            cout << "Дата прилета: " << binaryRecords[opt - 1].arrivalDate << endl;
            cout << "Время прилета: " << binaryRecords[opt - 1].arrivalTime << endl;
            cout << "Задержка (часы): " << binaryRecords[opt - 1].delayHours << endl;
            cout << "------------------------" << endl;
            break;

        case 5:
            cout << "Введите название файла, над которым будут происходить манипуляции: ";
            cin >> outputTextFileName;
            if (outputTextFileName == "flight_records")
            {
                cout << "Извините, данное название зарезервированно, выберете другое.\n" <<
                    "Например flight_records_output" << endl;
                break;
            }
            cout << "Введите порядковый номер записи в файле: ";
            cin >> opt;
            if (opt > records.size())
            {
                cout << "Ошибка, неверный индекс!";
            }
            else
            {
                // Прочитать записи из текстового файла
                records = readRecordsFromFile(inputTextFileName + ".txt");

                deleteRecordByIndex(records, opt - 1);

                for (const FlightRecord& record : records) {
                    cout << "Пункт вылета: " << record.departureLocation << endl;
                    cout << "Номер рейса: " << record.flightNumber << endl;
                    cout << "Дата прилета: " << record.arrivalDate << endl;
                    cout << "Время прилета: " << record.arrivalTime << endl;
                    cout << "Задержка (часы): " << record.delayHours << endl;
                    cout << "------------------------" << endl;
                }

                // Записать записи в двоичный файл
                writeRecordsToBinaryFile(records, binaryFileName + ".bin");

                // Прочитать записи из двоичного файла
                vector<FlightRecord> binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

                // Записать записи из двоичного файла в текстовый файл (для проверки)
                writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            }
            break;

        case 6:
            cout << "Введите название двоичного файла, в который будут записаны данные из текстового файла: ";
            cin >> delayedFlightsFileName; //"delayed_flights.bin"
            cout << "Введите дату, которая вас интересует (Пример оформления: 2022-10-05)" << endl;
            cin >> delayedDate;

            // Прочитать записи из текстового файла
            records = readRecordsFromFile(inputTextFileName + ".txt");//"flight_records.txt";

            // Формировать новый двоичный файл с задержанными рейсами по указанной дате
            createDelayedFlightsBinaryFile(records, delayedFlightsFileName + ".bin", delayedDate);

            // Прочитать записи из двоичного файла
            binaryRecords = readRecordsFromBinaryFile(delayedFlightsFileName + ".bin");

            // Записать записи из двоичного файла в текстовый файл (для проверки)
            writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            break;

        case 7:
            cout << "Введите название файла, над которым будут происходить манипуляции: ";
            cin >> outputTextFileName;
            if (outputTextFileName == "flight_records")
            {
                cout << "Извините, данное название зарезервированно, выберете другое.\n" <<
                    "Например flight_records_output" << endl;
                break;
            }
            cout << "Введите номер, интересующего вас рейса (Пример оформления: SY101)" << endl;
            cin >> PlaneName;
            cout << "Введите, интересующее вас время, на которое хотели бы заменить (Пример оформления: 10:15)" << endl;
            cin >> delayedDate;
            // Прочитать записи из текстового файла
            records = readRecordsFromFile(inputTextFileName + ".txt");

            // Изменить время прилета для заданного рейса
            changeArrivalTime(records, PlaneName, delayedDate);

            // Записать записи из двоичного файла в текстовый файл (для проверки)
            writeRecordsToTextFile(records, outputTextFileName + ".txt");
            break;

        default:
            break;
        }
    }
}
//flight_records