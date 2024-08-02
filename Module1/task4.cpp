// Требование для всех вариантов Задачи 4
// Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Куча должна быть динамической.
// 4.2 Топ K пользователей из лога
// Имеется лог - файл, в котором хранятся пары для N пользователей(Идентификатор пользователя, посещаемость сайта).
// Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.Количество заходов и идентификаторы пользователей не повторяются.
// Требования: время работы O(N* logK), где N - кол - во пользователей. Ограничение на размер кучи O(K).
// Формат входных данных : Сначала вводятся N и K, затем пары(Идентификатор пользователя, посещаемость сайта)

#include <iostream>
#include <cassert>
#include <sstream>
#include <memory>

class WebsiteUser
{
public:
    WebsiteUser();
    WebsiteUser(int user_id, int site_traffic);

    int GetUserID() const; // возвращает посещаемость сайта
    int GetSiteTraffic() const; // возвращает посещаемость сайта
    void PostUserID(int _user_id);  // записывает идентификатор пользователя в соответствующее поле класса
    void PostSiteTraffic(int _site_traffic); // записывает идентификатор пользователя посещаемость сайта в соответствующее поле класса

private:
    int site_traffic,  // посещаемость сайта
        user_id; // идентификатор пользователя,
};

int WebsiteUser::GetUserID() const
{
    return user_id;
}

int WebsiteUser::GetSiteTraffic() const
{
    return site_traffic;
}

void WebsiteUser::PostUserID(int _user_id)
{
    user_id = _user_id;
}

void WebsiteUser::PostSiteTraffic(int _site_traffic)
{
    site_traffic = _site_traffic;
}

WebsiteUser::WebsiteUser() : site_traffic(0), user_id(0)
{

}

WebsiteUser::WebsiteUser(int user_id, int site_traffic) : user_id(user_id), site_traffic(site_traffic)
{
}

class WebsiteUserComparator
{
public:
    bool IsGreaterComparator(const WebsiteUser& site_user_1, const WebsiteUser& site_user_2)
    {
        return  site_user_1.GetSiteTraffic() > site_user_2.GetSiteTraffic();
    }

    bool IsLessComparator(const WebsiteUser& site_user_1, const WebsiteUser& site_user_2)
    {
        return  site_user_1.GetSiteTraffic() < site_user_2.GetSiteTraffic();
    }

    bool IsLessOrEqualComparator(const WebsiteUser& site_user_1, const WebsiteUser& site_user_2)
    {
        return  site_user_1.GetSiteTraffic() <= site_user_2.GetSiteTraffic();
    }

    bool IsGreaterOrEqualComparator(const WebsiteUser& site_user_1, const WebsiteUser& site_user_2)
    {
        return  site_user_1.GetSiteTraffic() >= site_user_2.GetSiteTraffic();
    }
private:

};

template<class T>
class Array
{
public:
    Array();
    Array(int n);
    ~Array();
    Array(const Array<T>& array_instance);
    Array<T>& operator= (const Array<T>& array_instance);

    void Add(const T& element); // добавляет елемент в массив
    void DeleteLast(); // удаляет последний элемент из массива
    bool IsEmpty() const; // возвращает true, если массив пустой, и false в противном случае
    T Last(); // возвращает значение последнего элемента массива
    int Size() const; // возвращает размер массива
    T& operator[](int i) const; // оператор индексирования

private:
    int max_size, // максимальный размер массива
        current_size; // текущий размер массива
    std::shared_ptr<T[]> storage_array; // умный указатель на начало массива
};

template<class T>
Array<T> ::Array() : max_size(2), current_size(0), storage_array(new T[max_size])
{

}

template<class T>
Array<T> ::Array(int n) : max_size(n), current_size(0), storage_array(new T[max_size])
{
}

template<class T>
Array<T> :: ~Array()
{

}

template<class T>
Array<T> ::Array(const Array& array_instance)
{
    max_size = array_instance.max_size;
    current_size = array_instance.current_size;
    storage_array = array_instance.storage_array;
}

template<class T>
Array<T>& Array<T> :: operator= (const Array<T>& array_instance)
{
    if (this == &array_instance)
        return *this;
    this->max_size = array_instance.max_size;
    this->current_size = array_instance.current_size;
    this->storage_array = array_instance.storage_array;
    return *this;

}

template<class T>
void Array<T> ::Add(const T& element)
{
    assert(max_size != current_size);
    storage_array[current_size] = element; // добавление очередного элемента в массив
    ++current_size;
}

template<class T>
void Array<T>::DeleteLast()
{
    assert(Size() > 0);
    --current_size;
}

template<class T>
bool Array<T>::IsEmpty() const
{
    if (current_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
T Array<T>::Last()
{
    assert(Size() > 0);
    return storage_array[current_size - 1];
}

template<class T>
int Array<T>::Size() const
{
    return current_size;
}

template<class T>
T& Array<T>:: operator[](int i) const
{
    return storage_array[i];
}

template<class T, class Compare>
class Heap
{
public:
    Heap(int heap_size, Compare cmp);
    Heap(Array<T> arr, int size, Compare cmp);
    ~Heap();
    Heap(const Heap<T, Compare>& heap_instance);
    Heap<T, Compare>& operator= (const Heap<T, Compare>& heap_instance);
    // Добавить элемент в кучу за O(log n)
    void Insert(const T& element);
    // Извлечь максимум из кучи за O(log n)
    T ExtractMin();
    // Посмотреть значение максимума в куче за O(1)
    T PeekMin() const;
    // Заменить голову кучи и просеять новую голову вниз
    void ChangeHeadTo(const T& new_head);

private:
    Compare cmp; // функтор, содержаший функции сравнения
    int heap_size; // размер кучи
    bool heap_was_built; // использовалась ли функция buildheap для построение кучи из неотсортированоого массива
    Array<T> array_buffer; // динамический массив для хранения элементов кучи
    void buildHeap(); // Построение кучи за за O(n)
    void siftDown(int i); // Проталкивание элемента вниз.
    void siftUp(int i); // Проталкивание элемента наверх.
};

template<class T, class Compare>
Heap<T, Compare> ::Heap(int _heap_size, Compare _cmp) : heap_size(_heap_size), cmp(_cmp), heap_was_built(false)
{
    Array<T> new_buffer(heap_size);
    array_buffer = new_buffer;
}

template<class T, class Compare>
Heap<T, Compare> ::Heap(Array<T> _array_buffer, int _heap_size, Compare _cmp) : heap_size(_heap_size), cmp(_cmp), heap_was_built(false)
{
    array_buffer = _array_buffer;
    buildHeap();
}

template<class T, class Compare>
Heap<T, Compare> :: ~Heap()
{

}

template<class T, class Compare>
Heap<T, Compare> ::Heap(const Heap<T, Compare>& heap_instance)
{
    cmp = heap_instance.cmp;
    heap_size = heap_instance.heap_size;
    array_buffer = heap_instance.array_buffer;
    heap_was_built = heap_instance.heap_was_built;
}

template<class T, class Compare>
Heap<T, Compare>& Heap<T, Compare> :: operator= (const Heap<T, Compare>& heap_instance)
{
    if (this == &heap_instance)
        return *this;
    this->cmp = heap_instance.cmp;
    this->heap_size = heap_instance.heap_size;
    this->array_buffer = heap_instance.array_buffer;
    this->heap_was_built = heap_instance.heap_was_built;
    return *this;

}


template<class T, class Compare>
void Heap<T, Compare>::siftDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем меньшего сына, если такой есть.
    int largest = i;
    if (left < array_buffer.Size() && cmp.IsLessComparator(array_buffer[left], array_buffer[i]))
        largest = left;
    if (right < array_buffer.Size() && cmp.IsLessComparator(array_buffer[right], array_buffer[largest]))
        largest = right;
    // Если меньший сын есть, то проталкиваем корень в него.
    if (largest != i) {
        std::swap(array_buffer[i], array_buffer[largest]);
        siftDown(largest);
    }
}

template<class T, class Compare>
void Heap<T, Compare>::buildHeap()
{
    for (int i = array_buffer.Size() / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}


template<class T, class Compare>
void Heap<T, Compare>::siftUp(int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (cmp.IsGreaterOrEqualComparator(array_buffer[index], array_buffer[parent]))
            return;
        std::swap(array_buffer[index], array_buffer[parent]);
        index = parent;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::Insert(const T& element)
{
    array_buffer.Add(element);
    if (heap_was_built) // если уже использовалась функция buildheap для построение кучи из неотсортированоого массива
    {
        siftUp(array_buffer.Size() - 1);
    }
    else
    {
        if (heap_size == array_buffer.Size())
        {
            buildHeap();
        }
    }


}

template<class T, class Compare>
T Heap<T, Compare> ::PeekMin() const
{
    return array_buffer[0];
}


template<class T, class Compare>
T Heap<T, Compare>::ExtractMin()
{
    assert(!array_buffer.IsEmpty());
    // Запоминаем значение корня.
    T result = array_buffer[0];
    // Переносим последний элемент в корень.
    array_buffer[0] = array_buffer.Last();
    array_buffer.DeleteLast();
    // Вызываем SiftDown для корня.
    if (!array_buffer.IsEmpty()) {
        siftDown(0);
    }
    return result;
}

template<class T, class Compare>
void Heap<T, Compare>::ChangeHeadTo(const T& new_head)
{
    array_buffer[0] = new_head;
    siftDown(0);
}

void Run(std::istream& input, std::ostream& output)
{
    int n = 0, // количество пар входных данных
        k = 0; // количество выходных данных
    int ins = 0;
    int user_id = 0;
    int site_traffic = 0;
    WebsiteUser web_site_user_instance;
    WebsiteUserComparator web_site_user_comparator;
    input >> n;
    input >> k;
    assert(n >= k);
    Array<WebsiteUser> web_site_user_array(k); // заводим массив под к элементов

    int i = 0;
    for (; i < k; ++i) // получение первых k элементов и запись их в массив
    {
        input >> user_id >> site_traffic;
        web_site_user_instance.PostSiteTraffic(site_traffic);
        web_site_user_instance.PostUserID(user_id);
        web_site_user_array.Add(web_site_user_instance);
    }

    Heap<WebsiteUser, WebsiteUserComparator> heap_instance(web_site_user_array, k, web_site_user_comparator); // собранный ранее массив подаётся на вход конструктора кучи
    for (; i < n; ++i)
    {
        input >> user_id >> site_traffic;
        web_site_user_instance.PostSiteTraffic(site_traffic);
        web_site_user_instance.PostUserID(user_id);
        // если очередной добавляемый пользователь имеет больший показатель посещаемости, чем голова кучи
        if (web_site_user_comparator.IsLessComparator(heap_instance.PeekMin(), web_site_user_instance))
        {
            heap_instance.ChangeHeadTo(web_site_user_instance); // заменяем голову на этого пользователя                
        }
    }

    for (int i = 0; i < k; ++i)
    {
        if (i == (k - 1))
        {
            output << heap_instance.ExtractMin().GetUserID();
        }
        else
        {
            output << heap_instance.ExtractMin().GetUserID() << ' ';
        }
    }

}


void TestSolution()
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "3 3 100 36 80 3 1 5";
        Run(input, output);
        assert(output.str() == "80 1 100");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "4 4 4 1 3 2 2 3 1 4";
        Run(input, output);
        assert(output.str() == "4 3 2 1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "4 2 4 1 3 2 2 3 1 4";
        Run(input, output);
        assert(output.str() == "2 1");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "10 5 10 10 9 9 8 8 7 7 6 6 5 5 4 4 3 3 2 2 1 1";
        Run(input, output);
        assert(output.str() == "6 7 8 9 10");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "10 10 10 10 1 1 8 8 2 2 4 4 5 5 6 6 3 3 7 7 9 9";
        Run(input, output);
        assert(output.str() == "1 2 3 4 5 6 7 8 9 10");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "10 5 10 10 1 1 8 8 2 2 4 4 5 5 6 6 3 3 7 7 9 9";
        Run(input, output);
        assert(output.str() == "6 7 8 9 10");
    }
}


int main()
{
    Run(std::cin, std::cout);
    //TestSolution();
    return 0;
}

