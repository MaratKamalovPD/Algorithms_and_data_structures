// 3. B-дерево
// Постройте B - дерево минимального порядка t и выведите его по слоям.
// В качестве ключа используются числа, лежащие в диапазоне[0..23^2 - 1]
// Требования:

// B - дерево должно быть реализовано в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Формат ввода
// Сначала вводится минимальный порядок дерева t.
// Затем вводятся элементы дерева.

// Формат вывода
// Программа должна вывести B - дерево по слоям.
// Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.


#include <iostream>
#include <queue>

template<class T, class Compare>
class BTree
{
public:
    BTree(size_t _t, Compare& _cmp) : root(nullptr), cmp(_cmp), t(_t) {}
    ~BTree();
    BTree(BTree&) = delete;
    BTree& operator= (const BTree&) = delete;
    void Insert(const T& key);
    void PrintBTree() const;

private:
    struct Node
    {
        bool IsLeaf;
        T* Keys;
        Node** Children;
        int n;
        Node(bool isLeaf, int t) : IsLeaf(isLeaf), n(0)
        {
            Keys = new int[2 * t - 1];
            Children = new Node * [2 * t];
        }
        ~Node()
        {
            delete Children; // внутренние указатели уничтожаются в деструкторе B-Дерева, поэтому здесь нет цикла удаления всех Children[i]
            delete Keys;
        }
    };
    Compare cmp;
    Node* root;
    int t;

    void insertNonFull(Node* node, const T& key);
    void splitChild(Node* y, int pos);
    bool isNodeFull(Node* node) const;
    void HelpDestructor(Node* node);
};


template<class T, class Compare>
BTree<T, Compare>::~BTree()
{
    HelpDestructor(root);
    delete root;
}

template<class T, class Compare>
void BTree<T, Compare>::HelpDestructor(Node* node)
{
    int i = 0;
    for (; i < node->n; ++i)
    {
        if (!node->IsLeaf)
        {
            HelpDestructor(node->Children[i]);
            delete node->Children[i];
        }
        //delete node->Keys[i];
    }
    if (!node->IsLeaf) // так как максимальный размер массива Keys = 2 * t - 1, а Children = 2 * t, то есть на 1 больше, то нужна ещё одна итерация для Children
    {
        HelpDestructor(node->Children[i]);
        delete node->Children[i];
    }
}

template<class T, class Compare>
bool BTree<T, Compare>::isNodeFull(Node* node) const
{
    if (node->n == (2 * t - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T, class Compare>
void BTree<T, Compare>::Insert(const T& key)
{
    if (root == nullptr)
    {
        root = new Node(true, t);
        root->Keys[0] = key;
        root->n = 1;
    }
    else
    {
        if (isNodeFull(root)) // если корень заполнен
        {
            Node* new_root = new Node(false, t); // создаем новый узел, у него будут потомки
            new_root->Children[0] = root; // цепляем к нему старый корень
            root = new_root; // делаем его корнем
            splitChild(root, 0);

            int pos = 0;
            if (new_root->Keys[0] < key)
            {
                ++pos;
            }
            insertNonFull(new_root->Children[pos], key);
        }
        else
        {
            insertNonFull(root, key);
        }
    }
}

template<class T, class Compare>
void BTree<T, Compare>::insertNonFull(Node* node, const T& key)
{
    int pos = node->n - 1;

    if (node->IsLeaf)  // если node – лист, в этот узел запишем ключ key
    {
        while (pos >= 0 && cmp(node->Keys[pos], key)) // ищем позицию вставки справа налево, сдвигая обойденные ключи на 1 вправо
        {
            node->Keys[pos + 1] = node->Keys[pos];
            --pos;
        }
        node->Keys[pos + 1] = key; // добавляем ключ на освободившееся место
        node->n = node->n + 1; // +1 к хранимым ключам
    }
    else // если же node – внутренний узел
    {
        while (pos >= 0 && cmp(node->Keys[pos], key)) // надо найти потомка, куда будем писать
        {
            --pos;
        }
        if (isNodeFull(node->Children[pos + 1])) // если потомок полон, сначала разобъем его
        {
            splitChild(node, pos + 1);

            if (node->Keys[pos + 1] < key) // в какого из новых потомков пойдем?
            {
                ++pos;
            }
        }
        insertNonFull(node->Children[pos + 1], key);
    }
}

template<class T, class Compare>
void BTree<T, Compare>::splitChild(Node* x, int pos)
{
    Node* y = x->Children[pos]; // старый узел-потомок X
    Node* z = new Node(y->IsLeaf, t); // новый узел-потомок X
    z->n = t - 1; // половина ключей Y уходит в Z

    for (int j = 0; j < t - 1; ++j) // переносим их
    {
        z->Keys[j] = y->Keys[j + t];
    }

    if (!y->IsLeaf) // если у Y есть потомки
    {
        for (int j = 0; j < t; ++j) // половину потомков Y
        {
            z->Children[j] = y->Children[j + t]; // переносим в Z
        }
    }

    y->n = t - 1; // поправим счетчик ключей в Y

    for (int j = x->n; j >= pos + 1; --j)
    {
        x->Children[j + 1] = x->Children[j]; // сдвиг указателей на 1 вправо
    }

    x->Children[pos + 1] = z; // чтобы добавить указатель на Z

    for (int j = x->n - 1; j >= pos; --j) // сдвиг ключей в X вправо
    {
        x->Keys[j + 1] = x->Keys[j]; // на 1 для вставки медианы
    }

    x->Keys[pos] = y->Keys[t - 1]; // бывшего узла Y (до разбиения)
    x->n = x->n + 1; // из-за этого +1 к ключам в Х
}

template<class T, class Compare>
void BTree<T, Compare>::PrintBTree() const
{
    Node* current_node = root;
    std::queue<Node*> node_queue;
    for (int i = 0; i < current_node->n; ++i)
    {
        std::cout << current_node->Keys[i] << ' ';
    }
    for (int i = 0; i < current_node->n + 1; ++i)
    {
        node_queue.push(current_node->Children[i]);
    }
    std::cout << std::endl;
    node_queue.push(nullptr);
    while (!node_queue.empty())
    {
        current_node = node_queue.front();
        if (current_node == nullptr)
        {
            node_queue.push(nullptr);
            std::cout << std::endl;
            node_queue.pop();
            current_node = node_queue.front();
            if (current_node == nullptr)
            {
                break;
            }
        }

        for (int i = 0; i < current_node->n; ++i)
        {
            std::cout << current_node->Keys[i] << ' ';
        }
        if (!current_node->IsLeaf)
        {
            for (int i = 0; i < current_node->n + 1; ++i)
            {
                node_queue.push(current_node->Children[i]);
            }
        }
        node_queue.pop();
    }
}

struct IntCmp
{
    bool operator()(int l, int r)
    {
        return l > r;
    }
};


int main()
{
    int n = 0;
    IntCmp cmp;
    int element = 0;
    std::cin >> n;
    BTree<int, IntCmp> btree(n, cmp);
    while (std::cin >> element)
    {
        btree.Insert(element);
    }
    btree.PrintBTree();
    return 0;
}