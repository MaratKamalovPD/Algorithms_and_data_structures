﻿// Задача #1
// Во всех задачах необходимо использование битовых операций
// Использование арифметических операций запрещено
// Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде
// 1.2 Вернуть значение бита в числе N по его номеру K
// Формат входных данных. Число N, номер бита K


#include <iostream>
#include <sstream>
#include <cassert>
short ReturnBitValue(int number, int bit_number)
{
    number = number >> bit_number; // Сдвиг битовых разрядов вправо на bit_number
    return (number & 1); // Выполнение побитового И смещённого числа и единицы
}
void Run(std::istream& input, std::ostream& output)
{
    int N = 0, // См. условие
        k = 0; // См. условие
    input >> N >> k;
    output << ReturnBitValue(N, k);
}

void TestTheSolution()
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "25 3";
        Run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "25 2";
        Run(input, output);
        assert(output.str() == "0");
    }

}


int main()
{
    Run(std::cin, std::cout);
    //TestTheSolution();
    return 0;
}


