// 7_1.MSD для строк.
// Дан массив строк.Количество строк не больше 10^5.
// Отсортировать массив методом поразрядной сортировки MSD по символам.
// Размер алфавита - 256 символов.Последний символ строки = ‘\0’.


#include <iostream>
#include <string.h>

template<class T, class TGetKey>
void CountingSort(T* a,
	int start_position, // индекс начала группы строк, имеющих общий элемент в позиции с индексом position
	int end_position, // индекс конца группы строк, имеющих общий элемент в позиции с индексом position
	int position, // индекс символа в строке, по которому будет производиться сортировка подсчётом
	TGetKey getKey) // функтор для получения значения символа строки под индексом position
{
	int n = end_position + 1;
	int max = getKey(a[start_position], position);
	for (int i = start_position + 1; i < n; ++i) // находим максимальный индекс в массиве для сортировки подсчётом
	{
		max = std::max(max, getKey(a[i], position));
	}
	int* c = new int[max + 1]; // выделяем память под массив для учёта количества "встреч" элемента в исходном массиве 
	int* c_copy = new int[max + 1]; // выделяем память под копию массива с, потому что в один момент данные, содержащиеся в нём, будут испорчены
	memset(c, 0, (max + 1) * sizeof(int)); // заполняем массив с нулями

	for (int i = start_position; i < n; ++i)
	{
		++c[getKey(a[i], position)];  // считаем количество "встреч" элементов в исходном массиве
	}

	for (int i = 1; i < max + 1; ++i)
	{
		c[i] += c[i - 1]; // считаем концы групп элементов в уже отсортированном массиве
	}
	memcpy(c_copy, c, sizeof(int) * (max + 1)); // заполняем копию массива с данными из массива с, чтобы можно было портить данные в массиве с

	T* b = new T[n - start_position]; // заводим буферный массив

	for (int i = n - 1; i >= start_position; --i) // проходя с конца,
	{
		b[--c[getKey(a[i], position)]] = a[i];  // восстанавливаем необходимый порядок следования элементов в изначальном массиве
	}
	delete[] c;


	for (int i = start_position; i < n; ++i)
	{
		a[i] = b[i - start_position]; // присваиваем значениям изначального массива значения из буферного массива
	}
	delete[] b;

	int new_position = position + 1;
	for (int i = 0; i < max; ++i)
	{
		if (c_copy[i + 1] - c_copy[i] >= 2) // в случае, если размер группы 2 и более
		{
			CountingSort(a, start_position + c_copy[i], start_position + c_copy[i + 1] - 1, new_position, getKey); // то рекурсивно вызываем CountingSort
		}
	}
	delete[] c_copy;
}

int main()
{
	int max_size = 4;
	int current_size = 0;
	auto* string_array = new std::string[max_size];
	std::string word;

	while (!std::cin.eof())
	{
		if (current_size == max_size)
		{
			max_size *= 2;
			auto* new_string_array = new std::string[max_size];
			std::copy(string_array, string_array + current_size, new_string_array);
			delete[] string_array;
			string_array = new_string_array;
		}
		std::cin >> word;
		if (!word.empty())
		{
			string_array[current_size] = word;
			current_size++;
		}
		word.clear();
	}

	CountingSort(string_array, 0, current_size - 1, 0, [](std::string value, int position)
		{
			if (position > value.length()) // если позициа очередного символа, который мы пытаемся считать, больше длины строки
			{
				return 0; // то возвращаем 0
			}
			return int(value[position]); // иначе возвращаем код символа
		}
	);
	for (int i = 0; i < current_size; ++i)
	{
		std::cout << string_array[i] << std::endl;
	}
	delete[] string_array;
}
