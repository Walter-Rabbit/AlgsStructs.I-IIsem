#include <fstream>

using namespace std;

struct AVLtree {

private:
    struct elm {
        int x;
        int left, right;
        int parent;
    };
    int begining = 1;
    int size = 0;
    int field = 0;
    elm a[2001] = {{0, 0, 0, 0}};//размер 200001

    pair <int, int> balanceCount(int n) {
        a[0] = {0, 0, 0, 0};
        int i = n;
        pair <int, int> t = {0, 0};
        int left = 0, right = 0;
        if (a[i].left != 0) {
            t = balanceCount(a[i].left);
            left += max(t.first, t.second) + 1;
        }
        else {
            left++;
        }

        if (a[i].right != 0) {
            t = balanceCount(a[i].right);
            right += max(t.first, t.second) + 1;
        }
        else {
            right++;
        }
        if (left == 0 && right == 0) {
            return {1, 1};
        }

        return {left, right};
    }

    int rotate(int balance, int root) {
        if (balance > 1) {
            pair <int, int> t = balanceCount(a[root].right);
            int balanceKid = t.second - t.first;
            if (balanceKid == -1) {
                int indexA = root;
                int indexB = a[indexA].right;
                int indexC = a[indexB].left;
                int parentA = a[indexA].parent;

                a[indexA].right = a[indexC].left;
                a[a[indexA].right].parent = indexA;
                a[indexA].parent = indexC;

                a[indexB].left = a[indexC].right;
                a[a[indexB].left].parent = indexB;
                a[indexB].parent = indexC;

                a[indexC].left = indexA;
                a[indexC].right = indexB;
                a[indexC].parent = parentA;

                if (parentA == 0) {
                    begining = indexC;
                }
                else {
                    if (a[parentA].x > a[indexC].x) {
                        a[parentA].left = indexC;
                    } else {
                        a[parentA].right = indexC;
                    }
                }

                return indexC;
            }
            else {
                int indexA = root;
                int indexB = a[indexA].right;
                int parentA = a[indexA].parent;

                a[indexA].right = a[indexB].left;
                a[a[indexA].right].parent = indexA;
                a[indexA].parent = indexB;

                a[indexB].left = indexA;
                a[a[indexB].left].parent = indexB;
                a[indexB].parent = parentA;

                if (parentA == 0) {
                    begining = indexB;
                }
                else {
                    if (a[parentA].x > a[indexB].x) {
                        a[parentA].left = indexB;
                    } else {
                        a[parentA].right = indexB;
                    }
                }

                return indexB;
            }
        }
        if (balance < -1) {
            pair <int, int> t = balanceCount(a[root].left);
            int balanceKid = t.second - t.first;
            if (balanceKid == 1) {
                int indexA = root;
                int indexB = a[indexA].left;
                int indexC = a[indexB].right;
                int parentA = a[indexA].parent;

                a[indexA].left = a[indexC].right;
                a[a[indexA].left].parent = indexA;
                a[indexA].parent = indexC;

                a[indexB].right = a[indexC].left;
                a[a[indexB].right].parent = indexB;
                a[indexB].parent = indexC;

                a[indexC].right = indexA;
                a[indexC].left = indexB;
                a[indexC].parent = parentA;

                if (parentA == 0) {
                    begining = indexC;
                }
                else {
                    if (a[parentA].x > a[indexC].x) {
                        a[parentA].left = indexC;
                    } else {
                        a[parentA].right = indexC;
                    }
                }

                return indexC;
            }
            else {
                int indexA = root;
                int indexB = a[indexA].left;
                int parentA = a[indexA].parent;

                a[indexA].left = a[indexB].right;
                a[a[indexA].left].parent = indexA;
                a[indexA].parent = indexB;

                a[indexB].right = indexA;
                a[a[indexB].right].parent = indexB;
                a[indexB].parent = parentA;

                if (parentA == 0) {
                    begining = indexB;
                }
                else {
                    if (a[parentA].x > a[indexB].x) {
                        a[parentA].left = indexB;
                    } else {
                        a[parentA].right = indexB;
                    }
                }

                return indexB;
            }
        }
        return a[root].parent;
    }

    void balancing(int i) {
        while (i != 0) {
            pair<int, int> t = balanceCount(i);
            i = rotate(t.second - t.first, i);
        }
    }

public:
    int push(int x) {
        int i = begining;
        if (size == 0) {
            a[1] = {x, 0, 0, 0};
            size = 1;
            field = 1;
            return 0;
        }
        while (true) {
            if (x == a[i].x) {
                pair <int, int> t = balanceCount(begining);
                return t.second - t.first;
            }
            if (x < a[i].x && a[i].left != 0) {
                i = a[i].left;
                continue;
            }
            if (x < a[i].x && a[i].left == 0) {
                a[i].left = field + 1;
                field++;
                break;
            }
            if (x > a[i].x && a[i].right != 0) {
                i = a[i].right;
                continue;
            }
            if (x > a[i].x && a[i].right == 0) {
                a[i].right = field + 1;
                field++;
                break;
            }
        }
        size++;
        a[field] = {x, 0, 0, i};

        balancing(field);
        pair <int, int> t = balanceCount(begining);
        return t.second - t.first;
    }

    int extract(int x) {
        if (size == 0) {
            return 0;
        }

        int index = begining;
        while (true) {
            if (x == a[index].x) {
                break;
            }
            if (x < a[index].x && a[index].left != 0) {
                index = a[index].left;
                continue;
            }
            if (x < a[index].x && a[index].left == 0) {
                pair <int, int> t = balanceCount(begining);
                return t.second - t.first;
            }
            if (x > a[index].x && a[index].right != 0) {
                index = a[index].right;
                continue;
            }
            if (x > a[index].x && a[index].right == 0) {
                pair <int, int> t = balanceCount(begining);
                return t.second - t.first;
            }
        }
        size--;

        int indexParent = a[index].parent;
        int indexLeft = a[index].left;
        int indexRight = a[index].right;

        if (indexLeft == 0 && indexRight== 0) {
            if (indexParent == 0) {
                a[1] = {0, 0, 0, 0};
                size = 0;
                begining = 1;
            }
            else {
                if (a[index].x > a[indexParent].x) {
                    a[indexParent].right = 0;
                }
                else {
                    a[indexParent].left = 0;
                }
            }
            balancing(indexParent);
            pair <int, int> t = balanceCount(begining);
            return t.second - t.first;
        }

        if (indexLeft == 0) {
            if (a[index].x > a[indexParent].x) {
                a[indexParent].right = a[index].right;
            }
            else {
                a[indexParent].left = a[index].right;
            }
            a[indexRight].parent = indexParent;
            if (a[indexRight].parent == 0) {
                begining = indexRight;
            }
            balancing(indexParent);
            pair <int, int> t = balanceCount(begining);
            return t.second - t.first;
        }

        else {
            int indexMax = indexLeft;
            while (a[indexMax].right != 0) {
                indexMax = a[indexMax].right;
            }

            elm copy = a[indexMax];
            int indexMaxParent = a[indexMax].parent;
            int indexMaxLeft = a[indexMax].left;

            if (a[index].x > a[indexParent].x) {
                a[indexParent].right = indexMax;
            }
            else {
                a[indexParent].left = indexMax;
            }

            a[indexMax].parent = indexParent;
            if (indexLeft != indexMax) {
                a[indexLeft].parent = indexMax;
                a[indexMax].left = indexLeft;
            }
            if (indexRight != indexMax) {
                a[indexRight].parent = indexMax;
                a[indexMax].right = indexRight;
            }
            if (a[indexMax].parent == 0) {
                begining = indexMax;
            }

            if (copy.left == 0 && copy.right == 0) {
                if (copy.x > a[indexMaxParent].x) {
                    a[indexMaxParent].right = 0;
                }
                else {
                    a[indexMaxParent].left = 0;
                }
                if (a[indexMaxParent].x == x) {
                    indexMaxParent = indexMax;
                }
                balancing(indexMaxParent);
                pair <int, int> t = balanceCount(begining);
                return t.second - t.first;
            }

            if (copy.left != 0 && copy.right == 0) {
                if (copy.x > a[indexMaxParent].x) {
                    a[indexMaxParent].right = copy.left;
                }
                else {
                    a[indexMaxParent].left = copy.left;
                }
                a[indexMaxLeft].parent = indexMaxParent;
                if (a[indexMaxParent].x == x) {
                    indexMaxParent = indexMax;
                }
                balancing(indexMaxParent);
                pair <int, int> t = balanceCount(begining);
                return t.second - t.first;
            }
        }

        pair <int, int> t = balanceCount(begining);
        return t.second - t.first;
    }

    bool exist(int x) {
        if (size == 0) {
            return false;
        }

        int index = begining;
        while (true) {
            if (x == a[index].x) {
                return true;
            }
            if (x < a[index].x && a[index].left != 0) {
                index = a[index].left;
                continue;
            }
            if (x < a[index].x && a[index].left == 0) {
                return false;
            }
            if (x > a[index].x && a[index].right != 0) {
                index = a[index].right;
                continue;
            }
            if (x > a[index].x && a[index].right == 0) {
                return false;
            }
        }
    }
};

int main() {
    ifstream fin("avlset.in");
    ofstream fout("avlset.out");

    AVLtree a;
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        int x;
        fin >> c >> x;

        if (c == 'A') {
            fout << a.push(x) << "\n";
            continue;
        }

        if (c == 'D') {
            fout << a.extract(x) << "\n";
            continue;
        }

        if (c == 'C') {
            if (a.exist(x)) {
                fout << "Y\n";
            }
            else {
                fout << "N\n";
            }
            continue;
        }

    }

    fin.close();
    fout.close();
    return 0;
}