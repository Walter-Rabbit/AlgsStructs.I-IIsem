#include <fstream>
#include <string>

using namespace std;

struct elm {
    int key, parent;
    int left, right;
};

struct tree {
    int size = 0;
    int begining = 1;
    elm tree[101] = {{0, 0, 0, 0}};

    void insert(int x) {
        tree[0] = {0, 0, 0, 0};

        int index = begining;
        if (size == 0) {
            size++;
            tree[size].parent = 0;
            tree[size].right = 0;
            tree[size].left = 0;
            tree[size].key = x;
            return;
        }
        while (true) {
            int indexOfRight = tree[index].right;
            int indexOfLeft = tree[index].left;
            if (tree[index].key < x) {
                if (indexOfRight == 0) {
                    size++;
                    tree[index].right = size;
                    tree[size].parent = index;
                    tree[size].key = x;
                    break;
                }
                index = indexOfRight;
            }
            else if (tree[index].key > x) {
                if (indexOfLeft == 0) {
                    size++;
                    tree[index].left = size;
                    tree[size].parent = index;
                    tree[size].key = x;
                    break;
                }
                index = indexOfLeft;
            }
            else if (tree[index].key == x) {
                break;
            }
        }
    }

    bool exists(int x) {
        tree[0] = {0, 0, 0, 0};
        int index = begining;
        while (true) {
            if (index == 0 || size == 0) {
                return false;
            }
            else if (tree[index].key == x) {
                return true;
            }
            else if (tree[index].key < x) {
                index = tree[index].right;
            }
            else if (tree[index].key > x) {
                index = tree[index].left;
            }
        }
    }

    void extract(int x) {
        tree[0] = {0, 0, 0, 0};
        int index = begining;
        while (true) {
            int indexOfParent = tree[index].parent;
            int indexOfLeft = tree[index].left;
            int indexOfRight = tree[index].right;
            if (index == 0) {
                return;
            }
            else if (tree[index].key < x) {
                index = indexOfRight;
            }
            else if (tree[index].key > x){
                index = indexOfLeft;
            }
            else if (tree[index].key == x) {


                if (tree[index].left == 0 && tree[index].right == 0) {
                    if (tree[index].parent == 0) {
                        tree[1] = {0, 0, 0 ,0};
                        size = 0;
                        begining = 1;
                    }
                    else {
                        if (tree[index].key > tree[indexOfParent].key) {
                            tree[indexOfParent].right = 0;
                        } else {
                            tree[indexOfParent].left = 0;
                        }
                    }
                    return;
                }


                if (tree[index].left != 0 && tree[index].right == 0) {
                    if (tree[index].key > tree[indexOfParent].key) {
                        tree[indexOfParent].right = tree[index].left;
                    }
                    else {
                        tree[indexOfParent].left = tree[index].left;
                    }
                    tree[indexOfLeft].parent = indexOfParent;
                    if (tree[indexOfLeft].parent == 0) {
                        begining = indexOfLeft;
                    }
                    return;
                }


                if (tree[index].left == 0 && tree[index].right != 0) {
                    if (tree[index].key > tree[indexOfParent].key) {
                        tree[indexOfParent].right = tree[index].right;
                    }
                    else {
                        tree[indexOfParent].left = tree[index].right;
                    }
                    tree[indexOfRight].parent = indexOfParent;
                    if (tree[indexOfRight].parent == 0) {
                        begining = indexOfRight;
                    }
                    return;
                }


                if (tree[index].left != 0 && tree[index].right != 0) {
                    int indexOfMax = indexOfLeft;

                    while (tree[indexOfMax].right != 0) {
                        indexOfMax = tree[indexOfMax].right;
                    }
                    elm copy = tree[indexOfMax];
                    int indexOfMaxParent = tree[indexOfMax].parent;
                    int indexOfMaxLeft = tree[indexOfMax].left;

                    if (tree[index].key > tree[indexOfParent].key) {
                        tree[indexOfParent].right = indexOfMax;
                    }
                    else {
                        tree[indexOfParent].left = indexOfMax;
                    }

                    tree[indexOfMax].parent = indexOfParent;
                    if (indexOfLeft != indexOfMax) {
                        tree[indexOfLeft].parent = indexOfMax;
                        tree[indexOfMax].left = indexOfLeft;
                    }
                    if (indexOfRight != indexOfMax) {
                        tree[indexOfRight].parent = indexOfMax;
                        tree[indexOfMax].right = indexOfRight;
                    }
                    if (tree[indexOfMax].parent == 0) {
                        begining = indexOfMax;
                    }

                    if (copy.left == 0 && copy.right == 0) {
                        if (copy.key > tree[indexOfMaxParent].key) {
                            tree[indexOfMaxParent].right = 0;
                        }
                        else {
                            tree[indexOfMaxParent].left = 0;
                        }
                    }

                    else if (copy.left != 0 && copy.right == 0) {
                        if (copy.key > tree[indexOfMaxParent].key) {
                            tree[indexOfMaxParent].right = copy.left;
                        }
                        else {
                            tree[indexOfMaxParent].left = copy.left;
                        }
                        tree[indexOfMaxLeft].parent = indexOfMaxParent;
                    }
                    return;
                }
            }
        }
    }

    int next(int x) {
        tree[0] = {0, 0, 0, 0};
        int index = begining;
        int mn = INT_MAX;
        if (size != 0) {
            while (true) {
                if (index == 0) {
                    return mn;
                }
                if (tree[index].key <= x) {
                    index = tree[index].right;
                } else {
                    mn = tree[index].key;
                    index = tree[index].left;
                }
            }
        }
        return mn;
    }

    int prev(int x) {
        tree[0] = {0, 0, 0, 0};
        int index = begining;
        int mx = INT_MIN;
        if (size != 0) {
            while (true) {
                if (index == 0) {
                    return mx;
                }
                if (tree[index].key < x) {
                    mx = tree[index].key;
                    index = tree[index].right;
                } else {
                    index = tree[index].left;
                }
            }
        }
        return mx;
    }
};

int main() {
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");

    string st;
    int x;
    tree a;
    while (fin >> st) {
        fin >> x;
        if (st == "insert") {
            a.insert(x);
        }
        else if (st == "exists") {
            if (a.exists(x)) {
                fout << "true\n";
            }
            else {
                fout << "false\n";
            }
        }
        else if (st == "delete") {
            a.extract(x);
        }
        else if (st == "next") {
            int temp = a.next(x);
            if (temp == INT_MAX) {
                fout << "none\n";
            }
            else {
                fout << temp << "\n";
            }
        }
        else if (st == "prev") {
            int temp = a.prev(x);
            if (temp == INT_MIN) {
                fout << "none\n";
            }
            else {
                fout << temp << "\n";
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}