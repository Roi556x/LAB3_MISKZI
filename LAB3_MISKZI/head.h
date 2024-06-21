#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
// Функция для вывода 8-битного числа в двоичном формате
void print_bits(uint8_t bits) 
{
    int N(8);
    for (int i = N - 1; i >= 0; i--) {
        if (bits & ((uint8_t)1 << i))
            cout << "1";
        else
            cout << "0";
    }
    cout << endl;
}

// Функция для вывода одномерного вектора
void print_vector(const vector<uint8_t>& vect)
{
    for (long unsigned int i = 0; i < vect.size(); i++) {
        cout << hex << setfill('0') << setw(2) << (int)vect[i] << " ";
    }
    cout << endl;
}

// Функция для вывода двумерного вектора
void print_vector(const vector<vector<uint8_t> >& vect)
{
    for (long unsigned int i = 0; i < vect.size(); i++) {
        for (long unsigned int j = 0; j < vect[i].size(); j++)
            cout << hex << setfill('0') << setw(2) << (int)vect[i][j] << " ";
        cout << endl;
    }
}

// Функция для циклического сдвига байта вправо на p бит
uint8_t circle_step(uint8_t byte, int p)
{
    return (byte << (4 - p));
}

// Функция для создания таблицы подстановки S2 из таблицы S
vector<vector<uint8_t> > create_S2(const vector<uint8_t>& S)
{
    vector<vector<uint8_t> > S2;
    for (long unsigned int i = 0; i < S.size(); i++) {
        vector<uint8_t> help_vector;
        for (long unsigned int j = 0; j < S.size(); j++) {
            help_vector.push_back(((uint8_t)S[i] << 4) + S[j]);
        }
        S2.push_back(help_vector);
    }
    return S2;
}

// Функция для создания таблицы подстановки S3 из таблицы S2 с использованием циклического сдвига
vector<vector<uint8_t> > create_S3(const vector<vector<uint8_t> >& S)
{
    vector<vector<uint8_t> > S2;
    for (long unsigned int i = 0; i < S.size(); i++) {
        vector<uint8_t> help_vector;
        for (long unsigned int j = 0; j < S[i].size(); j++) {
            help_vector.push_back(circle_step(S[i][j], 4)); // Сдвиг на 4 бита
        }
        S2.push_back(help_vector);
    }
    return S2;
}
