// 7_1.MSD ��� �����.
// ��� ������ �����.���������� ����� �� ������ 10^5.
// ������������� ������ ������� ����������� ���������� MSD �� ��������.
// ������ �������� - 256 ��������.��������� ������ ������ = �\0�.


#include <iostream>
#include <string.h>

template<class T, class TGetKey>
void CountingSort(T* a,
	int start_position, // ������ ������ ������ �����, ������� ����� ������� � ������� � �������� position
	int end_position, // ������ ����� ������ �����, ������� ����� ������� � ������� � �������� position
	int position, // ������ ������� � ������, �� �������� ����� ������������� ���������� ���������
	TGetKey getKey) // ������� ��� ��������� �������� ������� ������ ��� �������� position
{
	int n = end_position + 1;
	int max = getKey(a[start_position], position);
	for (int i = start_position + 1; i < n; ++i) // ������� ������������ ������ � ������� ��� ���������� ���������
	{
		max = std::max(max, getKey(a[i], position));
	}
	int* c = new int[max + 1]; // �������� ������ ��� ������ ��� ����� ���������� "������" �������� � �������� ������� 
	int* c_copy = new int[max + 1]; // �������� ������ ��� ����� ������� �, ������ ��� � ���� ������ ������, ������������ � ��, ����� ���������
	memset(c, 0, (max + 1) * sizeof(int)); // ��������� ������ � ������

	for (int i = start_position; i < n; ++i)
	{
		++c[getKey(a[i], position)];  // ������� ���������� "������" ��������� � �������� �������
	}

	for (int i = 1; i < max + 1; ++i)
	{
		c[i] += c[i - 1]; // ������� ����� ����� ��������� � ��� ��������������� �������
	}
	memcpy(c_copy, c, sizeof(int) * (max + 1)); // ��������� ����� ������� � ������� �� ������� �, ����� ����� ���� ������� ������ � ������� �

	T* b = new T[n - start_position]; // ������� �������� ������

	for (int i = n - 1; i >= start_position; --i) // ������� � �����,
	{
		b[--c[getKey(a[i], position)]] = a[i];  // ��������������� ����������� ������� ���������� ��������� � ����������� �������
	}
	delete[] c;


	for (int i = start_position; i < n; ++i)
	{
		a[i] = b[i - start_position]; // ����������� ��������� ������������ ������� �������� �� ��������� �������
	}
	delete[] b;

	int new_position = position + 1;
	for (int i = 0; i < max; ++i)
	{
		if (c_copy[i + 1] - c_copy[i] >= 2) // � ������, ���� ������ ������ 2 � �����
		{
			CountingSort(a, start_position + c_copy[i], start_position + c_copy[i + 1] - 1, new_position, getKey); // �� ���������� �������� CountingSort
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
			if (position > value.length()) // ���� ������� ���������� �������, ������� �� �������� �������, ������ ����� ������
			{
				return 0; // �� ���������� 0
			}
			return int(value[position]); // ����� ���������� ��� �������
		}
	);
	for (int i = 0; i < current_size; ++i)
	{
		std::cout << string_array[i] << std::endl;
	}
	delete[] string_array;
}
