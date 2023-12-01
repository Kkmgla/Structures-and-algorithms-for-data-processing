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

// ������� ��� ������������ ������ ��������� ����� � ������������ ������� �� ��������� ����
void createDelayedFlightsBinaryFile(const vector<FlightRecord>& records, const string& outputFileName, const string& targetDate) {

    ofstream outputFile(outputFileName, ios::binary);

    if (!outputFile.is_open()) {
        cerr << "������ �������� �����: " << outputFileName << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        if (record.arrivalDate == targetDate && record.delayHours > 0.0f) {
            outputFile.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecord));
        }
    }

    outputFile.close();
}



/*������ ����� ������ �� �������� ��� ��� �� �������� ��������� ����� �������� (record.arrivalTime = newTime)
����������� ������� (char arrivalTime[100]) � �������������� =, ��� � C++ �� ���������.
� ���������� ��������� ������ "E0137 expression must be a modifiable lvalue"

// ������� ��� ��������� ������� ������� ��� ��������� �����
void changeArrivalTime(vector<FlightRecord>& records, const string& flightNumber, const string& newTime) {
    for (FlightRecord& record : records) {
        if (record.flightNumber == flightNumber) {
            record.arrivalTime = newTime;
        }
    }
}*/




// ������� ��� ��������� ������� ������� ��� ��������� �����
void changeArrivalTime(vector<FlightRecord>& records, const string& flightNumber, const string& newTime) {
    for (FlightRecord& record : records) {
        if (strcmp(record.flightNumber, flightNumber.c_str()) == 0) { //������� strcmp ���������� ��� ������ � ���������� 0, ���� ��� �����
            strncpy_s(record.arrivalTime, newTime.c_str(), sizeof(record.arrivalTime));//������� strncpy_s ������������� ��� ����������� ����������� �����, ����� ������������� ������������ ������ � ��������� ����������� ������
        }//����� c_str �������, ����� ��� ����� �������� ������ �� ������� string �������� ��� �����������, ������� ������� ����-��������������� ������ ���� const char*
    }
}

// ������� ��� �������� ������ � �������� ������� � �������
void deleteRecordByIndex(vector<FlightRecord>& records, size_t index) {
    if (index < records.size()) {
        records[index] = records.back(); // �������� ��������� ������ ������ ��������� ������
        records.pop_back(); // ������� ��������� ������
    }
}

// ������� ��� ������ ������� �� ���������� ����� � �������������� �� � ���������
vector<FlightRecord> readRecordsFromFile(const string& filename) {
    vector<FlightRecord> records;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
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

// ������� ��� ������ ������� � �������� ����
void writeRecordsToBinaryFile(const vector<FlightRecord>& records, const string& filename) {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecord));
    }

    file.close();
}

// ������� ��� ������ ������� �� ��������� ����� � �������������� �� � ���������
vector<FlightRecord> readRecordsFromBinaryFile(const string& filename) {
    vector<FlightRecord> records;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
        return records;
    }

    FlightRecord record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(FlightRecord))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        records.push_back(record);
    }

    file.close();
    return records;
}

// ������� ��� ������ ������� �� ������� � ��������� ����
void writeRecordsToTextFile(const vector<FlightRecord>& records, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
        return;
    }

    for (const FlightRecord& record : records) {
        file << record.departureLocation << " " << record.flightNumber << " " << record.arrivalDate << " " << record.arrivalTime << " " << record.delayHours << "\n";
    }

    file.close();
}

int main() {
    /*

        // ��������� ������ �� ���������� �����
        vector<FlightRecord> records = readRecordsFromFile(inputTextFileName);

        // �������� ������ � �������� ����
        writeRecordsToBinaryFile(records, binaryFileName);

        // ��������� ������ �� ��������� �����
        vector<FlightRecord> binaryRecords = readRecordsFromBinaryFile(binaryFileName);

        // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);


        // ����������� ����� �������� ���� � ������������ ������� �� ��������� ����
        createDelayedFlightsBinaryFile(records, delayedFlightsFileName, "2023-10-05");

        // ��������� ������ �� ��������� �����
        binaryRecords = readRecordsFromBinaryFile(delayedFlightsFileName);

        // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);


        // �������� ����� ������� ��� ��������� �����
        changeArrivalTime(records, "SY101", "12:30");

        // �������� ������ � �������� ����
        writeRecordsToBinaryFile(records, binaryFileName);

        // ��������� ������ �� ��������� �����
        binaryRecords = readRecordsFromBinaryFile(binaryFileName);

        // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
        writeRecordsToTextFile(binaryRecords, outputTextFileName);

    */



    /******************************************��� �������������:
    ���� flight_records.txt ������ ��������� ���������� � �� ��������� ��� ������������ �������������� ������ ������������ � ���� ���������.
    �� ���� �� ���� ����� ������ ������ ������, �� �� ������������*/

    setlocale(LC_ALL, "Russian");
    vector<FlightRecord> records;
    vector<FlightRecord> binaryRecords;
    string inputTextFileName = "flight_records";
    string binaryFileName = "flight_records";
    string outputTextFileName = "flight_records_output";
    string delayedFlightsFileName = "delayed_flights";
    string delayedTextFlightsFileName = "delayed_flights";
    while (1) {
        cout << "����:\n" <<
            "1. �������������� �������� ������ �� ���������� ����� � �������� ����.\n" <<
            "2. �������������� ������ �� ��������� ����� � ���������.\n" <<
            "3. ����� ���� ������� ��������� �����.\n" <<
            "4. ������ � ������ �� �� ����������� ������ � �����, ��������� �������� ������� ������� � ������ � �������� �����.\n" <<
            "5. �������� ������ � �������� ��������� �����, ��������� ����� ������ �� ��������� ������.\n" <<
            "6. ������������ � ����� �������� ����� ���������� �� ������, ����������� � ��������� ����.\n" <<
            "7. �������� ����� ������� ��� ��������� ����� �� ����� ��������.\n";
        int var;
        int opt;
        string delayedDate;
        string PlaneName;
        string FileName;
        cin >> var;
        switch (var) {

        case 1:
            cout << "������� �������� ��������� �����, � ������� ����� �������� ������ �� ���������� �����: ";
            cin >> binaryFileName; //"flight_records.bin";

            // ��������� ������ �� ���������� �����
            records = readRecordsFromFile(inputTextFileName + ".txt");//"flight_records.txt";
            // �������� ������ � �������� ����
            writeRecordsToBinaryFile(records, binaryFileName + ".bin");
            break;

        case 2:
            cout << "������� �������� �����, � ������� ����� �������� ������ �� ��������� �����: ";
            cin >> outputTextFileName;//"flight_records_output.txt"
            if (outputTextFileName == "flight_records")
            {
                cout << "��������, ������ �������� ����������������, �������� ������.\n" << 
                    "�������� flight_records_output" << endl;
                break;
            }
            // ��������� ������ �� ��������� �����
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

            // �������� ������ �� ��������� ����� � ��������� ���� 
            writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            break;

        case 3:
            cout << "������� �������� �����, �� ��������� ����� ����� ������: ";
            cin >> binaryFileName;
            // ��������� ������ �� ��������� �����
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");
            for (const FlightRecord& record : binaryRecords) {
                cout << "����� ������: " << record.departureLocation << endl;
                cout << "����� �����: " << record.flightNumber << endl;
                cout << "���� �������: " << record.arrivalDate << endl;
                cout << "����� �������: " << record.arrivalTime << endl;
                cout << "�������� (����): " << record.delayHours << endl;
                cout << "------------------------" << endl;
            }
            break;

        case 4:
            cout << "������� �������� �����, ��� ������� ����� ����������� �����������: ";
            cin >> binaryFileName;
            cout << "������� ���������� ����� ������ � �����: ";
            cin >> opt;

            // ��������� ������ �� ��������� �����
            binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

            cout << "����� ������: " << binaryRecords[opt - 1].departureLocation << endl;
            cout << "����� �����: " << binaryRecords[opt - 1].flightNumber << endl;
            cout << "���� �������: " << binaryRecords[opt - 1].arrivalDate << endl;
            cout << "����� �������: " << binaryRecords[opt - 1].arrivalTime << endl;
            cout << "�������� (����): " << binaryRecords[opt - 1].delayHours << endl;
            cout << "------------------------" << endl;
            break;

        case 5:
            cout << "������� �������� �����, ��� ������� ����� ����������� �����������: ";
            cin >> outputTextFileName;
            if (outputTextFileName == "flight_records")
            {
                cout << "��������, ������ �������� ����������������, �������� ������.\n" <<
                    "�������� flight_records_output" << endl;
                break;
            }
            cout << "������� ���������� ����� ������ � �����: ";
            cin >> opt;
            if (opt > records.size())
            {
                cout << "������, �������� ������!";
            }
            else
            {
                // ��������� ������ �� ���������� �����
                records = readRecordsFromFile(inputTextFileName + ".txt");

                deleteRecordByIndex(records, opt - 1);

                for (const FlightRecord& record : records) {
                    cout << "����� ������: " << record.departureLocation << endl;
                    cout << "����� �����: " << record.flightNumber << endl;
                    cout << "���� �������: " << record.arrivalDate << endl;
                    cout << "����� �������: " << record.arrivalTime << endl;
                    cout << "�������� (����): " << record.delayHours << endl;
                    cout << "------------------------" << endl;
                }

                // �������� ������ � �������� ����
                writeRecordsToBinaryFile(records, binaryFileName + ".bin");

                // ��������� ������ �� ��������� �����
                vector<FlightRecord> binaryRecords = readRecordsFromBinaryFile(binaryFileName + ".bin");

                // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
                writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            }
            break;

        case 6:
            cout << "������� �������� ��������� �����, � ������� ����� �������� ������ �� ���������� �����: ";
            cin >> delayedFlightsFileName; //"delayed_flights.bin"
            cout << "������� ����, ������� ��� ���������� (������ ����������: 2022-10-05)" << endl;
            cin >> delayedDate;

            // ��������� ������ �� ���������� �����
            records = readRecordsFromFile(inputTextFileName + ".txt");//"flight_records.txt";

            // ����������� ����� �������� ���� � ������������ ������� �� ��������� ����
            createDelayedFlightsBinaryFile(records, delayedFlightsFileName + ".bin", delayedDate);

            // ��������� ������ �� ��������� �����
            binaryRecords = readRecordsFromBinaryFile(delayedFlightsFileName + ".bin");

            // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
            writeRecordsToTextFile(binaryRecords, outputTextFileName + ".txt");
            break;

        case 7:
            cout << "������� �������� �����, ��� ������� ����� ����������� �����������: ";
            cin >> outputTextFileName;
            if (outputTextFileName == "flight_records")
            {
                cout << "��������, ������ �������� ����������������, �������� ������.\n" <<
                    "�������� flight_records_output" << endl;
                break;
            }
            cout << "������� �����, ������������� ��� ����� (������ ����������: SY101)" << endl;
            cin >> PlaneName;
            cout << "�������, ������������ ��� �����, �� ������� ������ �� �������� (������ ����������: 10:15)" << endl;
            cin >> delayedDate;
            // ��������� ������ �� ���������� �����
            records = readRecordsFromFile(inputTextFileName + ".txt");

            // �������� ����� ������� ��� ��������� �����
            changeArrivalTime(records, PlaneName, delayedDate);

            // �������� ������ �� ��������� ����� � ��������� ���� (��� ��������)
            writeRecordsToTextFile(records, outputTextFileName + ".txt");
            break;

        default:
            break;
        }
    }
}
//flight_records