// Задача 6
// Дано множество целых чисел из [0..10^9] размера n. 
// Используя алгоритм поиска k - ой порядковой статистики, требуется найти следующие параметры множества :
// 10 % перцентиль
// медиана
// 90 % перцентиль

// Требования: 
// К дополнительной памяти : O(n).
// Среднее время работы : O(n)
// Должна быть отдельно выделенная функция partition.
// Рекурсия запрещена.
// Решение должно поддерживать передачу функции сравнения снаружи.

// Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.Описание для случая прохода от начала массива к концу :
// Выбирается опорный элемент.Опорный элемент меняется с последним элементом массива.
// Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
// Затем располагаются элементы, строго бОльшие опорного.В конце массива лежат нерассмотренные элементы.
// Последним элементом лежит опорный.
// Итератор(индекс) i указывает на начало группы элементов, строго бОльших опорного.
// Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
// Шаг алгоритма.Рассматривается элемент, на который указывает j.Если он больше опорного, то сдвигаем j.
// Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
// В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.


// 6_3.
// Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.


#include<iostream>
#include<cassert>
#include<memory>
#include <sstream>

template <typename T>
bool IsGreaterByDefault(const T& operand_1, const T& operand_2)
{
	return operand_1 > operand_2;
}

int GetRandomIndex(int array_size)
{
	int lower_border = 0;
	int upper_border = array_size - 1;
	int random_index = std::rand() % (upper_border - lower_border + 1) + lower_border;
	return random_index;
}

int Partition(int* array_instance, int array_size, bool IsGreater(const int&, const int&) = IsGreaterByDefault<int>)
{
	if (array_size <= 1)
	{
		return 0;
	}
	std::swap(array_instance[GetRandomIndex(array_size)], array_instance[array_size - 1]);
	int pivot = array_instance[array_size - 1];
	int i = 0;
	int j = 0;
	while (j < (array_size - 1))
	{
		if (IsGreater(array_instance[j], pivot)) // если очередной элемент с индексом j больше пивота
		{
			++j; // увеличиваем j
		}
		else // в противном случае меняем местами элементы с индексами i и j, после чего увнличиваем оба индекса
		{
			std::swap(array_instance[i], array_instance[j]);
			++j;
			++i;
		}
	}
	// когда j дойдёт до конца массива
	std::swap(array_instance[i], array_instance[array_size - 1]); // меняем местами i-ый элемент и пивот
	return i;
}

int FindKStat(int* arr, int n, int k_statistics, bool IsGreater(const int&, const int&) = IsGreaterByDefault<int>) {
	assert(k_statistics >= 0 && k_statistics < n);
	int pivotPos = Partition(arr, n, IsGreater);
	if (pivotPos == k_statistics)
	{
		return arr[k_statistics];
	}
	int left = 0; // смешение относительно начала массива, основанное на пивотах, вычесленных в прошлых итерациях
	int right = n; // смешение относительно конца массива, основанное на пивотах, вычесленных в прошлых итерациях
	// имеено n, а не (n - 1), потому что Partition получает на вход длину массива, а не индекс(ы) элементов
	while (k_statistics != pivotPos)
	{
		if (k_statistics < pivotPos) // если очередной вычесленный пивот меньше индекса к-ой статистики
		{
			right = pivotPos;
		}
		else
		{
			left = pivotPos + 1;
		}
		pivotPos = Partition(arr + left, right - left, IsGreater) + left; // прибавляем left, потому что return функции partition
		// возвращает индекс элемента внутри укороченного массива, а нам нужен индекс в изначальном массиве
	}
	return arr[k_statistics];
}
void Run(std::istream& input, std::ostream& output)
{
	int array_size = 1;
	input >> array_size;
	int* array = new int[array_size];
	for (int i = 0; i < array_size; i++)
	{
		input >> array[i];
	}
	int median_index = ((50 * array_size) / 100);
	int ten_percent = ((10 * array_size) / 100);
	int ninety_percent = ((90 * array_size) / 100);

	output << FindKStat(array, array_size, ten_percent) << '\n';
	output << FindKStat(array, array_size, median_index) << '\n';
	output << FindKStat(array, array_size, ninety_percent) << '\n';
	delete[] array;
}

void TestSolution()
{
	{
		std::stringstream output;
		std::stringstream input;
		input << "10 1 2 3 4 5 6 7 8 9 10";
		Run(input, output);
		assert(output.str() == "2\n6\n10\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "20 95 16 31 30 98 68 60 85 43 62 48 3 92 72 67 8 17 39 34 96";
		Run(input, output);
		assert(output.str() == "16\n60\n96\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "100 71 50 42 92 84 19 41 59 79 53 33 31 38 18 66 67 57 96 32 100 1 25 99 98 89 47 95 54 61 10 73 9 69 26 36 12 6 8 15 77 93 64 45 76 51 85 5 56 22 17 44 23 97 13 74 34 81 14 55 40 2 30 65 27 91 37 16 28 4 94 35 49 88 29 21 86 72 75 87 43 78 70 68 90 60 83 24 82 48 11 39 62 52 3 46 58 63 80 7 20";
		Run(input, output);
		assert(output.str() == "11\n51\n91\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "40 5 6 3 10 4 9 7 2 8 1 6 8 2 7 3 1 4 5 9 10 10 7 9 8 1 2 6 3 5 4 7 3 6 2 10 4 9 1 8 5";
		Run(input, output);
		assert(output.str() == "2\n6\n10\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "10 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10";
		Run(input, output);
		assert(output.str() == "-9\n-5\n-1\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "2 1 2";
		Run(input, output);
		assert(output.str() == "1\n2\n2\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "3 3 1 2";
		Run(input, output);
		assert(output.str() == "1\n2\n3\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "1 1";
		Run(input, output);
		assert(output.str() == "1\n1\n1\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "10 1000000001 1000000002 1000000003 1000000004 1000000005 1000000006 1000000007 1000000008 1000000009 1000000010";
		Run(input, output);
		assert(output.str() == "1000000002\n1000000006\n1000000010\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "9 1 2 3 4 5 6 7 8 9";
		Run(input, output);
		assert(output.str() == "1\n5\n9\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "200 41 67 134 100 169 124 78 158 162 64 105 145 81 27 161 91 195 142 27 36 191 4 102 153 92 182 21 116 118 95 47 126 171 138 69 112 67 99 35 94 103 11 122 133 73 64 141 111 53 68 147 44 62 157 37 59 123 141 129 178 116 35 190 42 88 106 40 142 64 48 46 5 90 129 170 150 6 101 193 148 29 23 84 154 156 40 166 176 131 108 144 39 26 123 137 138 118 82 129 141 33 115 39 58 104 130 177 106 73 186 21 145 124 72 70 29 177 173 97 112 186 90 161 36 155 167 55 174 31 52 150 150 141 124 166 30 107 191 7 137 57 87 153 183 145 109 9 158 21 188 22 146 106 30 13 168 100 191 162 55 10 159 24 137 148 83 195 41 2 150 91 36 174 19 196 21 148 199 68 84 81 134 53 199 18 138 100 188 127 67 128 93 48 83 7 21 110 17 13 114";
		Run(input, output);
		assert(output.str() == "23\n106\n176\n");
	}
}

int main()
{
	Run(std::cin, std::cout);
	//TestSolution();
	return 0;
}