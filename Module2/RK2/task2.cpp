// Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена.Решение должно поддерживать передачу функции сравнения снаружи.
// 2_4.Выведите элементы в порядке level - order(по слоям, “в ширину”).


#include<iostream>
#include <queue>
#include <memory>
#include<stack>

template<class T, class Compare>
class BinaryTree {
public:
	BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp), element_count(0) {}
	~BinaryTree() {}
	BinaryTree(BinaryTree&) = delete;
	BinaryTree& operator= (const BinaryTree&) = delete;

	void Add(const T& key);
	int FindLeastHeight() const;
	void DfsInOrder(void (*visit)(const T& key)) const;

private:
	struct TreeNode {
		T value;
		std::shared_ptr<TreeNode> left_child;
		std::shared_ptr<TreeNode> right_child;
		TreeNode(const T& _value) : value(_value), left_child(nullptr), right_child(nullptr) {}
	};
	std::shared_ptr<TreeNode> root;
	Compare cmp;
	int element_count;
};

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& _value)
{
	std::shared_ptr<TreeNode> new_tree_node(new TreeNode(_value));
	++element_count;
	if (root == nullptr)
	{
		root = new_tree_node;
		return;
	}
	std::shared_ptr<TreeNode> current_tree_node = root;
	while (true)
	{
		if (cmp(current_tree_node->value, _value)) // врозвращает l < r
		{
			if ((current_tree_node->right_child) == nullptr)
			{
				current_tree_node->right_child = new_tree_node;
				return;
			}
			else
			{
				current_tree_node = current_tree_node->right_child;
			}
		}
		else
		{
			if ((current_tree_node->left_child) == nullptr)
			{
				current_tree_node->left_child = new_tree_node;
				return;
			}
			else
			{
				current_tree_node = current_tree_node->left_child;
			}
		}
	}
}

template<class T, class Compare>
void BinaryTree<T, Compare>::DfsInOrder(void (*visit)(const T& key)) const
{
	if (root == nullptr)
	{
		return;
	}
	std::queue<std::shared_ptr<TreeNode>> tree_node_queue;
	std::shared_ptr<TreeNode> tree_node_instance;
	tree_node_queue.push(root);
	for (int i = 0; i < element_count; ++i)
	{
		tree_node_instance = tree_node_queue.front();
		if (tree_node_instance->left_child != nullptr)
		{
			tree_node_queue.push(tree_node_instance->left_child);
		}
		if (tree_node_instance->right_child != nullptr)
		{
			tree_node_queue.push(tree_node_instance->right_child);
		}
		visit(tree_node_instance->value);
		tree_node_queue.pop();
	}

}

template<class T, class Compare>
int BinaryTree<T, Compare>::FindLeastHeight() const
{
	if (root == nullptr)
	{
		return 0;
	}
	std::queue<std::shared_ptr<TreeNode>> tree_node_queue;
	std::stack<std::shared_ptr<TreeNode>> tree_node_stack;
	std::shared_ptr<TreeNode> tree_node_instance;

	tree_node_queue.push(root);
	tree_node_queue.push(nullptr);
	int min_distance = 1;
	int layer_count = 1;
	for (int i = 0; i < element_count; ++i)
	{
		tree_node_instance = tree_node_queue.front();
		if (tree_node_instance == nullptr)
		{
			tree_node_queue.push(nullptr);
			tree_node_stack.push(nullptr);
			tree_node_queue.pop();
			tree_node_instance = tree_node_queue.front();
			++layer_count;
		}
		if (tree_node_instance->left_child != nullptr)
		{
			tree_node_queue.push(tree_node_instance->left_child);
		}
		if (tree_node_instance->right_child != nullptr)
		{
			tree_node_queue.push(tree_node_instance->right_child);
		}
		tree_node_stack.push(tree_node_instance);
		tree_node_queue.pop();
	}
	int element_in_layer_should_be;
	int least_distance = layer_count;
	while (!tree_node_stack.empty())
	{
		if (layer_count == 1)
		{
			break;
		}
		tree_node_instance = tree_node_stack.top();
		if (tree_node_instance == nullptr)
		{
			--layer_count;
			tree_node_stack.pop();
			tree_node_instance = tree_node_stack.top();
		}
		if ((tree_node_instance->left_child == nullptr) && (tree_node_instance->right_child == nullptr))
		{
			least_distance = layer_count;
		}
		tree_node_stack.pop();
	}
	return least_distance;

}

struct IntCmp {
	bool operator()(int l, int r)
	{
		return l < r;
	}
};

int main()
{
	IntCmp cmp;
	BinaryTree<int, IntCmp> tree(cmp);

	int element; // очередной вводимый элемент
	while (std::cin >> element)
	{
		tree.Add(element);
	}
	std::cout << tree.FindLeastHeight();

	return 0;
}