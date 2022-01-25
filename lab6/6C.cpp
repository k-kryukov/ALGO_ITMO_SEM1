#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>

using namespace std;

const int INF = 2000000000;

struct List {
	int key;
	List* left;
	List* right;
	List* parent;

	List(int key, List* left, List* right, List* parent) {
		this->key = key;
		this->left = left;
		this->right = right;
		this->parent = parent;
	}
};

void swap(List* a, List* b) {
	swap(a->key, b->key);
}

ostream& operator<<(ostream& stream, List* v) {
	stream << v->key << '\n';
	return stream;
}

struct Tree {

	Tree() {
		root = 0;
	}

	Tree(List* v) {
		this->root = v;
	}

	void insert(int new_value) {
		if (root == 0) {
			this->root = new List(new_value, 0, 0, 0);
			return;
		}

		List* temp = root;
		List* prev = root;
		bool first_iteration = true;
		
		while (temp != NULL) {
			if (!first_iteration)
				prev = temp;
			else
				first_iteration = false;

			if (new_value > temp->key) {
				if (temp->right == NULL) {
					temp->right = new List(new_value, 0, 0, temp);
					return;
				}

				temp = temp->right;
			}
			else if (new_value < temp->key) {
				if (temp->left == NULL) {
					temp->left = new List(new_value, 0, 0, temp);
					return;
				}

				temp = temp->left;
			}
			else
				return;
		}
	}

	List* find(int key) {
		List* cur = root;

		while (cur != NULL) {
			if (key == cur->key)
				return cur;
			else if (key > cur->key)
				cur = cur->right;
			else
				cur = cur->left;
		}

		return cur;
	}

	bool exists(int key) {
		List* cur = this->find(key);

		return cur == NULL ? false : true;
	}

	void print() {
		print_tree(this->root, 0);
		cout << "\n\n\n";
	}

	void delete_value(int key) {
		List* node = this->find(key);

		if (!node) {
			return;
		}

		if (node->left == NULL || node->right == NULL)
			delete_not_full_key(node);
		else {
			List* cur = node->left;
			while (cur->right != NULL) {
				cur = cur->right;
			}
			swap(cur, node);
			delete_not_full_key(cur);
		}
	}

	int get_max() const {
		if (!root)
			return -INF;

		List* cur = root;
		while (cur->right != NULL) {
			cur = cur->right;
		}

		return cur->key;
	}

	int get_min() const {
		if (!root)
			return INF;

		List* cur = root;
		while (cur->left != NULL) {
			cur = cur->left;
		}

		return cur->key;
	}

	int successor(int x) {
		List* cur_el = this->find(x);
		if (cur_el->key == get_max())
			return -INF;

		if (cur_el->right != NULL) {
			List* temp = cur_el->right;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			return temp->key;
		}
		else {
			List* temp = cur_el;
			while (temp->parent->left != temp) {
				temp = temp->parent;
			}
			return temp->parent->key;
		}
	}

	int preccessor(int x) {
		List* cur_el = this->find(x);
		if (cur_el->key == get_min())
			return INF;

		if (cur_el->left != NULL) {
			List* temp = cur_el->left;
			while (temp->right != NULL) {
				temp = temp->right;
			}
			return temp->key;
		}
		else {
			List* temp = cur_el;
			while (temp->parent->right != temp) {
				temp = temp->parent;
			}
			return temp->parent->key;
		}
	}

	void print_sorted() {
		bfs_with_print(this->root);
	}

private:
	List* root;

	void bfs_with_print(List* root) {
		if (!root)
			return;

		bfs_with_print(root->left);
		cout << root->key << " ";
		bfs_with_print(root->right);
	}

	void print_tree(List* root, int depth) {
		if (root == NULL)
			return;

		print_tree(root->right, depth + 1);
		cout << generate_spaces(depth * 2) << root->key << '\n';
		print_tree(root->left, depth + 1);
	}

	string generate_spaces(int counter) {
		string s = "";
		for (int i = 0; i < counter; ++i)
			s += '|';

		return s;
	}

	void delete_not_full_key(List* cur) {
		if (cur->left == NULL && cur->right == NULL) {
			if (cur == root) {
				delete cur;
				this->root = 0;
			}
			else {
				bool cur_is_left_child = (cur->parent->left == cur);
				if (cur_is_left_child)
					cur->parent->left = 0;
				else
					cur->parent->right = 0;

				delete cur;
			}
		}
		else if (cur->left == NULL) {
			if (cur == root) {
				root = cur->right;
				root->parent = 0;
				delete cur;
			}
			else {
				bool cur_is_left_child = (cur->parent->left == cur);
				if (cur_is_left_child) {
					cur->parent->left = cur->right;
					cur->right->parent = cur->parent;
				}
				else {
					cur->parent->right = cur->right;
					cur->right->parent = cur->parent;
				}

				delete cur;
			}
		}
		else {
			if (cur == root) {
				root = cur->left;
				root->parent = 0;
				delete cur;
			}
			else {
				bool cur_is_left_child = (cur->parent->left == cur);
				if (cur_is_left_child) {
					cur->parent->left = cur->left;
					cur->left->parent = cur->parent;
				}
				else {
					cur->parent->right = cur->left;
					cur->left->parent = cur->parent;
				}

				delete cur;
			}
		}
	}
};



int main() {
	ifstream fin("bstsimple.in");
	ofstream fout("bstsimple.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}

	Tree t;
	string s;

	while (fin >> s) {
		int x;
		fin >> x;
		if (s == "insert") {
			t.insert(x);
		}
		else if (s == "delete") {
			t.delete_value(x);
		}
		else if (s == "exists") {
			t.exists(x) ? fout << "true\n" : fout << "false\n";
		}
		else if (s == "next") {
			bool need_to_be_deleted = !t.exists(x);
			if (need_to_be_deleted)
				t.insert(x);

			int succ = t.successor(x);
			(succ == -INF) ? fout << "none\n" : fout << succ << endl;
			
			if (need_to_be_deleted)
				t.delete_value(x);
		}
		else if (s == "prev") {
			bool need_to_be_deleted = !t.exists(x);
			if (need_to_be_deleted)
				t.insert(x);

			int precc = t.preccessor(x);
			(precc == INF) ? fout << "none\n" : fout << precc << endl;
			
			if (need_to_be_deleted)
				t.delete_value(x);
		}
	}

	fin.close();
	fout.close();
	return 0;
}