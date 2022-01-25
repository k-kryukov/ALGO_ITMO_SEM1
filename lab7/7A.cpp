// FOR EACH VERTEX OF BINARY TREE PRINT HER "BALANCE"
// BALANCE B(V) = abs(H(V.LEFT) - H(V.RIGHT))
// THE WAY TREE IS GIVEN: EACH LINE = *value* *number_left_child* *number_right_child*

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int value;
    int height;
    Node* left;
    Node* right;

    Node(int value, Node* left, Node* right, int height) {
        this->value = value;
        this->left = left;
        this->right = right;
        this->height = height;
    }
};

class Tree {
    Node* root;
    vector<int> heights;
    vector<int> balances;

    Node* get_tree(vector<vector<int>> const& input, size_t cur) {
        Node* left = 0;
        Node* right = 0;

        left = (input[cur][1] == 0 ? NULL : get_tree(input, input[cur][1]));
        right = (input[cur][2] == 0 ? NULL : get_tree(input, input[cur][2]));

        int height;
        if (left != 0 && right != 0) {
            height = max(right->height, left->height) + 1;
        }
        else if (left != 0) {
            height = left->height + 1;
        }
        else if (right != 0) {
            height = right->height + 1;
        }
        else {
            height = 1;
        }
            

        heights[cur] = height;
        balances[cur] = (right != NULL ? right->height : 0) - (left != NULL ? left->height : 0);

        return new Node(input[cur][0], left, right, height);
    }

    void print_tree(Node* root, unsigned int depth) {
        if (root == NULL)
            return;
        
        print_tree(root->right, depth + 1);
        cout << string(2 * depth, ' ') << root->value << '\n';
        print_tree(root->left, depth + 1);
    }

public:
    Tree(vector<vector<int>> const& input) {
        heights.resize(input.size());
        balances.resize(input.size());

        this->root = get_tree(input, 0);
    }

    void print() {
        print_tree(this->root, 0);
    }

    void print_heights(ofstream& out) {
        for (auto x : heights) {
            out << x << endl;
        }
    }

    void print_balances(ofstream& out) {
        for (auto x : balances) {
            out << x << endl;
        }
    }
};

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    if (!fin) {
        cerr << "ERROR!\n";
        return -1;
    }

    int n;
    fin >> n;
    
    vector<vector<int>> input(n, vector<int> (3, 0));

    for (int i = 0; i < n; ++i) {
        int v, l, r;
        fin >> v >> l >> r;
        input[i] = {v, (l == 0 ? 0 : l - 1), (r == 0 ? 0 : r - 1)};
    }

    Tree t(input);
    t.print_balances(fout);

    return 0;
}
