#include <iostream>
#include <random>

class Tree
{
	struct Node
	{
		int key;
		int size;
		Node* left;
		Node* right;

		Node(int key, int size = 0, Node* left = nullptr, Node* right = nullptr)
			:key(key), size(size), left(left), right(right) {}
	};

public:
	Tree()
		:rnd(std::random_device()()), root(nullptr) {}
	Tree(const Tree& other)
		:rnd(std::random_device()())
	{
		root = new Node{ other.root->key, other.root->size };
		other.preorder_copy(other.root, root, copy_func);
	}
	~Tree()
	{
		postorder_delete(root);
	}
	Node* find(int key)  { return find(key, root); }
	void insert(int key) { root = insert(key, root); }

	void print() const { print(root, 0); }

	void symmetric_print() const { symmetric(root, print_func); }
	void preorder_print()  const { preorder(root, print_func);  }
	void symmetric_f(void(*f_ptr)(int)) const { symmetric(root, f_ptr); }
	void preorder_f(void(*f_ptr)(int))  const { preorder(root, f_ptr); }

	// Добавление эл-тов в A из B в симм. порядке обхода
	Tree operator+(const Tree& other)
	{
		Tree r_tree{ *this };
		other.symmetric_copy(other.root, &r_tree, sym_copy_func);
		return r_tree;
	}
	
private:
	std::mt19937 rnd;
	Node* root;

	Node* find(int key, Node* p)
	{
		if (!root)
			return nullptr;
		if (key == p->key)
			return p;
		if (key < p->key)
			return find(key, p->left);
		
		return find(key, p->right);
	}

	void fixsize(Node* p)
	{
		int l_size = 0;
		int r_size = 0;
		if (p->left)  l_size = p->left->size;
		if (p->right) r_size = p->right->size;
		p->size = l_size + r_size + 1;
	}

	Node* rotate_r(Node* p)
	{
		Node* q = p->left;
		if (!q) return p;
		p->left = q->right;
		q->right = p;
		q->size = p->size;
		fixsize(p);
		return q;
	}

	Node* rotate_l(Node* q)
	{
		Node* p = q->right;
		if (!p) return q;
		q->right = p->left;
		p->left = q;
		p->size = q->size;
		fixsize(q);
		return p;
	}

	Node* insert_root(int k, Node* p)
	{
		if (!p) return new Node{ k };
		if (k < p->key)
		{
			p->left = insert_root(k, p->left);
			return rotate_r(p);
		}
		else
		{
			p->right = insert_root(k, p->right);
			return rotate_l(p);
		}
	}

	Node* insert(int key, Node* p)
	{
		if (!p) return new Node{ key, 1 };
		if (rnd() % (p->size + 1) == 0)
			return insert_root(key, p);
		if (p->key > key)
			p->left = insert(key, p->left);
		else
			p->right = insert(key, p->right);
		fixsize(p);
		return p;
	}

	void print(Node* p, int space) const
	{
		if (!p)
			return;

		space += 5;
		print(p->right, space);
		std::cout << "\n";
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << p->key << "\n";

		print(p->left, space);
	}

	void preorder(Node* p, void(*f_ptr)(int)) const
	{
		if (!p) return;
		
		f_ptr(p->key);
		preorder(p->left, f_ptr);
		preorder(p->right, f_ptr);
	}
	void symmetric(Node* p, void(*f_ptr)(int)) const
	{
		if (!p) return;

		symmetric(p->left, f_ptr);
		f_ptr(p->key);
		symmetric(p->right, f_ptr);
	}

	void symmetric_copy(Node* p, Tree* q, void(*f_ptr)(Node*, Tree*)) const
	{
		if (!p) return;

		symmetric_copy(p->left, q, f_ptr);
		f_ptr(p, q);
		symmetric_copy(p->right, q, f_ptr);
	}

	void preorder_copy(Node* p, Node* q, void(*f_ptr)(Node*, Node*)) const
	{
		if (!p) return;

		f_ptr(p, q);
		preorder_copy(p->left, q->left, f_ptr);
		preorder_copy(p->right, q->right, f_ptr);
	}

	void postorder_delete(Node* p)
	{
		if (!p) return;

		postorder_delete(p->left);
		postorder_delete(p->right);

		delete p;
	}

	static void print_func(int x) { std::cout << x << " "; }
	static void copy_func(Node* old_r, Node* new_r)
	{
		if (old_r->left)
		{
			new_r->left = new Node{ old_r->left->key, old_r->left->size };
		}
		if (old_r->right)
		{
			new_r->right = new Node{ old_r->right->key, old_r->right->size };
		}
	}
	static void sym_copy_func(Node* r, Tree* t)
	{
		t->insert(r->key);
	}
};

int main()
{
	srand(time(NULL));
	Tree t1, t2;

	for (int i = -5; i < 0; i++)
	{
		t1.insert(i);
	}
	for (int i = 1; i < 6; i++)
	{
		t2.insert(i);
	}

	std::cout << "Preorder t1: ";
	t1.preorder_print();
	std::cout << "\n";
	std::cout << "Symmetric t2: ";
	t2.symmetric_print();
	std::cout << "\n";

	const auto t3 = t1 + t2;
	std::cout << "Symmetric t1 + t2: ";
	t3.symmetric_print();

	std::cout << "\n";
	t3.print();
}