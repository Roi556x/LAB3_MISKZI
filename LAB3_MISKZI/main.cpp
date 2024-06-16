#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "head.h"
using namespace std;
int main()
{
    // Значения таблицы S и сдвига p на свои
    vector<uint8_t> S = { 0x8, 0x2, 0xB, 0x3, 0x5, 0xA, 0xD, 0xE, 0x1, 0xF, 0x7, 0x4, 0xC, 0x9, 0x6, 0x0};
    vector<uint8_t> input_16 = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
    vector<uint8_t> input_8 = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    vector<uint8_t> output;
    int p = 4; // Значение сдвига
    vector<vector<uint8_t>> S2 = create_S2(S); // Создание таблицы S*
    vector<vector<uint8_t>> S3 = create_S3(S2); // Создание таблицы S'

    // Вывод таблицы подстановки S
    cout << "Таблица замен S:" << endl;
    print_vector(S);
    cout << endl;

    cout << "Таблица замен input_16:" << endl;
    print_vector(input_16);
    cout << endl;

    cout << "Таблица замен input_8:" << endl;
    print_vector(input_8);
    cout << endl;

    // Вывод таблицы подстановки S*
    cout << "Таблица замен S*:" << endl;
    print_vector(S2);
    cout << endl;

    // Вывод таблицы подстановки S'
    cout << "Таблица замен S':" << endl;
    print_vector(S3);
    cout << endl;

    // 1) Реализация операции подстановки для 4-битного вектора
    cout << "1)Операция замены 8-битного вектора:" << endl;
    cout << "   Input vector:  ";
    print_vector(input_8);
    for (long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S[input_8[i]]);
    }
    cout << "   Output vector: ";
    print_vector(output);
    output.clear();
    cout << endl;

    // 2) Реализация подстановки двух смежных 4-битных векторов с использованием таблицы S*
    cout << "2) Замена двух соседних 4-битных векторов с помощью таблицы S*:" << endl;
    cout << "   Input vector:  ";
    print_vector(input_16);
    for (long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S2[input_8[i] & 0x0F][circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "   Output vector: ";
    print_vector(output);
    output.clear();
    cout << endl;

    // 3) Реализация операции перестановки над 8-битным вектором с использованием циклического сдвига
    cout << "3) Операция перестановки 8-битного вектора с использованием циклического сдвига:" << endl;
    cout << "   Input vector:  ";
    print_vector(input_8);
    for (long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(input_8[i] & 0x0F);
        output.push_back(circle_step(input_8[i], p) & 0x0F);
    }
    cout << "   Output vector: ";
    print_vector(output);
    output.clear();
    cout << endl;

    // 4) Реализация комбинации операций подстановки и перестановки
    cout << "4) Сочетание операций замены и перестановки :" << endl;
    cout << "   Input vector:  ";
    print_vector(input_8);
    for (long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S[input_8[i] & 0x0F]);
        output.push_back(S[circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "   Output vector: ";
    print_vector(output);
    output.clear();
    cout << endl;

    // 5) Преобразование файла с использованием преобразования из п. 4
    cout << "5) Трансформация файла с помощью трансформации из пункта 4:" << endl;
    cout << "   чтение из '1.txt', запись в '2.txt'" << endl;
    ifstream file_1("1.txt", ios::binary | ios::in);
    ofstream file_2("2.txt", ios::binary | ios::out);
    if (!file_1.is_open() || !file_2.is_open()) {
        cerr << "   Ошибка открытия файла!" << endl;
    } else {
        char byte_out;
        while (file_1.get(byte_out)) {
            uint8_t byte_in;
            byte_in = (S[(byte_out & 0x0F)] << p) | S[(circle_step(byte_out, p) & 0x0F)];
            file_2.write((char*)&byte_in, sizeof(char));
        }
        cout << "   Преобразование файла завершено." << endl;
    }
    file_1.close();
    file_2.close();
    cout << endl;

    // 6) Реализация комбинации операций подстановки и перестановки с использованием эквивалентной подстановки S'
    cout << "6) Сочетание операций замены и перестановки с использованием эквивалентной замены S':" << endl;
    cout << "   Input vector:  ";
    print_vector(input_16);
    for (long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S3[input_8[i] & 0x0F][circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "   Output vector: ";
    print_vector(output);
    output.clear();
    cout << endl;

    // 7) Преобразование файла с использованием эквивалентной подстановки из п. 6
    cout << "7) Преобразование файла с использованием эквивалентной замены из пункта 6:" << endl;
    cout << "   Чтение из '3.txt', запись в '4.txt'" << endl;
    ifstream file_3("3.txt", ios::binary | ios::in);
    ofstream file_4("4.txt", ios::binary | ios::out);
    if (!file_3.is_open() || !file_4.is_open()) {
        cerr << "   Error opening file!" << endl;
    } else {
        char byte_out;
        while (file_3.get(byte_out)) {
            uint8_t byte_in;
            byte_in = S3[byte_out & 0x0F][circle_step(byte_out, p) & 0x0F];
            file_4.write((char*)&byte_in, sizeof(char));
        }
        cout << "   Преобразование файла завершено." << endl;
    }
    file_3.close();
    file_4.close();
    cout << endl;

    return 0;
}