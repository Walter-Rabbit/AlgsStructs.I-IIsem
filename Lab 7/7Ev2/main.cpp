#include <fstream>

using namespace std;

struct AVLtree {
private:

    struct node {
        int key;
        int height;
        node* left;
        node* right;

        node(int x) {
            key = x;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    static int _height(node* p) {
        if (p == nullptr) {
            return 0;
        }
        return p->height;
    }

    static node* _newHeight(node* p) {
        int heightLeft = _height(p->left);
        int heightRight = _height(p->right);
        p->height = max(heightLeft, heightRight) + 1;
        return p;
    }

    static int _balanceCount(node* p) {
        int heightLeft = _height(p->left);
        int heightRight = _height(p->right);
        return heightRight - heightLeft;
    }

    static node* _rotateRight(node* A) {
        node* B = A->left;
        A->left = B->right;
        B->right = A;

        _newHeight(A);
        _newHeight(B);
        return B;
    }

    static node* _rotateLeft(node* A) {
        node* B = A->right;
        A->right = B->left;
        B->left = A;

        _newHeight(A);
        _newHeight(B);
        return B;
    }

    static node* _balancing(node* p) {
        _newHeight(p);

        if (_balanceCount(p) == 2) {
            if (_balanceCount(p->right) == -1) {
                p->right = _rotateRight(p->right);
            }
            _rotateLeft(p);
            return;
        }

        if (_balanceCount(p) == -2) {
            if (_balanceCount(p->left) == 1) {
                p->left = _rotateLeft(p->left);
            }
            _rotateRight(p);
            return;
        }
    }

public:

    static node* insert(node* p, int x) {
        if (p == nullptr) {
            return;
        }
    }
};

int main() {
    ifstream fin("avlset.in");
    ofstream fout("avlset.out");

    fin.close();
    fout.close();
    return 0;
}
