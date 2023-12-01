#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <bitset>
#include <queue>
using namespace std;

/***********************************************************************************************************************************************************/

//RLE funcs
string compressRLE(const string& input) {
    string compressed;
    int count = 1;

    for (int i = 1; i <= input.length(); i++) {
        if (i == input.length() || input[i - 1] != input[i]) {
            compressed += to_string(count) + input[i - 1];
            count = 1;
        }
        else {
            count++;
        }
    }

    return compressed;
}

string decompressRLE(const string& input) {
    string decompressed;
    int tmp = 0;
    for (char ch : input)
    {
        if (isdigit(ch))
        {
            tmp = static_cast<int>(ch) - 48;
        }
        else
        {
            for (int i = 0; i < tmp; i++)
            {
                decompressed += ch;
            }
            tmp = 0;
        }
    }
    return decompressed;
}
/***********************************************************************************************************************************************************/

/*Алгоритм LZ77 (Зив и Лемпель [1977]): на каждом шаге выводится тройка (d, l, a), что означает:
сперва повторяется подстрока длины l, ранее встречавшаяся d символов назад, а потом идёт символ a.
Допускается l > d, в этом случае кодируется подстрока с периодическим окончанием.
В конкретных реализациях всё это представляется по-разному, иногда разделяются (d, l) и a.*/
struct LZ77Token {
    //число, представляющее смещение от текущей позиции в буфере поиска к началу буфера. Оно указывает на позицию, где начинается совпадение в предыдущей строке
    int offset;
    //число, обозначающее количество символов, которые совпадают между текущим окном буфера и предыдущим содержимым
    int length;
    //символ, следующий за совпадающим фрагментом. Этот символ добавляется к сжатому потоку
    char nextChar;
};

vector<LZ77Token> compressLZ77(const string& input) {
    vector<LZ77Token> compressed;
    int bufferSize = 100; //размер буфера поиска, который определяет максимальную длину совпадающей подстроки.
    int searchBufferStart = 0; //указывает на текущее положение в строке в буфере поиска.

    while (searchBufferStart < input.length()) {
        //используются для отслеживания наилучшего совпадения (самой длинной подстроки) и его смещения.
        int matchLength = 0;
        int bestOffset = 0;

        for (int offset = 1; offset <= bufferSize && searchBufferStart >= offset; offset++) {
            int i = 0;
               //(               размерные ограничения                     )  (                               сравнение                              )
            while (i < bufferSize && searchBufferStart + i < input.length() && input[searchBufferStart - offset + i] == input[searchBufferStart + i]) {
            //i < bufferSize - проверка на то чтобы "строка совпадения" не превышала размер буфера
            //searchBufferStart + i < input.length() - проверка на глубину поиска (до какого символа можно доходить)
                i++;
            }

            if (i > matchLength) {
                matchLength = i;
                bestOffset = offset;
            }
        }

        LZ77Token token;
        token.offset = bestOffset;
        token.length = matchLength;
        // тернарный оператор
        // если строка не кончилась то записываем следующую букву, если нет - 0
        // втавить иной символ не можем, так как при дешифровке в конец строки добавиться этот сивол
        token.nextChar = (searchBufferStart + matchLength < input.length()) ? input[searchBufferStart + matchLength] : '\0';

        compressed.push_back(token);

        searchBufferStart += (matchLength + 1);
    }

    return compressed;
}

string decompressLZ77(const vector<LZ77Token>& compressed) {
    string decompressed;
    for (const auto& token : compressed) {
        if (token.length == 0) {
            decompressed += token.nextChar;
        }
        else {
            int startPos = decompressed.length() - token.offset;
            for (int i = 0; i < token.length; i++) {
                decompressed += decompressed[startPos + i];
            }
            decompressed += token.nextChar;
        }
    }

    return decompressed;
}
/***********************************************************************************************************************************************************/

/*Другой похожий алгоритм, LZ78 (Зив и Лемпель [1978]),
строит-таки таблицу частовстречающихся подстрок — «словарь» (dictionary)
— но делает он это по мере чтения строки. Словарь хранится в префиксном дереве, что позволяет легко находить самое длинное
продолжение входной строки, уже присутствующее в словаре. При декодировании строится
в точности этот же словарь. В сжатом представлении строки словарь не хранится.
В начале работы в словаре содержится единственный элемент под номером ноль: T0 = ε;
иными словами, префиксное дерево состоит из корня, помеченного номером 0.
На каждом шаге читается самая длинная строка Tj = v, уже имеющаяся в словаре, и выводится её код j;
также читается и выводится следующий символ a. При этом в словарь добавляется новая строка va
— конкатенация только что прочитанной со следующим входным символом.
На префиксном дереве это выглядит так: после вывода очередной пары (j, a) алгоритм
переходит в корень префиксного дерева, и дальше читает столько входных символов, сколько возможно.
Когда очередной символ прочитать нельзя, создаётся новый лист,
при этом выводится номер предыдущей вершины и прочитанный символ.*/
struct LZ78Token {
    //индекс в словаре, который указывает на префикс текущего токена. Префикс представляет собой подстроку, которая была ранее добавлена в словарь.
    int prefixIndex;

    //символ, который добавляется к префиксу для создания нового токена.Следующий символ представляет собой новый символ, который не входит в текущий префикс.
    char nextChar;

    LZ78Token(int index, char ch) : prefixIndex(index), nextChar(ch) {}
};

vector<LZ78Token> compressLZ78(const string& input) {
    //ключ - строка, значением - индекс токена.
    unordered_map<string, int> dictionary;
    vector<LZ78Token> compressed;
    int nextIndex = 1;  // Индекс для новых записей в словаре
    string currentPrefix; //Переменная для формирования текущего токена.

    for (char ch : input) {
        string currentToken = currentPrefix + ch;
        /*unordered_map::find возвращает итератор, указывающий на найденный элемент.
        Если элемент не найден, то find вернет unordered_map::end, что является итератором,
        указывающим за последний элемент контейнера.*/
        if (dictionary.find(currentToken) != dictionary.end()) {
            // Если текущий токен уже в словаре, продолжаем собирать префикс для следующего токена
            currentPrefix = currentToken;
        }
        else {
            // Иначе, добавляем текущий токен в словарь и создаем токен для вывода
            //       (     ключ     ) ( значение )
            dictionary[currentToken] = nextIndex;
            nextIndex++;
            /*Место, объяняющее, почему нам вообше здесь нужна карта, а не например массив,
            с помощью нее мы устанавливаем префиксный индекс (позицию)
                                                    !*/
            compressed.emplace_back(dictionary[currentPrefix], ch);//emplace, а не push, тк у нас есть конструктор

            // Сбрасываем префикс для следующего токена
            currentPrefix = "";
        }
    }

    return compressed;
}

string decompressLZ78(const vector<LZ78Token>& compressed) {
    //ключ - индекс токена, значением - строка.
    unordered_map<int, string> dictionary;
    string decompressed;

    int nextIndex = 1;  // Индекс для новых записей в словаре

    for (const LZ78Token& token : compressed) {
        /*Для каждого токена создается строка entry, объединяя значение в словаре, соответствующее индексу token.prefixIndex, и символ token.nextChar*/
        string entry = dictionary[token.prefixIndex] + token.nextChar;

        dictionary[nextIndex] = entry;
        nextIndex++;
        decompressed += entry;
    }

    return decompressed;
}
/***********************************************************************************************************************************************************/

/*Алгоритм метода Шеннона-Фано — один из первых алгоритмов сжатия,
который впервые сформулировали американские учёные Шеннон и Фано,
и он имеет большое сходство с алгоритмом Хаффмана. Алгоритм основан на частоте повторения.
Так, часто встречающийся символ кодируется кодом меньшей длины, а редко встречающийся — кодом большей длины.
В свою очередь, коды, полученные при кодировании, префиксные.
Это и позволяет однозначно декодировать любую последовательность кодовых слов. Но все это вступление.*/
struct Symbol {
    char symbol;
    double probability;
    string code;  // добавлено поле для хранения кода

    Symbol(char s, double p) : symbol(s), probability(p) {}
};

// Узел для дерева Шеннона-Фано
struct Node {
    char symbol;
    Node* left;
    Node* right;
    Node(char s) : symbol(s), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : symbol('\0'), left(l), right(r) {}
};

// Функция сортировки символов по вероятности в убывающем порядке
bool compareSymbols(const Symbol& a, const Symbol& b) {
    return a.probability > b.probability;
}

// Функция для построения дерева Шеннона-Фано
Node* buildShannonFanoCnT(vector<Symbol>& symbols, string code, int start, int end, double chancesCorrector = 0.5) {
    if (start == end) {
        if (symbols[start].symbol == '\n')
        {
            cout << "Symbol: Enter" << ", Code: " << code << endl;
        }
        else if (symbols[start].symbol == ' ')
        {
            cout << "Symbol: Space" << ", Code: " << code << endl;
        }
        else {
            cout << "Symbol: " << symbols[start].symbol << ", Code: " << code << endl;
        }
        return new Node(symbols[start].symbol);
    }

    double sum = 0.0;
    int mid = start;

    // Находим точку разделения символов
    for (int i = start; i <= end; ++i) {
        sum += symbols[i].probability;
        if (sum >= chancesCorrector) break;
        mid = i;
    }

    // Рекурсивно строим дерево для двух частей
    Node* left = buildShannonFanoCnT(symbols, code + "0", start, mid, chancesCorrector / 2);
    Node* right = buildShannonFanoCnT(symbols, code + "1", mid + 1, end, chancesCorrector / 2);

    return new Node(left, right);
}


// Функция для декодирования текста с использованием дерева Шеннона-Фано
string decodeShannonFano(const string& encodedText, Node* root) {
    string decodedText;
    Node* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        }
        else if (bit == '1') {
            current = current->right;
        }

        if (current->symbol != '\0') {
            // Достигнут лист, добавляем символ к раскодированному тексту
            decodedText += current->symbol;
            current = root; // Возвращаемся в корень для следующего символа
        }
    }

    return decodedText;
}

// Рекурсивная функция для поиска кода символа в дереве Шеннона-Фано
bool findCodeInTree(Node* root, char symbol, string& code) {
    if (root == nullptr) {
        return false;
    }

    if (root->symbol == symbol) {
        return true;
    }

    if (findCodeInTree(root->left, symbol, code)) {
        code = '0' + code;
        return true;
    }

    if (findCodeInTree(root->right, symbol, code)) {
        code = '1' + code;
        return true;
    }

    return false;
}

// Функция для поиска кода символа в дереве Шеннона-Фано
string getCodeForSymbol(Node* root, char symbol) {
    string code;
    if (findCodeInTree(root, symbol, code)) {
        return code;
    }
    else {
        return "Symbol not found in the tree.";
    }
}

// Функция для расчета средней длины кода
double calculateAverageCodeLength(const vector<Symbol>& symbols, const string& input) {
    double averageLength = 0.0;

    for (char ch : input) {
        auto it = find_if(symbols.begin(), symbols.end(), [ch](const Symbol& s) { return s.symbol == ch; });
        if (it != symbols.end()) {
            averageLength += it->code.length();
        }
    }

    return averageLength / input.length();
}

// Функция для расчета дисперсии длины кода
double calculateCodeLengthVariance(const vector<Symbol>& symbols, const string& input, double averageLength) {
    double variance = 0.0;

    for (char ch : input) {
        auto it = find_if(symbols.begin(), symbols.end(), [ch](const Symbol& s) { return s.symbol == ch; });
        if (it != symbols.end()) {
            double difference = it->code.length() - averageLength;
            variance += difference * difference;
        }
    }

    return variance / input.length();
}
/***********************************************************************************************************************************************************/

/*Кодирование Хаффмана – это алгоритм сжатия данных, который формулирует основную идею сжатия файлов.
Мы знаем, что каждый символ хранится в виде последовательности из 0 и 1 и занимает 8 бит.
Это называется кодированием фиксированной длины, поскольку каждый символ использует одинаковое фиксированное количество битов для хранения.
Основная идея заключается в кодировании переменной длины. Мы можем использовать тот факт, что некоторые символы в тексте встречаются чаще,
чем другие, чтобы разработать алгоритм, который будет представлять ту же последовательность символов меньшим количеством битов.
При кодировании переменной длины мы присваиваем символам переменное количество битов в зависимости от частоты их появления в данном тексте.
В конечном итоге некоторые символы могут занимать всего 1 бит, а другие 2 бита, 3 или больше.
Проблема с кодированием переменной длины заключается лишь в последующем декодировании последовательности.*/

struct node
{
    char ch;
    int frequency;
    node* left;
    node* right;

    node(char ch, int freq, node* left, node* right)
        : ch(ch), frequency(freq), left(left), right(right)
    {}
};


struct comp {
    bool operator()(node* l, node* r) { return l->frequency > r->frequency; }
};

void TreePrint(node* root, int level, const unordered_map<char, string>& huffmanCode) {
    if (root != nullptr) {
        TreePrint(root->right, level + 1, huffmanCode);

        for (int i = 0; i < level; i++) {
            cout << "    ";
        }

        if (root->ch != 0) {
            cout << root->ch << " (" << huffmanCode.at(root->ch) << ")\n";
        }
        else {
            cout << "*\n";
        }

        TreePrint(root->left, level + 1, huffmanCode);
    }
}

// Функция заполняет словарь по дереву
void encode(node* root, string str, unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr) return;
    //если листик
    if (!root->left && !root->right) huffmanCode[root->ch] = str;

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode); //на самом деле у второго самого часто встречающегося симовла будет код не 1, а 01
}

char decode(node* root, int& index, int& charsRead, string str)
{
    if (root == nullptr) return 0;

    if (!root->left && !root->right) {
        charsRead++;
        return root->ch;
    }

    index++;

    if (str[index] == '0')
        return decode(root->left, index, charsRead, str);
    else
        return decode(root->right, index, charsRead, str);
}

// Функция для расчета средней длины кода
double calculateAverageCodeLength(const unordered_map<char, string>& huffmanCode, const string& input) {
    double averageLength = 0.0;

    for (char ch : input) {
        averageLength += huffmanCode.at(ch).length();
    }

    return averageLength / input.length();
}

// Функция для расчета дисперсии длины кода
double calculateCodeLengthVariance(const unordered_map<char, string>& huffmanCode, const string& input, double averageLength) {
    double variance = 0.0;

    for (char ch : input) {
        double difference = huffmanCode.at(ch).length() - averageLength;
        variance += difference * difference;
    }

    return variance / input.length();
}
/***********************************************************************************************************************************************************/


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    while (true) {
        cout << "1. Test RLE algorithm"
            << "\n2. Test LZ77 algorithm"
            << "\n3. Test LZ78 algorithm"
            << "\n4. Test Shannon-Fano algorithm"
            << "\n5. Test Haffman algorithm"
            << "\n6. Exit\n";

        string input;
        char opt;
        cout << "Enter your choice: ";
        cin >> opt;

        switch (opt) {
            case '1': {
                bool tmp;                
                cout << "Utilize default text or write it on your own?\n"
                << "0 - Default text\n" << "1 - Own text\n";
                cin >> tmp;

                if (!tmp) {
                    input = "Maaaaaaaaaazda rx";
                }
                else if(tmp)
                {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    cout << "Enter your text: ";
                    getline(cin, input);
                }
                else
                {
                    cout << "No such option\n";
                    break;
                }

                string compressed = compressRLE(input);
                cout << "Original: " << input << "\nOriginal message length: " << input.length() << endl;
                cout << "RLE Compressed: " << compressed << "\nCompressed message length: " << compressed.length() << endl;
                string decompressed = decompressRLE(compressed);
                cout << "RLE Decompressed: " << decompressed << "\nКоэффициент сжатия = " << compressed.length()/input.length() << "\n\n";
                break;
            }
            case '2': {
                bool tmp;
                cout << "Utilize default text or write it on your own?\n"
                    << "0 - Default text\n" << "1 - Own text\n";
                cin >> tmp;

                if (!tmp) input = "101000100101010001011";
                else if (tmp)
                {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    cout << "Enter your text: ";
                    getline(cin, input);
                }
                else
                {
                    cout << "No such option\n";
                }

                vector<LZ77Token> compressed1 = compressLZ77(input);
                cout << "Original: " << input << "\nOriginal message length: " << input.length() << endl;
                cout << "LZ77 Compressed:";
                for (const auto& token : compressed1) {
                    cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ") ";
                }
                cout << "\nCompressed message length: " << compressed1.size() * 3 << endl;

                string decompressed1 = decompressLZ77(compressed1);
                cout << "LZ77 Decompressed: " << decompressed1 << "\n\n\n";
                break;
            }
            case '3': {
                bool tmp;
                cout << "Utilize default text or write it on your own?\n"
                    << "0 - Default text\n" << "1 - Own text\n";
                cin >> tmp;

                if (!tmp) {
                    setlocale(LC_ALL, "Russian");
                    input = "какатанекатанекатата ";
                }
                else if (tmp)
                {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    cout << "Enter your text: ";
                    getline(cin, input);
                }
                else
                {
                    cout << "No such option\n";
                }

                vector<LZ78Token> compressed2 = compressLZ78(input);
                cout << "Original: " << input << "\nOriginal message length: " << input.length() << endl;
                cout << "LZ78 Compressed:";
                for (LZ78Token token : compressed2) {
                    cout << "(" << token.prefixIndex << ", " << token.nextChar << ") ";
                }
                cout << "\nCompressed message length: " << compressed2.size() * 2 << endl;

                string decompressed2 = decompressLZ78(compressed2);
                cout << "LZ78 Decompressed: " << decompressed2 << "\n\n\n";
                break;
            }
            case '4': {
                bool tmp;
                cout << "Utilize default text or write it on your own?\n"
                    << "0 - Default text\n" << "1 - Own text\n";
                cin >> tmp;

                if (!tmp) {
                    ifstream inputfile("txtMessageShannon&Fano.txt");
                    if (!inputfile.is_open()) {
                        cerr << "Error in " << "txtMessageShannon&Fano.txt" << endl;
                        exit(1);
                    }

                    stringstream buffer;
                    buffer << inputfile.rdbuf();
                    input = buffer.str();
                    cout << "Original Text:\n" << buffer.str() << endl;
                }
                else if (tmp)
                {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    cout << "Enter your text: ";
                    getline(cin, input);
                }
                else
                {
                    cout << "No such option\n";
                }

                // Создаем вектор символов и вычисляем их вероятности
                vector<Symbol> symbols;
                map<char, int> charCount;

                for (char ch : input) {
                    charCount[ch]++;
                }

                for (const auto& entry : charCount) {
                    double probability = static_cast<double>(entry.second) / input.length();// Считаем проценты
                    symbols.emplace_back(entry.first, probability);
                }

                // Сортируем символы по вероятности
                sort(symbols.begin(), symbols.end(), compareSymbols);

                // Выводим символы и их вероятности
                cout << "\nSymbols and Probabilities:" << endl;
                for (const auto& symbol : symbols) {
                    if (symbol.symbol == '\n')
                    {
                        cout << "Enter: " << symbol.probability << endl;
                    }
                    else if (symbol.symbol == ' ')
                    {
                        cout << "Space: " << symbol.probability << endl;
                    }
                    else {
                        cout << symbol.symbol << ": " << symbol.probability << endl;
                    }
                }

                cout << "\nShannon-Fano Codes:" << endl;
                Node* shannonFanoTreeRoot = buildShannonFanoCnT(symbols, "", 0, symbols.size() - 1);

                // Формирование строки после кодировки
                string codedMessage;
                for (char ch : input) {
                    string findChar = getCodeForSymbol(shannonFanoTreeRoot, ch);
                    codedMessage += findChar;
                };

                // Декодируем текст
                string decodedMessage = decodeShannonFano(codedMessage, shannonFanoTreeRoot);

                /******************************Блок сжатия*******************************/
                // Записываем сжатый текст в двоичный файл
                string encoded = "";
                string encodedbin = "";
                bitset<8> byte;
                int i = 0;
                int chars = 0;
                for (char ch : input) {
                    string code = getCodeForSymbol(shannonFanoTreeRoot, ch);
                    encoded += code;
                    chars++;
                    for (char ch : code) {
                        bool bit = ch - 48;
                        byte[i] = bit;
                        i++;
                        if (i == 8) {
                            encodedbin += (char)byte.to_ulong(); // Когда набрали 1 байт, записываем его в закодированную строку
                            i = 0;
                            byte.reset();
                        }
                    }
                }
                encodedbin += (char)byte.to_ulong(); // последний неполный байт
                cout << "encoded message: " << encoded << "\nencodedbin message: " << encodedbin << endl;


                int filelen = encodedbin.length();
                ofstream outputfile("encoded.txt", ios::binary | ios::out);
                outputfile.write((char*)&filelen, sizeof(int)); 
                outputfile.write((char*)&chars, sizeof(int)); 
                outputfile << encodedbin;
                outputfile.close();
                // Считываем закодированный двоичный файл
                ifstream inputfile1("encoded.txt", ios::binary);
                int fileLength = 0;
                int charsInFile = 0;
                inputfile1.read((char*)&fileLength, sizeof(int));
                inputfile1.read((char*)&charsInFile, sizeof(int));
                char* encodedFromFile = new char[fileLength];
                inputfile1.read(encodedFromFile, fileLength);
                printf("Tекст сжат в : % .6f раз\nКоэффициент сжатия = % .6f\n", (float)charsInFile / fileLength, (float)fileLength / charsInFile);
                /******************************Блок сжатия*******************************/

                // Обновим коды в объектах Symbol
                for (auto& symbol : symbols) {
                    symbol.code = getCodeForSymbol(shannonFanoTreeRoot, symbol.symbol);
                }
                cout << "Средняя длина кода: " << calculateAverageCodeLength(symbols, input) << endl;
                cout << "Дисперсия длины кода: " << calculateCodeLengthVariance(symbols, input, calculateAverageCodeLength(symbols, input)) << endl;

                // Выводим результат
                cout << "\nDecoded Text:\n" << decodedMessage << endl;

                // Очищаем память
                delete shannonFanoTreeRoot;

                break;
            }
            case '5': {
                bool tmp;
                cout << "Utilize default text or write it on your own?\n"
                    << "0 - Default text\n" << "1 - Own text\n";
                cin >> tmp;

                if (!tmp) {
                    ifstream inputfile("txtMessageHaffmann.txt");
                    if (!inputfile.is_open()) {
                        cerr << "Error in " << "txtMessageHaffmann.txt" << endl;
                        exit(1);
                    }

                    stringstream buffer;
                    buffer << inputfile.rdbuf();
                    input = buffer.str();
                    cout << "Original Text:\n" << buffer.str() << endl;
                }
                else if (tmp)
                {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    cout << "Enter your text: ";
                    getline(cin, input);
                }
                else
                {
                    cout << "No such option\n";
                }

                // Считаем частоту встречи символов
                unordered_map<char, int> charCount;
                for (char ch : input) {
                    charCount[ch]++;
                }

                // Создаем очередь из узлов, сначала редкие
                priority_queue<node*, vector<node*>, comp> pq;
                for (auto pair : charCount) pq.push(new node(pair.first, pair.second, nullptr, nullptr)); // авто сортировка элементов по убыванию

                // Превращаем очередь в дерево
                while (pq.size() != 1)
                {
                    // Два самых редких узла...
                    node* left = pq.top(); pq.pop();
                    node* right = pq.top();	pq.pop();

                    // ... – это новый узел с частотой, равной их сумме
                    pq.push(new node('\0', left->frequency + right->frequency, left, right));
                }

                // Это дерево Хаффмана
                node* root = pq.top();

                // Генерируем коды по дереву и записываем в словарь (map) для удобного получения
                unordered_map<char, string> huffmanCode;
                encode(root, "", huffmanCode);

                cout << "Haffman's tree:\n";
                TreePrint(root, 0, huffmanCode);

                cout << "\nHaffman codes:\n";
                for (auto pair : huffmanCode) {
                    if (pair.first == '\n'){
                        cout << "Enter: " << pair.second << endl;
                    }
                    else if (pair.first == ' '){
                        cout << "Space: " << pair.second << endl;
                    }
                    else {
                        cout << pair.first << ": " << pair.second << endl;
                    }
                }

                /******************************Блок сжатия*******************************/
                // Записываем сжатый текст в двоичный файл
                string encoded = "";
                string encodedbin = "";
                bitset<8> byte;
                int i = 0;
                int chars = 0;
                for (char ch : input) {
                    string code = huffmanCode[ch];
                    encoded += code;
                    chars++;
                    for (char ch : code) {
                        bool bit = ch - 48;
                        byte[i] = bit;
                        i++;
                        if (i == 8) {
                            encodedbin += (char)byte.to_ulong(); // Когда набрали 1 байт, записываем его в закодированную строку
                            i = 0;
                            byte.reset();
                        }
                    }
                }
                encodedbin += (char)byte.to_ulong(); // последний неполный байт
                cout << "\nencoded message: " << encoded << "\nencodedbin message: " << encodedbin << endl;

                int filelen = encodedbin.length();
                ofstream outputfile("encoded.txt", ios::binary | ios::out);
                outputfile.write((char*)&filelen, sizeof(int)); // Единственный способ записать динамическую строку в файл – записать сначала ее размер
                outputfile.write((char*)&chars, sizeof(int)); // Записываем количество закодированных символов, чтобы знать, когда остановить декодирование, иначе будем декодировать незначащие нули в конце
                outputfile << encodedbin;
                outputfile.close();
                // Считываем закодированный двоичный файл
                ifstream inputfile1("encoded.txt", ios::binary);
                int fileLength = 0;
                int charsInFile = 0;
                inputfile1.read((char*)&fileLength, sizeof(int));
                inputfile1.read((char*)&charsInFile, sizeof(int));
                char* encodedFromFile = new char[fileLength];
                inputfile1.read(encodedFromFile, fileLength);
                printf("\nТекст сжат в: %.6f раз\nКоэффициент сжатия = %.6f\n",
                    (float)charsInFile / fileLength, (float)fileLength / charsInFile);
                /******************************Блок сжатия*******************************/
                cout << "Средняя длина кода: " << calculateAverageCodeLength(huffmanCode, input) << endl;
                cout << "Дисперсия длины кода: " << calculateCodeLengthVariance(huffmanCode, input, calculateAverageCodeLength(huffmanCode, input)) << endl;

                int index = -1;
                int charsRead = 0;
                ofstream outputfile1("decoded.txt");
                cout << "\nFINALLY DECODED MESSAGE:\n";
                while ((index < fileLength * 8) && (charsRead < charsInFile)) {
                    char x = decode(root, index, charsRead, encoded);
                    outputfile1 << x;
                    cout << x;
                }
                outputfile1.close();
                cout << "\n\n";


                break;
            }
            case '6': {

                exit(1);
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    return 0;
}