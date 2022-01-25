#include <iostream>
#include <fstream>
#include <string>
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
	Tree(vector<vector<int>> const& a) {
		List* res = make_tree(a, 0);
		this->root = res;
	}

	void print(ostream& stream) {
		print_any_tree(this->root, 0, stream);
	}

	bool check_linear_search_tree() {
		return check_tree(this->root);
	}
private:
	List* root;

	string generate_spaces(int n) {
		string res;
		for (int i = 0; i < n; ++i)
			res += ' ';

		return res;
	}

	List* make_tree(vector<vector<int>> const& a, int start_point) {
		List* left;
		List* right;

		if (a[start_point][1] != 0)
			left = make_tree(a, a[start_point][1] - 1);
		else
			left = 0;

		if (a[start_point][2] != 0)
			right = make_tree(a, a[start_point][2] - 1);
		else
			right = 0;

		return new List(a[start_point][0], left, right);
	}

	void print_any_tree(List* t, int depth, ostream& stream) {
		if (t == NULL)
			return;

		print_any_tree(t->right, depth + 1, stream);
		cout << generate_spaces(depth * 2) << t->key << endl;
		print_any_tree(t->left, depth + 1, stream);
	}

	bool check_tree(List* t) {
		if (t == NULL || t->left == NULL && t->right == NULL)
			return true;

		bool left_is_ok = check_tree(t->left);
		bool right_is_ok = check_tree(t->right);

		if (t->left != NULL) {
			List* temp = t->left;
			int mx_left = temp->key;

			while (temp->right != NULL) {
				temp = temp->right;
				mx_left = temp->key;
			}

			if (t->key <= mx_left)
				return false;
		}

		if (t->right != NULL) {
			List* temp = t->right;
			int min_right = temp->key;

			while (temp->left != NULL) {
				temp = temp->left;
				min_right = temp->key;
			}

			if (t->key >= min_right)
				return false;
		}

		return left_is_ok && right_is_ok;
	}
};


int main() {
	ifstream fin("check.in");
	ofstream fout("check.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}

	int n;
	fin >> n;
	if (!n) {
		fout << "YES";
		return 0;
	}

	vector<vector<int>> a(n, vector<int>(3, 0));
	for (int i = 0; i < n; ++i) {
		int k, l, r;
		fin >> k >> l >> r;
		a[i] = {k,l,r};
	}

	Tree t(a);
	if (t.check_linear_search_tree())
		fout << "YES";
	else
		fout << "NO";
	return 0;
}