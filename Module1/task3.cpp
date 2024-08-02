//  Реализовать очередь с помощью двух стеков.
//  Использовать стек, реализованный с помощью динамического буфера.
//  Обрабатывать команды push back и pop front.
//  В первой строке количество команд n. n ? 1000000.

//  Каждая команда задаётся как 2 целых числа: a b.

//  a = 2 - pop front
//  a = 3 - push back

//  Если дана команда pop front, то число b - ожидаемое значение. 
//  Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

// Требуется напечатать YES - если все ожидаемые значения совпали.
//  Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

#include <iostream>
#include <cassert>
#include <memory>
#include <sstream>
class Stack
{
public:
    Stack();
    ~Stack();

    Stack(Stack&) = delete;
    Stack& operator= (const Stack&) = delete;

    void Push(unsigned int data);
    unsigned int Pop();
    int Size() const;


private:
    int max_size,
        current_size;
    std::shared_ptr<int[]> stack_array;

};

class DoubleStackQueue
{
public:
    DoubleStackQueue();
    ~DoubleStackQueue();

    DoubleStackQueue(DoubleStackQueue&) = delete;
    DoubleStackQueue& operator= (const DoubleStackQueue&) = delete;

    void PushBack(int data);
    int PopFront();
    int Size() const;


private:
    Stack pop_stack,
        push_stack;
    int   size;
};

void Stack::Push(unsigned int data)
{
    if (current_size == max_size)
    {

        std::shared_ptr<int[]> new_array(new int[max_size * 2]); // выделение памяти под элементы в 2 раза большем объеме
        for (int i = 0; i < max_size; i++)
        {
            new_array[i] = stack_array[i]; // копирование значений из старого массива в новый 
        }
        stack_array = new_array; // присваивание полю класса, соответствующему указателю на начало массива, значения нового указателя,
        //соответствующего в 2 раза большему объему выделенной памяти
        max_size = max_size * 2; // увеличение максимального размера массива в 2 раза
    }
    stack_array[current_size] = data; // добавление очередного элемента в массив
    ++current_size;
}

unsigned int Stack::Pop()
{
    assert(Size() > 0);
    --current_size;
    return stack_array[current_size];
}

int Stack::Size() const
{
    return current_size;

}

Stack::Stack() : max_size(2), current_size(0), stack_array(new int[max_size])
{

}

Stack::~Stack()
{

}

int DoubleStackQueue::Size() const
{
    return size;

}

DoubleStackQueue::DoubleStackQueue() : size(0)
{

}

DoubleStackQueue::~DoubleStackQueue()
{

}

void DoubleStackQueue::PushBack(int data)
{
    push_stack.Push(data);
    ++size;
}

int DoubleStackQueue::PopFront()
{
    assert(size > 0);
    if (pop_stack.Size() == 0)
    {
        while (push_stack.Size() > 0)
        {
            pop_stack.Push(push_stack.Pop());
        }
    }
    --size;
    return pop_stack.Pop();
}

void Run(std::istream& input, std::ostream& output)
{
    DoubleStackQueue queue;
    int n = 0; // См. условие
    input >> n;
    bool result = true;
    for (int i = 0; i < n; ++i)
    {
        int command = 0;
        int data = 0;
        input >> command >> data;
        switch (command)
        {
        case 2:
            if (queue.Size() == 0)
            {
                result = result && data == -1;
            }
            else
            {
                result = result && queue.PopFront() == data;
            }
            break;
        case 3:
            queue.PushBack(data);
            break;
        default:
            assert(false);


        }
    }
    output << (result ? "YES" : "NO");
}

void TestTheSolution()
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "3 3 44 3 50 2 44";
        Run(input, output);
        assert(output.str() == "YES");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 2 -1 3 10";
        Run(input, output);
        assert(output.str() == "YES");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "2 3 44 2 66";
        Run(input, output);
        assert(output.str() == "NO");
    }

}

int main()
{
    Run(std::cin, std::cout);
    //TestTheSolution();

}

