// Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Общее время работы алгоритма O(n log n)
// 5_4.Закраска прямой 2.
// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка(Li и Ri).
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.

#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <sstream>
template<class T>
bool IsLessDefault(const T& l, const T& r)
{
    return l < r;
}

template<class T>
void MergeArray(T* array_1, T* array_2, T* merged_array, int array_size_1, int array_size_2,
    bool (*IsLessBySomething)(const T& living_time_1, const T& living_time_2) = IsLessDefault)
{
    if ((array_size_1 + array_size_2) == 1)
    {
        merged_array = array_1;
    }

    int array_1_current_element_number = 0,// переменная, отслеживающая текущий индекс элемента 1-ого массива для слияния
        array_2_current_element_number = 0,
        merged_array_current_element_number = 0; // переменная, отслеживающая текущий индекс элемента отсортированного массива
    bool array_1_still_has_elements = true, // переменная, отражающее то, остались ли ещё в массиве элементы для слияния
        array_2_still_has_elements = true;

    while (array_1_still_has_elements || array_2_still_has_elements) // пока хотя бы в одном из исходных массивов есть элементы
    {
        if (IsLessBySomething(array_1[array_1_current_element_number], array_2[array_2_current_element_number]))
        {
            merged_array[merged_array_current_element_number] = array_1[array_1_current_element_number];
            ++array_1_current_element_number;
            if (array_1_current_element_number == (array_size_1))
            {
                array_1_still_has_elements = false;
            }
        }
        else
        {
            merged_array[merged_array_current_element_number] = array_2[array_2_current_element_number];
            ++array_2_current_element_number;
            if (array_2_current_element_number == (array_size_2))
            {
                array_2_still_has_elements = false;
            }
        }
        ++merged_array_current_element_number;
        if (!array_1_still_has_elements) // отработка особого случая, если в первом массиве закончились элементы для слияния
        {
            for (int i = array_2_current_element_number; i < array_size_2; ++i)
            {
                merged_array[merged_array_current_element_number] = array_2[i];
                ++merged_array_current_element_number;
            }
            break; // в конце обработки этого случая происходит выход из цикла
        }
        if (!array_2_still_has_elements) // отработка особого случая, если во втором массиве закончились элементы для слияния
        {
            for (int i = array_1_current_element_number; i < array_size_1; ++i)
            {
                merged_array[merged_array_current_element_number] = array_1[i];
                ++merged_array_current_element_number;
            }
            break; // в конце обработки этого случая происходит выход из цикла
        }
    }
}

template<class T>
void RecurciveMergeSort(T* initial_array, int array_size,
    bool (*IsLessBySomething)(const T& living_time_1, const T& living_time_2) = IsLessDefault)
{
    if (array_size <= 1) // сортировка массива из одного элемента не имеет смысла
    {
        return;
    }
    int left_part_size = array_size / 2;
    int right_part_size = array_size - left_part_size;
    RecurciveMergeSort(initial_array, left_part_size, IsLessBySomething); // рекурсивно сливаем левую часть массива
    RecurciveMergeSort(initial_array + left_part_size, right_part_size, IsLessBySomething); // рекурсивно сливаем правую часть массива
    T* sorted_array = new T[array_size];
    MergeArray(initial_array, initial_array + left_part_size, sorted_array, left_part_size, right_part_size, IsLessBySomething); // непосредственно функция слияния
    memcpy(initial_array, sorted_array, sizeof(T) * array_size);
    delete[] sorted_array;
}

struct LineSegment
{
    int initial_point,
        finish_point;
    LineSegment() : initial_point(0), finish_point(0) {}
    LineSegment(int initial_point, int finish_point) : initial_point(initial_point), finish_point(finish_point) {}
};


// Сортировка по точкам начала отрезков 
bool IsLessByInitialPoint(const LineSegment& line_segment_1, const LineSegment& line_segment_2)
{
    return  line_segment_1.initial_point < line_segment_2.initial_point;
}
// Сортировка по точкам конца отрезков
bool IsLessByFinishPoint(const LineSegment& line_segment_1, const LineSegment& line_segment_2)
{
    return  line_segment_1.finish_point < line_segment_2.finish_point;
}

int CountOneLayerSumLenth(LineSegment* initial_point_sorted_array, int line_segment_count)
{
    LineSegment* finish_point_sorted_array = new LineSegment[line_segment_count];
    memcpy(finish_point_sorted_array, initial_point_sorted_array, sizeof(LineSegment) * line_segment_count);

    RecurciveMergeSort(initial_point_sorted_array, line_segment_count, IsLessByInitialPoint);
    RecurciveMergeSort(finish_point_sorted_array, line_segment_count, IsLessByFinishPoint);

    int one_layer_sum_lenth = 0; // сумма длин частей числовой прямой, окрашенных ровно в 1 слой
    int one_layer_initial_point = 0; // начало отрезка, в пределах которого числовая прямая окражена в 1 слой
    int one_layer_finish_point = 0; // конец отрезка, в пределах которого числовая прямая окражена в 1 слой
    int current_layer_sum = 0; // числов слоёв, в которые окрашена числовая прямая в текущий момент
    int current_element_finish = 0; // счётчик позиции текущего элемента из массива, отсортированного по концам отрезков
    int current_element_initial = 0; // счётчик позиции текущего элемента из массива, отсортированного по началам отрезков
    // перебираем оба массива (один отсортированный по началам отрезков, другой - по концам)
    // объединяем все точки (и точки начал, и точки концов) в одно виртуальное множество (на самом деле точки лежат внутри своих объектов, а объекты в разных массивах)
    // после чего обходим все точки в порядке возрастания 
    // в случае, если точка из множеста начал отрезков, то увеличиваем высоту на 1 и мониторим переход высоты с 1 на 2 и с 0 на 1
    // в случае, если точка из множеста концов отрезков, то уменьшаем высоту на 1 и мониторим переход высоты с 2 на 1 и с 1 на 0
    for (int i = 0; i < (line_segment_count * 2); ++i)
    {
        // в случае, когда алгоритм перебрал все элементы из массива, отсортированного по началам отрезков
        if ((current_element_initial == line_segment_count) || (current_element_finish == (line_segment_count)))
        {
            --current_layer_sum;
            if (current_layer_sum == 1)
            {
                one_layer_initial_point = finish_point_sorted_array[current_element_finish].finish_point;
            }
            else
            {
                if (current_layer_sum == 0)
                {
                    one_layer_sum_lenth += finish_point_sorted_array[current_element_finish].finish_point - one_layer_initial_point;
                }
            }
            ++current_element_finish;
            continue;
        }

        if (initial_point_sorted_array[current_element_initial].initial_point < finish_point_sorted_array[current_element_finish].finish_point)
        {
            ++current_layer_sum;
            if (current_layer_sum == 1)
            {
                one_layer_initial_point = initial_point_sorted_array[current_element_initial].initial_point;
            }
            else
            {
                if (current_layer_sum == 2)
                {
                    one_layer_sum_lenth += initial_point_sorted_array[current_element_initial].initial_point - one_layer_initial_point;
                }
            }
            ++current_element_initial;
        }
        else
        {
            --current_layer_sum;
            if (current_layer_sum == 1)
            {
                one_layer_initial_point = finish_point_sorted_array[current_element_finish].finish_point;
            }
            else
            {
                if (current_layer_sum == 0)
                {
                    one_layer_sum_lenth += finish_point_sorted_array[current_element_finish].finish_point - one_layer_initial_point;
                }
            }
            ++current_element_finish;
        }
    }
    delete[] finish_point_sorted_array;
    return one_layer_sum_lenth;

}


void Run(std::istream& input, std::ostream& output)
{
    int line_segment_count = 0;
    input >> line_segment_count;
    LineSegment* initial_point_sorted_array = new LineSegment[line_segment_count];

    for (int i = 0; i < line_segment_count; ++i)
    {
        input >> initial_point_sorted_array[i].initial_point >> initial_point_sorted_array[i].finish_point;
    }
    output << CountOneLayerSumLenth(initial_point_sorted_array, line_segment_count);
    delete[] initial_point_sorted_array;

}

void TestSolution()
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "3 1 4 7 8 2 5";
        Run(input, output);
        assert(output.str() == "3");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "3 1 4 5 8 3 6";
        Run(input, output);
        assert(output.str() == "5");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "4 1 3 3 5 2 3 3 4";
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 1 3 3 5 2 3 3 4 3 6";
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "6 1 3 3 5 2 3 3 4 3 6 2 3";
        Run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "7 1 3 3 5 2 3 3 4 3 6 2 3 5 6";
        Run(input, output);
        assert(output.str() == "1");
    }
}

int main()
{
    Run(std::cin, std::cout);
    //TestSolution();
    return 0;

}

