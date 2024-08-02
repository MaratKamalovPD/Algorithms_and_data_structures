// Реализуйте структуру данных типа “множество строк” на основе динамической хеш - таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш - функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8 - ми.
// Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3 / 4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_2.Для разрешения коллизий используйте двойное хеширование.
// Требования: В таблице запрещено хранение указателей на описатель элемента.

// Формат входных данных:
// Каждая строка входных данных задает одну операцию над множеством.
// Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
// Тип операции  – один из трех символов :
// +означает добавление данной строки в множество;
// -означает удаление  строки из множества;
// ? означает проверку принадлежности данной строки множеству.
// При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
// При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

// Формат выходных данных:
// Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.



#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>


template<class T, class H>
class HashTable {
public:
	HashTable(int initialSize, const H& hasher);
	~HashTable();
	HashTable(HashTable&) = delete;
	HashTable& operator= (const HashTable&) = delete;

	bool Has(const T& key) const;

	bool Add(const T& key);

	bool Delete(const T& key);


private:
	H hasher;
	enum CellState { EMPTY, VALUE, DELETED };
	struct HashTableElement {
		T value;
		CellState state;
		HashTableElement() : state(EMPTY) {}
		HashTableElement(const T& _value, CellState _state) :
			value(_value), state(_state) {}
	};
	std::vector<HashTableElement> table;
	int empty_cells_count;
	int values_cells_count;
	int deleted_cells_count;

	void GrowTable(bool growth_needed);
};

template<class T, class H>
HashTable<T, H>::HashTable(int initial_size, const H& _hasher) :
	hasher(_hasher),
	table(initial_size),
	empty_cells_count(initial_size),
	values_cells_count(0),
	deleted_cells_count(0)
{
}

template<class T, class H>
HashTable<T, H>::~HashTable()
{

}

template<class T, class H>
bool HashTable<T, H>::Has(const T& _value) const
{
	unsigned int hash;
	for (int i = 0; i < table.size(); ++i)
	{
		hash = hasher(_value, i) % table.size();
		if (table[hash].state == EMPTY)
		{
			return false;
		}
		if (table[hash].state == DELETED)
		{
			continue;
		}
		if (table[hash].state == VALUE)
		{
			if (table[hash].value == _value)
			{
				return true;
			}
			else
			{
				continue;
			}
		}
	}
	return false;
}


template<class T, class H>
bool HashTable<T, H>::Add(const T& _value)
{
	if ((4 * (values_cells_count + deleted_cells_count)) > (3 * table.size())) // если более трёх четвертей таблицы заполнено действительными и удалёнными значениями
	{
		if ((8 * deleted_cells_count) > (3 * table.size())) // если ещё при этом более трёх восьмых таблицы заполнено удалёнными значениями
		{
			GrowTable(false); // производим рехеширование без изменения размера таблицы
		}
		else
		{
			GrowTable(true); // производим рехеширование с изменением размера таблицы
		}
	}
	int index_of_first_deleted_cell = -1;
	unsigned int hash;
	for (int i = 0; i < table.size(); ++i)
	{
		hash = hasher(_value, i) % table.size();
		if (table[hash].state == EMPTY)
		{
			if (index_of_first_deleted_cell == -1)
			{
				table[hash].value = _value;
				table[hash].state = VALUE;
				--empty_cells_count;
				++values_cells_count;
				return true; // вставляем элемент по индексу текущего хэша, получилось вставить
			}
			else
			{
				table[index_of_first_deleted_cell].value = _value;
				table[index_of_first_deleted_cell].state = VALUE;
				--empty_cells_count;
				++values_cells_count;
				return true; // вставляем элемент по первой удалённой ячейки, получилось вставить
			}
		}
		if (table[hash].state == DELETED)
		{
			if (index_of_first_deleted_cell == -1)
			{
				index_of_first_deleted_cell = int(hash);
				continue;
			}
			else
			{
				continue;
			}
		}
		if (table[hash].state == VALUE)
		{
			if (table[hash].value == _value)
			{
				return false; // такой элемент уже есть в хэш таблице, не получилось вставить
			}
			else
			{
				continue;
			}
		}
	}
	return false; // не было пустых ячеек, не получилось вставить
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T& _value)
{
	unsigned int hash;
	for (int i = 0; i < table.size(); ++i)
	{
		hash = (hasher(_value, i) % table.size());
		if (table[hash].state == EMPTY)
		{
			return false; // ячейки с таким значение нет в хэш таблице, удаление не сработало
		}
		if (table[hash].state == DELETED)
		{
			continue;
		}
		if (table[hash].state == VALUE)
		{
			if (table[hash].value == _value)
			{
				(table[hash].state = DELETED);
				--empty_cells_count;
				++deleted_cells_count;
				return true; // ячейка успешно удалена
			}
			else
			{
				continue;
			}
		}
	}
	return false; // ячейки с таким значение нет в хэш таблице, удаление не сработало
}

template<class T, class H>
void HashTable<T, H>::GrowTable(bool growth_needed)
{
	unsigned int hash;
	unsigned int new_size;
	if (growth_needed)
	{
		new_size = table.size() * 2;
	}
	else
	{
		new_size = table.size();
	}
	std::vector<HashTableElement> new_table(new_size);
	empty_cells_count = new_size;
	values_cells_count = 0;
	deleted_cells_count = 0;
	for (int i = 0; i < table.size(); ++i)
	{
		if (table[i].state == EMPTY)
		{
			continue;
		}
		if (table[i].state == DELETED)
		{
			continue;
		}
		if (table[i].state == VALUE)
		{
			for (int j = 0; j < new_table.size(); ++j) // при рехэшировании тоже могут возникать коллизии, обрабатываем их также, как при добавлении элемента в хэш таблицу, только без оглядки на удалённые элементы (потому что их не будет)
			{
				hash = hasher(table[i].value, j) % new_table.size();
				if (new_table[hash].state == VALUE)
				{
					continue;
				}
				else
				{
					new_table[hash].value = table[i].value;
					new_table[hash].state = VALUE;
					--empty_cells_count;
					++values_cells_count;
					break;
				}
			}
		}
	}
	table = std::move(new_table);

}




struct DoubleHasherForString
{
	unsigned int operator()(const std::string& _value, int i) const
	{
		unsigned int hash_1 = 0;
		for (int j = _value.length() - 1; j >= 0; j--) // считаем h1 методом Горнера с проходом от конца строки к началу
		{
			hash_1 = hash_1 * 233 + int(_value[j]);
		}
		hash_1 = (hash_1 * 2) + 1;
		unsigned int hash_2 = 0;
		for (unsigned int j = 0; j < _value.size(); ++j) // считаем h2 методом Горнера с проходом от начала строки к концу
		{
			hash_2 = hash_2 * 877 + int(_value[j]);
		}
		hash_2 = (hash_2 * 2) + 1;
		return (hash_1 + (i * hash_2)); // вычисляем двойной хэш
	}
};

void Run(std::istream& input, std::ostream& output)
{
	DoubleHasherForString hasher;
	HashTable<std::string, DoubleHasherForString> table(4, hasher);
	char operation = 0;
	std::string word;
	while (input >> operation >> word)
	{
		switch (operation)
		{
		case '+':
			output << (table.Add(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			output << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			output << (table.Has(word) ? "OK" : "FAIL") << std::endl;
			break;
		default:
			assert(false);
		}
	}
}

void TestSolution()
{
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye ? bye + bye - bye ? bye ? hello";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik + zic + rick";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik ? hello ? bye";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik ? hello ? bye - hello - bye";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik ? hello ? bye - hello - bye + hello + bye";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik + zic + rick - hello - bye - biba - boba - aboba - giga - bik";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
	{
		std::stringstream output;
		std::stringstream input;
		input << "+ hello + bye + biba + boba + aboba + giga + bik + zic + rick - hello - bye - biba - boba - aboba - giga - bik - zic - rick";
		Run(input, output);
		assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
	}
}

int main()
{
	//TestSolution();
	Run(std::cin, std::cout);
	return 0;
}