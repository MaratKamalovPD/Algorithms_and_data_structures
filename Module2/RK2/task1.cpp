
#include<iostream>
#include <queue>
#include <memory>

template<class T, class Compare>
class BinaryTree {
public:
	BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp), element_count(0) {}
	~BinaryTree() {}
	BinaryTree(BinaryTree&) = delete;
	BinaryTree& operator= (const BinaryTree&) = delete;

	void Add(const T& key);

	int AllElementsAreEqual() const;

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
int BinaryTree<T, Compare>::AllElementsAreEqual() const
{
	if (root == nullptr)
	{
		return 1;
	}
	std::queue<std::shared_ptr<TreeNode>> tree_node_queue;
	std::shared_ptr<TreeNode> tree_node_instance;
	T root_value = root->value;
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
		if (tree_node_instance->value != root_value)
		{
			return 0;
		}
		tree_node_queue.pop();
	}
	return 1;

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
	int n = 0; // количество вводимых элементов
	int element; // очередной вводимый элемент
	while (std::cin >> element)
	{
		tree.Add(element);
	}
	std::cout << tree.AllElementsAreEqual();

	return 0;
}