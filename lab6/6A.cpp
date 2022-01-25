#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct List {
	int key;
	List* left;
	List* right;

	List(int key, List* left, List* right) {
		this->key = key;
		this->left = left;
		this->right = right;
	}
};

struct Tree {
	Tree(List* l) {
		this->root = l;
	}

	Tree(vector<vector<int>> const& a) {
		this->root = make_tree(a, 0);
	}

	int height() { 
		return tree_height(this->root);
	}

private:
	List* root;

	int tree_height(List* t) {
		if (t->left != 0 && t->right != 0)
			return max(tree_height(t->left), tree_height(t->right)) + 1;
		else if (t->left != 0)
			return tree_height(t->left) + 1;
		else if (t->right != 0)
			return tree_height(t->right) + 1;
		else
			return 1;
	}

	List* make_tree(vector<vector<int>> const& a, int start_point) {
		List* left;
		List* right;

		if (a[start_point][1] != 0)
			left = make_tree(a, a[start_point][1]);
		else
			left = 0;

		if (a[start_point][2] != 0)
			right = make_tree(a, a[start_point][2]); 
		else
			right = 0;

		return new List(a[start_point][0], left, right);
	}
};

int main() {
	ifstream fin("height.in");
	ofstream fout("height.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}
	
	int n;
	fin >> n;
	if (!n) {
		fout << 0;
		return 0;
	}
	
	vector<vector<int>> a(n, vector<int>(3));
	for (int i = 0; i < n; ++i) {
		int k, l, r;
		fin >> k >> l >> r;
		a[i] = {k, (l != 0 ? l-1 : 0), (r != 0 ? r-1 : 0)};
	}
	
	Tree root(a);
	fout << root.height();
	return 0;
}