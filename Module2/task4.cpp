// Задача 4.1
// В одной военной части решили построить в одну шеренгу по росту.
// Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
// За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
// Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
// Требуемая скорость выполнения команды - O(log n).

// Формат ввода
// Первая строка содержит число N – количество команд(1 ≤ N ≤ 90 000).В каждой следующей строке содержится описание команды : число 1 и X если солдат приходит в строй(X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя.Солдаты в строе нумеруются с нуля.

// Формат вывода
// На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат(все стоящие за ним двигаются назад).


#include <iostream>
#include <queue>
#include <stack>
#include <cassert>
#include <sstream>

template<class T, class Compare>
class BinaryTree
{
public:

	BinaryTree(const Compare& _cmp);
	~BinaryTree();
	BinaryTree(BinaryTree&) = delete;
	BinaryTree& operator= (const BinaryTree&) = delete;

	int FindKstat(const T& _key) const;

	T FindElementByKstat(const T& kstat) const;

	void Add(const T& key);

	void Delete(const T& key);

	void DfsInOrder(void (*visit)(const T& key)) const;

private:
	struct node // структура для представления узлов дерева
	{
		T key;
		unsigned int height;
		unsigned int leafs_in_subtree;
		node* left;
		node* right;
		node(const T& k) : key(k), left(nullptr), right(nullptr), height(1), leafs_in_subtree(1) {}
	};
	node* root;
	Compare cmp;
	int element_count;

	unsigned int height(node* p) const;

	unsigned int LeafsInSubtree(node* p) const;

	int bfactor(node* p) const;

	void fixheight(node* p);

	node* rotateright(node* p) // правый поворот вокруг p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node* rotateleft(node* q) // левый поворот вокруг q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	node* insert(node* p, const T& k) // вставка ключа k в дерево 
	{
		if (!p) return new node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* findandremovemin(node*& min, node* p) // поиск узла с минимальным ключом 
	{
		if (p->left == nullptr)
		{
			min = p;
			return p->right;
		}
		p->left = findandremovemin(min, p->left);
		return balance(p);
	}

	node* remove(node* p, const T& k) // удаление ключа k 
	{
		if (!p)
		{
			return nullptr;
		}
		if (k < p->key)
		{
			p->left = remove(p->left, k);
		}
		else
		{
			if (k > p->key)
			{
				p->right = remove(p->right, k);
			}
			else //  k == p->key 
			{
				node* q = p->left;
				node* r = p->right;
				delete p;
				if (!r)
				{
					return q;
				}
				node* min = nullptr;
				min->right = findandremovemin(min, r);
				min->left = q;
				return balance(min);
			}
		}
		return balance(p);
	}
};

template<class T, class Compare>
BinaryTree<T, Compare>::BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp), element_count(0)
{

}

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree()
{
	if (root == nullptr)
	{
		return;
	}
	std::queue<node*> tree_node_queue;
	std::stack<node*> tree_node_stack;
	node* tree_node_instance;
	tree_node_queue.push(root);
	for (int i = 0; i < element_count; ++i)
	{
		tree_node_instance = tree_node_queue.front();
		if (tree_node_instance->left != nullptr)
		{
			tree_node_queue.push(tree_node_instance->left);
		}
		if (tree_node_instance->right != nullptr)
		{
			tree_node_queue.push(tree_node_instance->right);
		}
		tree_node_stack.push(tree_node_instance);
		tree_node_queue.pop();
	}
	while (!tree_node_stack.empty())
	{
		tree_node_instance = tree_node_stack.top();
		delete tree_node_instance->left;
		delete tree_node_instance->right;
		if (tree_node_instance == root)
		{
			delete root;
		}
		tree_node_stack.pop();
	}
}

template<class T, class Compare>
int BinaryTree<T, Compare>::FindKstat(const T& _key) const
{
	if (root == nullptr)
	{
		return -1;
	}
	int k_stat = 0;
	if (root->right != nullptr)
	{
		k_stat = root->right->leafs_in_subtree;
	}
	node* current_tree_node = root;
	while (true)
	{
		if (current_tree_node->key == _key)
		{
			return k_stat;
		}
		if (current_tree_node->key > _key)
		{
			current_tree_node = current_tree_node->left;
			++k_stat;
			if (current_tree_node->right != nullptr)
			{
				k_stat += current_tree_node->right->leafs_in_subtree;
			}
			continue;
		}
		if (current_tree_node->key < _key)
		{
			current_tree_node = current_tree_node->right;
			--k_stat;
			if (current_tree_node->left != nullptr)
			{
				k_stat -= current_tree_node->left->leafs_in_subtree;
			}
			continue;
		}
	}
}

template<class T, class Compare>
T BinaryTree<T, Compare>::FindElementByKstat(const T& kstat) const
{
	if (root == nullptr)
	{
		return -1;
	}
	int k_stat = 0;
	if (root->right != nullptr)
	{
		k_stat = root->right->leafs_in_subtree;
	}
	node* current_tree_node = root;
	while (true)
	{
		if (k_stat == kstat)
		{
			return current_tree_node->key;
		}
		if (k_stat < kstat)
		{
			current_tree_node = current_tree_node->left;
			++k_stat;
			if (current_tree_node->right != nullptr)
			{
				k_stat += current_tree_node->right->leafs_in_subtree;
			}
			continue;
		}
		if (k_stat > kstat)
		{
			current_tree_node = current_tree_node->right;
			--k_stat;
			if (current_tree_node->left != nullptr)
			{
				k_stat -= current_tree_node->left->leafs_in_subtree;
			}
			continue;
		}
	}
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& key)
{
	++element_count;
	root = insert(root, key);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Delete(const T& key)
{
	--element_count;
	root = remove(root, key);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::DfsInOrder(void (*visit)(const T& key)) const
{
	if (root == nullptr)
	{
		return;
	}
	std::queue<node*> tree_node_queue;
	node* tree_node_instance;
	tree_node_queue.push(root);
	for (int i = 0; i < element_count; ++i)
	{
		tree_node_instance = tree_node_queue.front();
		if (tree_node_instance->left != nullptr)
		{
			tree_node_queue.push(tree_node_instance->left);
		}
		if (tree_node_instance->right != nullptr)
		{
			tree_node_queue.push(tree_node_instance->right);
		}
		visit(tree_node_instance->key);
		tree_node_queue.pop();
	}
}

template<class T, class Compare>
unsigned int BinaryTree<T, Compare>::height(node* p) const
{
	return p ? p->height : 0;
}

template<class T, class Compare>
unsigned int BinaryTree<T, Compare>::LeafsInSubtree(node* p) const
{
	return p ? p->leafs_in_subtree : 0;
}

template<class T, class Compare>
int BinaryTree<T, Compare>::bfactor(node* p) const
{
	if (p == nullptr)
	{
		return 0;
	}
	return height(p->right) - height(p->left);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::fixheight(node* p)
{
	if (p == nullptr)
	{
		return;
	}
	unsigned int hl = height(p->left);
	unsigned int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;

	unsigned int sl = LeafsInSubtree(p->left);
	unsigned int sr = LeafsInSubtree(p->right);
	p->leafs_in_subtree = sl + sr + 1;
}


struct IntCmp {
	bool operator()(int l, int r)
	{
		return l < r;
	}
};

void Run(std::istream& input, std::ostream& output)
{
	IntCmp cmp;
	BinaryTree<int, IntCmp> tree(cmp);

	int comands_count = 0;
	int comand = 0;
	int value = 0;
	input >> comands_count;
	for (int i = 0; i < comands_count; ++i)
	{
		input >> comand >> value;
		if (comand == 1)
		{
			tree.Add(value);
			output << tree.FindKstat(value) << std::endl;
			continue;
		}
		if (comand == 2)
		{
			tree.Delete(tree.FindElementByKstat(value));
			continue;
		}
		assert(false);
	}
}

void TestSolution()
{
	{
		std::stringstream output;
		std::stringstream input;
		input << "5 1 100 1 200 1 50 2 1 1 150";
		Run(input, output);
		assert(output.str() == "0\n0\n2\n1\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "17 1 100 1 200 1 50 2 1 1 150 1 75 1 250 2 0 2 2 1 600 1 900 1 10 1 20 1 30 1 40 2 3 2 4";
		Run(input, output);
		assert(output.str() == "0\n0\n2\n1\n2\n0\n0\n0\n5\n5\n5\n5\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "6	1 1 1 2 1 3 2 0 2 0 2 0";
		Run(input, output);
		assert(output.str() == "0\n0\n0\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "6 1 3	1 2 1 1 1 4	2 2 2 2";
		Run(input, output);
		assert(output.str() == "0\n1\n2\n0\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "8 1 1 2 0 1 1	2 0 1 1 2 0 1 1 2 0";
		Run(input, output);
		assert(output.str() == "0\n0\n0\n0\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "17 1 5 1 3 1 1 1 6 1 4 1 2 2 5 2 3 2 1 1 30 1 10 1 20 2 3 2 0 1 90 1 40 1 60";
		Run(input, output);
		assert(output.str() == "0\n1\n2\n0\n2\n4\n0\n1\n1\n0\n1\n1\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "40 1 4 1 28 1 11 1 15 1 24 1 35 1 17 1 36 1 26 1 31 1 33 1 39 1 19 1 2 1 0 1 23 1 25 1 18 1 32 1 8 1 5 1 21 1 7 1 12 1 14 1 20 1 27 1 6 1 10 1 1 1 30 1 38 1 13 1 37 1 3 1 16 1 29 1 34 1 9 1 22";
		Run(input, output);
		assert(output.str() == "0\n0\n1\n1\n1\n0\n3\n0\n3\n2\n2\n0\n8\n13\n14\n8\n7\n11\n4\n16\n17\n11\n18\n16\n16\n12\n7\n23\n21\n28\n6\n1\n21\n2\n31\n20\n9\n5\n29\n17\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "60 1 4 1 28 1 11 1 15 1 24 1 35 1 17 1 36 1 26 1 31 1 33 1 39 1 19 1 2 1 0 1 23 1 25 1 18 1 32 1 8 1 5 1 21 1 7 1 12 1 14 1 20 1 27 1 6 1 10 1 1 1 30 1 38 1 13 1 37 1 3 1 16 1 29 1 34 1 9 1 22 2 4 2 10 2 11 2 15 2 14 2 16 2 17 2 1 2 6 2 9 2 3 2 7 2 19 2 2 2 0 2 12 2 5 2 18 2 13 2 8";
		Run(input, output);
		assert(output.str() == "0\n0\n1\n1\n1\n0\n3\n0\n3\n2\n2\n0\n8\n13\n14\n8\n7\n11\n4\n16\n17\n11\n18\n16\n16\n12\n7\n23\n21\n28\n6\n1\n21\n2\n31\n20\n9\n5\n29\n17\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "61 1 4 1 28 1 11 1 15 1 24 1 35 1 17 1 36 1 26 1 31 1 33 1 39 1 19 1 2 1 0 1 23 1 25 1 18 1 32 1 8 1 5 1 21 2 4 2 3 2 1 2 6 2 0 2 5 2 2 1 7 1 12 1 14 1 20 1 27 2 4 2 3 2 1 2 6 2 0 2 5 2 2 1 6 1 10 1 1 1 30 1 38 1 13 1 37 1 3 2 4 2 3 2 1 2 6 2 0 2 5 2 2 1 16 1 29 1 34 1 9 1 22";
		Run(input, output);
		assert(output.str() == "0\n0\n1\n1\n1\n0\n3\n0\n3\n2\n2\n0\n8\n13\n14\n8\n7\n11\n4\n16\n17\n11\n11\n9\n9\n5\n2\n9\n7\n14\n0\n0\n7\n1\n17\n2\n1\n0\n8\n3\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "100 1 92 1 51 1 11 1 69 1 24 1 35 1 17 1 36 1 26 1 98 1 67 1 39 1 83 1 2 1 75 1 56 1 59 1 18 1 32 1 40 1 91 1 86 1 57 1 12 1 14 1 42 1 27 1 62 1 63 1 58 1 30 1 96 1 13 1 68 1 3 1 87 1 71 1 64 1 9 1 22 1 66 1 80 1 20 1 79 1 89 1 81 1 73 1 0 1 94 1 41 1 88 1 28 1 52 1 43 1 16 1 60 1 49 1 7 1 84 1 72 1 29 1 61 1 6 1 45 1 53 1 76 1 8 1 33 1 37 1 15 1 25 1 55 1 70 1 31 1 82 1 47 1 48 1 10 1 90 1 34 1 23 1 74 1 77 1 19 1 85 1 44 1 93 1 54 1 97 1 1 1 38 1 95 1 4 1 21 1 99 1 5 1 78 1 65 1 50 1 46";
		Run(input, output);
		assert(output.str() == "0\n1\n2\n1\n3\n3\n5\n3\n5\n0\n3\n5\n2\n13\n3\n6\n6\n14\n12\n9\n2\n3\n9\n21\n21\n12\n18\n8\n8\n11\n21\n1\n29\n8\n33\n4\n8\n12\n36\n30\n12\n7\n33\n8\n4\n8\n12\n47\n2\n28\n6\n36\n27\n29\n46\n23\n30\n54\n9\n16\n42\n25\n59\n34\n31\n14\n61\n44\n42\n58\n52\n32\n19\n49\n11\n39\n39\n70\n5\n51\n62\n18\n16\n67\n10\n46\n3\n40\n1\n88\n55\n3\n88\n73\n0\n90\n21\n34\n49\n53\n");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "150 1 92 1 51 1 11 1 69 1 24 1 35 1 17 1 36 1 26 1 98 1 67 1 39 1 83 1 2 1 75 1 56 1 59 1 18 1 32 1 40 1 91 1 86 1 57 1 12 1 14 1 42 1 27 1 62 1 63 1 58 1 30 2 4 2 10 2 11 2 12 2 14 2 5 2 13 2 1 2 6 2 9 2 3 2 7 2 8 2 2 2 0 1 96 1 13 1 68 1 3 1 87 1 71 1 64 1 9 1 22 1 66 1 80 1 20 1 79 1 89 1 81 1 73 1 0 1 94 1 41 1 88 1 28 1 52 1 43 1 16 1 60 1 49 1 7 1 84 1 72 1 29 1 61 1 6 1 45 1 53 1 76 2 4 2 10 2 11 2 12 2 14 2 5 2 13 2 1 2 6 2 9 2 3 2 7 2 8 2 2 2 0 1 8 1 33 1 37 1 15 1 25 1 55 1 70 1 31 1 82 1 47 1 48 1 10 1 90 1 34 1 23 1 74 1 77 1 19 1 85 1 44 1 93 1 54 1 97 1 1 1 38 1 95 1 4 1 130 1 92 1 51 1 11 1 69 1 24 1 35 1 17 1 36 1 26 1 98 1 67 1 39 1 83 1 2 1 75 1 56 1 59 1 18 1 32 1 40 1 91 1 86 1 57 1 12 1 14 1 42 1 27 1 62 1 63 1 58 1 30 2 4 2 10 2 11 2 12 2 14 2 5 2 13 2 1 2 6 2 9 2 3 2 7 2 8 2 2 2 0 1 96 1 13 1 68 1 3 1 87 1 71 1 64 1 9 1 22 1 66 1 80 1 20 1 79 1 89 1 81 1 73 1 0 1 94 1 41 1 88 1 28 1 52 1 43 1 16 1 60 1 49 1 7 1 84 1 72 1 29 1 61 1 6 1 45 1 53 1 76 2 4 2 10 2 11 2 12 2 14 2 5 2 13 2 1 2 6 2 9 2 3 2 7 2 8 2 2 2 0 1 8 1 33 1 37 1 15 1 25 1 55 1 70 1 31 1 82 1 47 1 48  1 10 1 90 1 34 1 23 1 74 1 77 1 19 1 85 1 44 1 93 1 54 1 97 1 1 1 38 1 95 1 4 1 21 1 99 1 5 1 78 1 65 1 50 1 46 21 1 99 1 5 1 78 1 65 1 50 1 46";
		Run(input, output);
		assert(output.str() == "0\n1\n2\n1\n3\n3\n5\n3\n5\n0\n3\n5\n2\n13\n3\n6\n6\n14\n12\n9\n2\n3\n9\n21\n21\n12\n18\n8\n8\n11\n21\n0\n14\n2\n18\n2\n3\n6\n21\n15\n6\n3\n18\n4\n2\n4\n7\n32\n1\n17\n4\n21\n18\n19\n31\n16\n20\n39\n6\n11\n27\n18\n44\n24\n22\n10\n31\n15\n15\n28\n22\n8\n5\n19\n1\n14\n14\n40\n1\n22\n32\n6\n5\n37\n2\n21\n0\n16\n0\n58\n28\n1\n58\n0\n4\n23\n56\n16\n45\n35\n53\n35\n45\n1\n18\n35\n9\n75\n15\n24\n23\n61\n46\n38\n6\n9\n27\n74\n72\n40\n");
	}

}

int main()
{
	//TestSolution();
	Run(std::cin, std::cout);
	return 0;
}
