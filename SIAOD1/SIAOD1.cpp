#include <iostream>
#include <string>
using namespace std;

string bitout(unsigned int x, int b)
{
    int xc = x;
    string result;
    for (int i = 0; i < b; i++)
    {
        if (x % 2 == 1) result = "1" + result;
        else result = "0" + result;
        x = x / 2;
    }
    return result + " " + to_string(xc);
}

int task1()
{
    //3 5 11 биты
    int mask = 0x0828; //b 0000 1000 0010 1000
    int x = 0x0316;    //b 0000 0011 0001 0110 
    x = x | mask;
    return x; //b 0000 1011 0011 1110  2878
}

int task2(int x)
{//„етыре младших
    int mask = 0xFFF0; //1111 1111 1111 0000

    x = x & mask;

    return x;
}

int task3(int x)
{//умножение на 128
    return x << 7;
}

int task4(int x)
{//деление на 128
    return x >> 7;
}

int task5(int x, int n)
{//ћаска инициализируетс€ единицей в старшем разр€де (маска 2)
    int mask = 0x8000; // 1000 0000 0000 0000
    //сдвиг единицы на n-ый бит
    mask = mask >> 15 - n;
    x = x | mask; //обнуление бита
    return x;
}

int main()
{
    unsigned short int n;
    int number;
    while (1) {
        cout << "Options:\nSolve task 1\nSolve task 2\nSolve task 3\nSolve task 4\nSolve task 5\n";
        cin >> n;
        switch (n) {
        case 1:
            cout << bitout(0x0316, 16) << endl << bitout(task1(), 16) << endl;
            break;
        case 2:
            cout << "Enter you number: ";
            cin >> number;
            cout << bitout(number, 16) << endl << bitout(task2(number), 16) << endl;
            break;
        case 3:
            cout << "Enter you number: ";
            cin >> number;
            cout << bitout(number, 16) << endl << bitout(task3(number), 16) << endl;
            break;
        case 4:
            cout << "Enter you number: ";
            cin >> number;
            cout << bitout(number, 16) << endl << bitout(task4(number), 16) << endl;
            break;
        case 5:
            cout << "Enter you number: ";
            cin >> number;
            cout << "Enter bit index:";
            int x;
            cin >> x;
            cout << bitout(number, 16) << endl << bitout(task5(number, x), 16) << endl;
            break;
        default:
            cerr << "Wrong number\n";
            break;
        };
    }
}