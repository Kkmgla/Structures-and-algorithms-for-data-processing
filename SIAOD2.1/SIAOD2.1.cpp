#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке;
//файл может быть образцовым или введен пользователем;
void func1(string FileName, int option) {
	if (option == 1) {
		ifstream File(FileName, std::ios::in);
		if (!File.is_open()) {
			cerr << "Не удалось открыть файл." << std::endl;
		}
		else {
			string line;
			while (getline(File, line, '\n')) {
				cout << line << std::endl;
			}
			File.close();
		}
	}
	else {
		ofstream outputFile(FileName, std::ios::out);
		if (!outputFile.is_open()) {
			cerr << "Не удалось открыть файл." << std::endl;
		}
		else {
			int num;
			char choice;
			do {
				cout << "Введите число: " << endl;
				cin >> num;
				cout << "Ввести число " << num << " на следующей строке? " << endl;
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
				{
					outputFile << "\n";
					outputFile << num << " ";
				}
				else {
					outputFile << num << " ";
				}
				cout << "Хотите ввести еще число?" << endl;
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
			outputFile.close();
			cout << "Числа успешно записаны в файл.\n" << endl;
		}
	}
};

//Вывод содержимого текстового файла;
void func2(string FileName) {
	ifstream File(FileName, ios::in);
	if (!File.is_open()) {
		cerr << "Не удалось открыть файл." << std::endl;
	}
	else {
		string line;
		while (getline(File, line, '\n')) {
			cout << line << std::endl;
		}
		File.close();
	}
};

//Добавление новой строки в конец файла;
int func3(string FileName) {
	ofstream outputFile(FileName, ios::app);

	// Проверяем, успешно ли открыт файл
	if (!outputFile.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return 1;
	}
	string line;
	char choice;
	do {
		cout << "Введите строку: ";
		cin.ignore(); // Очищаем буфер ввода
		getline(std::cin, line);

		outputFile << line << '\n';

		cout << "Хотите ввести еще строку? (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	// Закрываем файл после записи
	outputFile.close();

	cout << "Строки успешно записаны в файл." << endl;
};

//Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение;
int func4(string FileName, int position) {
	ifstream inputFile(FileName, std::ios::in);
	if (!inputFile.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return 1;
	}

	vector<int> numbers;
	string line;

	// Читаем строки из файла и извлекаем числа
	while (getline(inputFile, line)) {
		istringstream iss(line);
		int num;

		while (iss >> num) {
			numbers.push_back(num);
		}
	}
	inputFile.close();

	if (position > numbers.size())
	{
		cout << "Ошибка! Числа на такой позиции нет.\n";
		return 0;
	}
	// Выводим числа из вектора
	cout << "Числа из файла:" << endl;
	for (int num : numbers) {
		cout << num << ' ';
	}
	cout << "\nЧисло на " << position << " позиции: " << numbers[position - 1] << endl;
};

//Определить количество чисел в файле.
int func5(string FileName) {
	ifstream inputFile(FileName, std::ios::in);
	if (!inputFile.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return 1;
	}

	vector<int> numbers;
	string line;

	// Читаем строки из файла и извлекаем числа
	while (getline(inputFile, line)) {
		istringstream iss(line);				//istringstream (строковый поток) - это класс в C++, который позволяет считывать данные из строки,
		//как если бы они считывались из стандартного ввода (клавиатуры) или файла.
		//Он является частью библиотеки <sstream>, которая предоставляет механизмы для работы с потоками данных в виде строк.
		int num;

		while (iss >> num) {
			numbers.push_back(num);
		}
	}
	inputFile.close();

	// Выводим числа из вектора
	cout << "Числа из файла:" << endl;
	for (int num : numbers) {
		cout << num << ' ';
	}
	cout << "\nКоличество чисел в файле: " << numbers.size() << endl;
};

//Создать новый файл из значений исходного, переписав в него только простые числа, располагая каждое на отдельной строке текстового файла.
int funcVar25(string FileName) {
	ifstream inputFile("StoredFile.txt", std::ios::in);
	if (!inputFile.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return 1;
	}

	vector<int> numbers;
	string line;

	// Читаем строки из файла и извлекаем числа
	while (getline(inputFile, line)) {
		istringstream iss(line);
		int num;

		while (iss >> num) {
			numbers.push_back(num);
		}
	}
	inputFile.close();

	// Выводим числа из вектора
	cout << "Числа из файла:" << endl;
	for (int num : numbers) {
		cout << num << ' ';
	}

	vector <int> numbersP;
	for (int num : numbers) {
		bool isPrime = true;

		if (num <= 1) {
			isPrime = false;
		}
		else {
			for (int i = 2; i < num; ++i) {
				if (num % i == 0) {
					isPrime = false;
					break;
				}
			}
		}

		if (isPrime) {
			numbersP.push_back(num);
		}
	}
	cout << "\nПростые числа: ";
	for (int num : numbersP) {
		cout << num << ' ';
	}
	ofstream outputFile(FileName, std::ios::out);
	if (!outputFile.is_open()) {
		cerr << "\nНе удалось открыть файл." << std::endl;
	}
	else
	{
		for (int num : numbersP)
		{
			outputFile << num;
			outputFile << "\n";
		}
	}
	cout << endl;
};



int main() {
	setlocale(LC_ALL, "Russian");

	while (1) {
		cout << "Меню:\n" <<
			"1. Cоздание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке.\n" <<
			"2. Bывод содержимого текстового файла.\n" <<
			"3. Добавление новой строки в конец файла.\n" <<
			"4. Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение.\n" <<
			"5. Определить количество чисел в файле.\n" <<
			"6. Создать новый файл из значений исходного, переписав в него только простые числа, располагая каждое на отдельной строке текстового файла.\n";
		int var;
		string FileName;
		cin >> var;
		switch (var) {

		case 1:
			int option;
			cout << "Выберете опцию:\n" <<
				"1. Использовать образцовый файл.\n" <<
				"2. Создать свой.\n";
			cin >> option;
			if (option == 1)
			{
				func1("StoredFile.txt", option);
			}
			else if (option == 2)
			{
				cout << "Введите название файла: \n";
				cin >> FileName;
				if(FileName == "StoredFile") {
					cout << "Извините, данное название зарезервировано." << endl;
					break;
				}
				func1(FileName + ".txt", option);
			}
			else
			{
				cerr << "Ошибка!\n";
				break;
			}
			break;

		case 2:
			cout << "Введите название файла: \n";
			cin >> FileName;
			func2(FileName + ".txt");
			break;

		case 3:
			cout << "Введите название файла: \n";
			cin >> FileName;
			if (FileName == "StoredFile") {
				cout << "Извините, данное название зарезервировано. Редактирование данного файла запрещено, выберете другой файл." << endl;
				break;
			}
			func3(FileName + ".txt");
			break;

		case 4:
			cout << "Введите название файла: \n";
			cin >> FileName;
			int position;
			cout << "укажите порядковый номер числа в файле\n";
			cin >> position;
			func4(FileName + ".txt", position);
			break;

		case 5:
			cout << "Введите название файла: \n";
			cin >> FileName;
			func5(FileName + ".txt");
			break;

		case 6:
			cout << "Введите название файла, в который будут переписываться числа: \n";
			cin >> FileName;
			funcVar25(FileName + ".txt");
			break;

		default:
			break;
		}
	}
}