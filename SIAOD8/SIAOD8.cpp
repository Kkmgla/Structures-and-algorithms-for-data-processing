#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

struct Result {
public:
    int intValue;
    string stringValue;
};

struct MatrixStruct {
    vector<vector<int>> matrix;
    int rows;
    int cols;

    // Конструктор для создания матрицы с элементами от 0 и до конца матрицы
    MatrixStruct(int rows, int cols)
        : rows(rows), cols(cols), matrix(rows, vector<int>(cols)) {
        int value = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = value++;
            }
        }
    }

    // Метод перемножения двух матриц
    static MatrixStruct multiply(const MatrixStruct& mat1, const MatrixStruct& mat2) {
        // Проверка возможности умножения
        if (mat1.cols != mat2.rows) {
            std::cerr << "Error: Incompatible matrix dimensions for multiplication.\n";
            return MatrixStruct(0, 0);
        }

        MatrixStruct result(mat1.rows, mat2.cols);

        for (int i = 0; i < mat1.rows; ++i) {
            for (int j = 0; j < mat2.cols; ++j) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < mat1.cols; ++k) {
                    result.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
                }
            }
        }

        return result;
    }

    // Пример оператора вывода для удобного отображения матрицы
    friend std::ostream& operator<<(std::ostream& os, const MatrixStruct& mat) {
        for (const auto& row : mat.matrix) {
            for (int element : row) {
                os << element << "\t";
            }
            os << "\n";
        }
        return os;
    }


    /* Cравнение будет происходить только по rows и cols, и если хотя бы одно из них не совпадает, объекты считаются различными.*/
    // Оператор сравнения для сравнения двух объектов MatrixStruct
    bool operator<(const MatrixStruct& other) const {
        if (rows != other.rows) {
            return rows < other.rows;
        }
        if (cols != other.cols) {
            return cols < other.cols;
        }
        // Сравнение элементов матрицы
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    return matrix[i][j] < other.matrix[i][j];
                }
            }
        }
        // Если все значения равны, то объекты равны
        return false;
    }

    // Оператор сравнения для проверки равенства двух объектов MatrixStruct
    bool operator==(const MatrixStruct& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        // Проверка значений элементов матрицы
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    return false;
                }
            }
        }
        // Если все значения равны, то объекты равны
        return true;
    }

};

void printMatrix(const vector<MatrixStruct>& matrixVector) {
    if (matrixVector.size() != 0) {
        char currentLetter = 'A';

        for (const auto& matrixStruct : matrixVector) {
            cout << "Matrix " << currentLetter << ": Rows: " << matrixStruct.rows << ", Cols: " << matrixStruct.cols << endl;
            for (const auto& row : matrixStruct.matrix) {
                for (const auto& element : row) {
                    cout << " " << element << "\t";
                }
                cout << endl;
            }
            cout << "===========================================================" << endl;  // Разделитель между матрицами
            currentLetter++;
        }
    }
    else {
        cout << "There is no single matrix yet\n";
    }
}

Result maximizeScalarMultiplications(vector<MatrixStruct>& matrixVector, int result, string str, map<MatrixStruct, string>& MatrixCharMap) {
    Result r;
    r.intValue = result;
    r.stringValue = str;


    // Проверки
    if (matrixVector.size() == 0){
        cout << "There is no single matrix yet\n";
        return r;
        }
    if (matrixVector.size() == 1) {
        
        cout << "Great luck! The greedy algorithm worked, and all matrices were multiplied\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += it->second;
        }
        r.stringValue = val;
        return r;
    }

    // Лучший результат проходки и на что происходило умножение
    vector<pair<int, int>> localMaximizeScalarMultiplications;

    // Поиск лучшего локального результата
    for (int i = 0; i < matrixVector.size(); i++) {
        localMaximizeScalarMultiplications.push_back(make_pair(0, 0));
        for (int y = 0; y < matrixVector.size(); y++) {
            if ((y != i) && (matrixVector[i].cols == matrixVector[y].rows) &&
                ((matrixVector[i].cols * matrixVector[i].rows * matrixVector[y].cols) > localMaximizeScalarMultiplications[i].first)) {
                localMaximizeScalarMultiplications[i].first =
                    matrixVector[i].cols * matrixVector[i].rows * matrixVector[y].cols;
                localMaximizeScalarMultiplications[i].second = y;
            }
        }
    }

    // Проверка на то, стоит ли вообще продолжать (2x2, 5x5); дальше перемножений не будет
    bool out = false;
    for (int i = 0; i < localMaximizeScalarMultiplications.size(); i++) {
        if (localMaximizeScalarMultiplications[i].first != 0) {
            out = true;
        }
    }
    if (!out) {
        cout << "Bad luck! The greedy algorithm worked, but as a result of its execution we were unable to obtain the one matrix remaining after multiplication\n" <<
        "Since the expected algorithm is built on the principle of choosing the best local option, without thinking about future steps, such an outcome is quite likely\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += it->second + "; ";
        }
        r.stringValue = val;
        return r;
    }

    // Поиск максимального значения первого элемента вектора пар
    auto maxElement = max_element(localMaximizeScalarMultiplications.begin(), localMaximizeScalarMultiplications.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
        });

    // Проверка, найден ли максимальный элемент
    int position = 0;
    if (maxElement != localMaximizeScalarMultiplications.end()) {
        // Получение позиции (индекса) элемента
        position = distance(localMaximizeScalarMultiplications.begin(), maxElement);

        //cout << "Max element: " << maxElement->first                                                        // макс кол-во умножений
            //<< "\nIndex of the matrix in matrixVector by which we need to multiply: " << maxElement->second // индекс матрицы в matrixVector на которую нам нужно умножать
            //<< "\nIndex of the matrix in matrixVector to be multiplied by second: " << position << endl;    // индекс матрицы в matrixVector, которую нужно умножать на second
        // то есть умножив position на maxElement->second мы получим лучший локальный результат – maxElement->first  
    }
    else {
        //cout << "Vector is empty." << endl;
        cout << "Bad luck! The greedy algorithm worked, but as a result of its execution we were unable to obtain the one matrix remaining after multiplication\n" <<
            "Since the expected algorithm is built on the principle of choosing the best local option, without thinking about future steps, such an outcome is quite likely\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += ", " + it->second;
        }
        r.stringValue = val;
        return r;
    }

    // Типа умножили и получили новую матрицу
    MatrixStruct matrixStruct = MatrixStruct::multiply(matrixVector[position], matrixVector[maxElement->second]);

    // Добавили в вектор
    matrixVector.push_back(matrixStruct);

    string tmmmp = "(" + MatrixCharMap[matrixVector[position]] + " * " + MatrixCharMap[matrixVector[maxElement->second]] + ")";
    MatrixCharMap.erase(matrixVector[position]);
    MatrixCharMap.erase(matrixVector[maxElement->second]);
    MatrixCharMap[matrixVector.back()] = tmmmp;


    // Индексы элементов, которые нужно удалить
    // Две матрицы, между которыми происходит умножение
    vector<int> indicesToDelete;
    if (maxElement->second > position)
    {
        indicesToDelete = { position,  maxElement->second };
    }
    else
    {
        indicesToDelete = { maxElement->second, position };
    }

    // Удаление элементов по индексам
    for (auto it = indicesToDelete.rbegin(); it != indicesToDelete.rend(); ++it) {
        size_t indexToRemove = *it;

        if (indexToRemove < matrixVector.size()) {
            matrixVector.erase(matrixVector.begin() + indexToRemove);
        }
    }

    // Рекурсивный вызов функции
    return maximizeScalarMultiplications(matrixVector, maxElement->first + r.intValue, r.stringValue, MatrixCharMap);
}

Result vLob(vector<MatrixStruct>& matrixVector, int result, string str, map<MatrixStruct, string>& MatrixCharMap) {
  
    Result r;
    r.intValue = result;
    r.stringValue = str;


    // Проверки
    if (matrixVector.size() == 0) {
        cout << "There is no single matrix yet\n";
        return r;
    }
    if (matrixVector.size() == 1) {

        cout << "Great luck! The 'V lob' algorithm worked, and all matrices were multiplied\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += it->second;
        }
        r.stringValue = val;
        return r;
    }

    // Лучший результат проходки и на что происходило умножение
    vector<pair<int, int>> localMaximizeScalarMultiplications;

    bool flag = false;
    // Поиск лучшего локального результата
    for (int i = 0; i < matrixVector.size(); i++) {
        if (flag)
        {
            break;
        }
        localMaximizeScalarMultiplications.push_back(make_pair(0, 0));
        for (int y = 0; y < matrixVector.size(); y++) {
            if ((y != i) && (matrixVector[i].cols == matrixVector[y].rows) && ((matrixVector[i].cols * matrixVector[i].rows * matrixVector[y].cols) > localMaximizeScalarMultiplications[i].first)) {
                localMaximizeScalarMultiplications[i].first = matrixVector[i].cols * matrixVector[i].rows * matrixVector[y].cols;
                localMaximizeScalarMultiplications[i].second = y;

                //нашли первую подходящую матрицу
                flag = 1;
                break;
            }
        }
    }

    // Проверка на то, стоит ли вообще продолжать (2x2, 5x5); дальше перемножений не будет
    bool out = false;
    for (int i = 0; i < localMaximizeScalarMultiplications.size(); i++) {
        if (localMaximizeScalarMultiplications[i].first != 0) {
            out = true;
        }
    }
    if (!out) {
        cout << "Bad luck! The greedy algorithm worked, but as a result of its execution we were unable to obtain the one matrix remaining after multiplication\n" <<
            "Considering that we took the first matrices that came across that fit each other in terms of, such an outcome is quite likely\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += it->second + "; ";
        }
        r.stringValue = val;
        return r;
    }

    // Поиск максимального значения первого элемента вектора пар
    auto maxElement = max_element(localMaximizeScalarMultiplications.begin(), localMaximizeScalarMultiplications.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
        });

    // Проверка, найден ли максимальный элемент
    int position = 0;
    if (maxElement != localMaximizeScalarMultiplications.end()) {
        // Получение позиции (индекса) элемента
        position = distance(localMaximizeScalarMultiplications.begin(), maxElement);

        //cout << "Max element: " << maxElement->first                                                        // макс кол-во умножений
            //<< "\nIndex of the matrix in matrixVector by which we need to multiply: " << maxElement->second // индекс матрицы в matrixVector на которую нам нужно умножать
            //<< "\nIndex of the matrix in matrixVector to be multiplied by second: " << position << endl;    // индекс матрицы в matrixVector, которую нужно умножать на second
        // то есть умножив position на maxElement->second мы получим лучший локальный результат – maxElement->first  
    }
    else {
        //cout << "Vector is empty." << endl;
        cout << "Bad luck! The greedy algorithm worked, but as a result of its execution we were unable to obtain the one matrix remaining after multiplication\n" <<
            "Considering that we took the first matrices that came across that fit each other in terms of, such an outcome is quite likely\n";
        r.intValue = result;
        string val = "";
        for (auto it = MatrixCharMap.begin(); it != MatrixCharMap.end(); ++it) {
            val += ", " + it->second;
        }
        r.stringValue = val;
        return r;
    }

    // Типа умножили и получили новую матрицу
    MatrixStruct matrixStruct = MatrixStruct::multiply(matrixVector[position], matrixVector[maxElement->second]);
    
    // Добавили в вектор
    matrixVector.push_back(matrixStruct);
    
    string tmmmp = "(" + MatrixCharMap[matrixVector[position]] + " * " + MatrixCharMap[matrixVector[maxElement->second]] + ")";
    MatrixCharMap.erase(matrixVector[position]);
    MatrixCharMap.erase(matrixVector[maxElement->second]);
    MatrixCharMap[matrixVector.back()] = tmmmp;


    // Индексы элементов, которые нужно удалить
    // Две матрицы, между которыми происходит умножение
    vector<int> indicesToDelete;
    if (maxElement->second > position)
    {
        indicesToDelete = { position,  maxElement->second };
    }
    else
    {
        indicesToDelete = { maxElement->second, position };
    }

    // Удаление элементов по индексам
    for (auto it = indicesToDelete.rbegin(); it != indicesToDelete.rend(); ++it) {
        size_t indexToRemove = *it;

        if (indexToRemove < matrixVector.size()) {
            matrixVector.erase(matrixVector.begin() + indexToRemove);
        }
    }

    // Рекурсивный вызов функции
    return vLob(matrixVector, maxElement->first + r.intValue, r.stringValue, MatrixCharMap);
}

int main() {
    enum AlphabeticIndex {
        A = 'A', B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    };

    vector<MatrixStruct> matrixVector;
    int row, col;
    AlphabeticIndex currentLetter = A;  // Используем буквенное обозначение вместо числа
    while (true) {
        cout << "1. Greedy algorithm"
            << "\n2. V lob algorithm"
            << "\n3. Add new matrix"
            << "\n4. Print all matrices"
            << "\n5. Exit"<< endl;

        char opt;
        char tmp;
        Result r;
        cout << "Enter your choice: ";
        cin >> opt;

        switch (opt) {
        case '1': {
            //крайний вариант на случай если у нас матрицы одинакового размера
            map<MatrixStruct, tuple<string, string, string>> MatrixTupleCharMap;
            map<MatrixStruct, string> MatrixCharMap;
            char currentLetter = 'A';

            for  (const auto &m : matrixVector)
            {
                MatrixCharMap[m] = currentLetter;
                currentLetter++;
            }

            r = maximizeScalarMultiplications(matrixVector, 0, " ", MatrixCharMap);
            cout << "The maximum number number of multiplications of the specified matrices, using Greedy algorithm: " << r.intValue <<
                "\nMathematical expressions that we received as a result of multiplication of matrices: " << r.stringValue << endl;
            break;
        }
        case '2': {
            map<MatrixStruct, string> MatrixCharMap;
            char currentLetter = 'A';

            for (const auto& m : matrixVector)
            {
                MatrixCharMap[m] = currentLetter;
                currentLetter++;
            }

            r = vLob(matrixVector, 0, " ", MatrixCharMap);
            cout << "The maximum number number of multiplications of the specified matrices, using 'V lob' algorithm: " << r.intValue <<
                "\nMathematical expressions that we received as a result of multiplication of matrices: " << r.stringValue << endl;
            break;
        }
        case '3': {

            int i = 0;
            bool y = true;


            while (true) {

                cout << "Enter sizes of the " << static_cast<char>(currentLetter) << " matrix (row>>col): ";
                cin >> row >> col;

                if (row > 0 && col > 0) {
                    MatrixStruct matrixStruct(row, col);
                    matrixVector.push_back(matrixStruct);
                }
                else
                    cout << "Error input!\n";

                currentLetter = static_cast<AlphabeticIndex>(currentLetter + 1);

                cout << "Create a new matrix? (1/0)\n";
                cin >> y;
                if (!y)
                    break;
                if (y)
                    continue;
                else
                    break;
            }
            break;
        }
        case '4': {
            printMatrix(matrixVector);
            break;
        }
        case '5': {
            exit(1);
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    }
    return 0;
}