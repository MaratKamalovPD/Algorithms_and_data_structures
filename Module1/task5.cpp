// �� ���� ������� ������� ������� ���������� ����������� � ������������ ���������� �������� � ���� ��������� �������.
// ������� ������ ������������ �������� ������� ��������� �������.
// ����� ����� ������ ��������� O(n log n)
// 5_4.�������� ������ 2.
// �� �������� ������ �������� N ��������.
// �������� ���������� ������ � ������� ������ ������� �������(Li � Ri).
// ����� ����� ���� ������ �������� ������, ���������� ����� � ���� ����.

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

    int array_1_current_element_number = 0,// ����������, ������������� ������� ������ �������� 1-��� ������� ��� �������
        array_2_current_element_number = 0,
        merged_array_current_element_number = 0; // ����������, ������������� ������� ������ �������� ���������������� �������
    bool array_1_still_has_elements = true, // ����������, ���������� ��, �������� �� ��� � ������� �������� ��� �������
        array_2_still_has_elements = true;

    while (array_1_still_has_elements || array_2_still_has_elements) // ���� ���� �� � ����� �� �������� �������� ���� ��������
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
        if (!array_1_still_has_elements) // ��������� ������� ������, ���� � ������ ������� ����������� �������� ��� �������
        {
            for (int i = array_2_current_element_number; i < array_size_2; ++i)
            {
                merged_array[merged_array_current_element_number] = array_2[i];
                ++merged_array_current_element_number;
            }
            break; // � ����� ��������� ����� ������ ���������� ����� �� �����
        }
        if (!array_2_still_has_elements) // ��������� ������� ������, ���� �� ������ ������� ����������� �������� ��� �������
        {
            for (int i = array_1_current_element_number; i < array_size_1; ++i)
            {
                merged_array[merged_array_current_element_number] = array_1[i];
                ++merged_array_current_element_number;
            }
            break; // � ����� ��������� ����� ������ ���������� ����� �� �����
        }
    }
}

template<class T>
void RecurciveMergeSort(T* initial_array, int array_size,
    bool (*IsLessBySomething)(const T& living_time_1, const T& living_time_2) = IsLessDefault)
{
    if (array_size <= 1) // ���������� ������� �� ������ �������� �� ����� ������
    {
        return;
    }
    int left_part_size = array_size / 2;
    int right_part_size = array_size - left_part_size;
    RecurciveMergeSort(initial_array, left_part_size, IsLessBySomething); // ���������� ������� ����� ����� �������
    RecurciveMergeSort(initial_array + left_part_size, right_part_size, IsLessBySomething); // ���������� ������� ������ ����� �������
    T* sorted_array = new T[array_size];
    MergeArray(initial_array, initial_array + left_part_size, sorted_array, left_part_size, right_part_size, IsLessBySomething); // ��������������� ������� �������
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


// ���������� �� ������ ������ �������� 
bool IsLessByInitialPoint(const LineSegment& line_segment_1, const LineSegment& line_segment_2)
{
    return  line_segment_1.initial_point < line_segment_2.initial_point;
}
// ���������� �� ������ ����� ��������
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

    int one_layer_sum_lenth = 0; // ����� ���� ������ �������� ������, ���������� ����� � 1 ����
    int one_layer_initial_point = 0; // ������ �������, � �������� �������� �������� ������ �������� � 1 ����
    int one_layer_finish_point = 0; // ����� �������, � �������� �������� �������� ������ �������� � 1 ����
    int current_layer_sum = 0; // ������ ����, � ������� �������� �������� ������ � ������� ������
    int current_element_finish = 0; // ������� ������� �������� �������� �� �������, ���������������� �� ������ ��������
    int current_element_initial = 0; // ������� ������� �������� �������� �� �������, ���������������� �� ������� ��������
    // ���������� ��� ������� (���� ��������������� �� ������� ��������, ������ - �� ������)
    // ���������� ��� ����� (� ����� �����, � ����� ������) � ���� ����������� ��������� (�� ����� ���� ����� ����� ������ ����� ��������, � ������� � ������ ��������)
    // ����� ���� ������� ��� ����� � ������� ����������� 
    // � ������, ���� ����� �� �������� ����� ��������, �� ����������� ������ �� 1 � ��������� ������� ������ � 1 �� 2 � � 0 �� 1
    // � ������, ���� ����� �� �������� ������ ��������, �� ��������� ������ �� 1 � ��������� ������� ������ � 2 �� 1 � � 1 �� 0
    for (int i = 0; i < (line_segment_count * 2); ++i)
    {
        // � ������, ����� �������� �������� ��� �������� �� �������, ���������������� �� ������� ��������
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

