﻿// 2_2. Дан массив целых чисел А[0..n-1].
// Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. 
// Найти m за O(log m). 
// Требования:  Время работы O(log m).
// Внимание!В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// 2 ≤ n ≤ 10000.



#include <iostream>
#include <sstream>
#include <cassert>

int FindInflectionPointPosition(int* array_instance, int start_position, int end_position)
{
    if (array_instance[end_position] > array_instance[end_position - 1])
    {
        return end_position;
    }
    int middle_element_position = (start_position + end_position) / 2; // позиция элемента из середины интервала
    int counter = 0;
    while (counter < 32)
    {
        if ((array_instance[middle_element_position] > array_instance[middle_element_position - 1]) && (array_instance[middle_element_position] > array_instance[middle_element_position + 1]))
        {
            return middle_element_position;
        }
        else
        {
            if ((array_instance[middle_element_position] > array_instance[middle_element_position - 1]) && (array_instance[middle_element_position] < array_instance[middle_element_position + 1]))
            {
                start_position = middle_element_position + 1;
                middle_element_position = (middle_element_position + end_position) / 2;
            }
            else
            {
                if ((array_instance[middle_element_position] < array_instance[middle_element_position - 1]) && (array_instance[middle_element_position] > array_instance[middle_element_position + 1]))
                {
                    end_position = middle_element_position;
                    middle_element_position = (start_position + middle_element_position) / 2;
                }
            }
        }
        ++counter;
    }
}

int DoExponentialSearch(int array_size, int* array_instance)
{
    int start_position = 0, // позиция элемента в массиве: начало интервала, в котором будет происходить бинарный поиск
        end_position = 0, // позиция элемента в массиве: конец интервала в котором будет происходить бинарный поиск
        pow_variable = 0; // степень двойки

    for (int i = 1; i < array_size; i = i * 2) // проходимся по интервалам 1..2, 2..4, 4..8 и т.д. и смотрим, содержат ли они точку перегиба 
    {
        start_position = i / 2;
        end_position = i;
        if (array_instance[start_position] > array_instance[end_position])
        {
            break;
        }
        else
        {
            end_position = (array_size - 1);
        }
    }
    return FindInflectionPointPosition(array_instance, start_position, end_position);
}


void Run(std::istream& input, std::ostream& output)
{
    int array_size = 0; // размер массива
    input >> array_size;
    int* array_instance = new int[array_size];
    int* dub = array_instance; // вспомогательный указатель, необходимый для извлечения массива чисел из istream
    // | | | синтаксическая конструкция взята из следующего ресурса: https://stackoverflow.com/questions/40787522/get-several-integer-numbers-with-c-cin-and-put-them-into-array
    // v v v
    while (input >> *dub++ and dub != array_size + array_instance); // записываем числа из istream в массив
    /*for (int i = 0; i < array_size; i++) {
        input >> dub;
        array_instance[i] = dub;
    }*/
    output << DoExponentialSearch(array_size, array_instance);
    delete[] array_instance;
}

void TestTheSolution()
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "10 1 2 3 4 5 6 7 6 5 4"; // тестовый вариант из задания
        Run(input, output);
        assert(output.str() == "6");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "7 1 2 3 4 3 2 1"; // симметричное расположение точки перегиба
        Run(input, output);
        assert(output.str() == "3");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "12 1 2 3 4 5 6 7 8 9 10 11 3 "; // точка перегиба - предпоследний элемент
        Run(input, output);
        assert(output.str() == "10");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "12 1 10 9 8 7 6 5 4 3 2 1 0"; // точка перегиба - второй элемент с начала
        Run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 1 2";  // массив из двух элементов, точка перегиба - второй элемент
        Run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 2 1";  // массив из двух элементов, точка перегиба - первый элемент
        Run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 -1 -2";  // массив из двух элементов, точка перегиба - первый элемент (отрицательные числа)
        Run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 -2 -1";  // массив из двух элементов, точка перегиба - второй элемент (отрицательные числа)
        Run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "10 1 2 3 4 5 6 7 8 9"; // массив более чем из двух элементов, точка перегиба - последний элемент
        Run(input, output);
        assert(output.str() == "8");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "10 9 8 7 6 5 4 3 2 1"; // массив более чем из двух элементов, точка перегиба - первый элемент
        Run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "12 7 8 10 9 8 7 6 5 4 3 2 1"; // массив более чем из двух элементов, точка перегиба - третий элемент
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 -1 2 3 2 -1"; // симметричное расположение точки перегиба (с отрицательными числами)
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 -3 -2 -1 -2 -3"; // симметричное расположение точки перегиба (только отрицательные числа)
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1"; // точка перегиба лежит на 0 позиции
        Run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 15 16 14 13 12 11 10 9 8 7 6 5 4 3 2 1"; // точка перегиба лежит на 1 позиции
        Run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 14 15 16 13 12 11 10 9 8 7 6 5 4 3 2 1"; // точки перегиба лежит на 2 позиции
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 13 14 15 16 12 11 10 9 8 7 6 5 4 3 2 1"; // точка перегиба лежит на 3 позиции
        Run(input, output);
        assert(output.str() == "3");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 12 13 14 15 16 11 10 9 8 7 6 5 4 3 2 1"; // точки перегиба лежит на 4 позиции
        Run(input, output);
        assert(output.str() == "4");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 11 12 13 14 15 16 10 9 8 7 6 5 4 3 2 1"; // точка перегиба лежит на 5 позиции
        Run(input, output);
        assert(output.str() == "5");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 9 10 11 12 13 14 15 16 8 7 6 5 4 3 2 1"; // точки перегиба лежит на 7 позиции
        Run(input, output);
        assert(output.str() == "7");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 8 9 10 11 12 13 14 15 16 7 6 5 4 3 2 1"; // точка перегиба лежит на 8 позиции
        Run(input, output);
        assert(output.str() == "8");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 7 8 9 10 11 12 13 14 15 16 6 5 4 3 2 1"; // точки перегиба лежит на 9 позиции
        Run(input, output);
        assert(output.str() == "9");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "16 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"; // точка перегиба лежит на 15 позиции
        Run(input, output);
        assert(output.str() == "15");
    }

    {
        std::stringstream output;
        std::stringstream input; // массив из 16 элементов, где точки перегиба лежать на границах точке экспоненциального поиска и рядом с ними
        input << "32 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32"; // точка перегиба лежит на 15 позиции
        Run(input, output);
        assert(output.str() == "31");
    }
}


int main()
{
    Run(std::cin, std::cout);
    //TestTheSolution(); 
    return 0;
}