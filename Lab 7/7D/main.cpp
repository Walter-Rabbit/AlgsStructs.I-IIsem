#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

struct elm {
    int x;
    int left, right;
    int parent;
};
int begining = 1;
elm a[200001];

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
        pair <int, int> t = balanceCount(i);
        i = rotate(t.second - t.first, i);
    }
}

void extract(int x, int& n) {
    if (n == 0) {
        return;
    }

    int index = 1;
    while (true) {
        if (x == a[index].x) {
            break;
        }
        if (x < a[index].x && a[index].left != 0) {
            index = a[index].left;
            continue;
        }
        if (x < a[index].x && a[index].left == 0) {
            return;
        }
        if (x > a[index].x && a[index].right != 0) {
            index = a[index].right;
            continue;
        }
        if (x > a[index].x && a[index].right == 0) {
            return;
        }
    }
    n--;

    int indexParent = a[index].parent;
    int indexLeft = a[index].left;
    int indexRight = a[index].right;

    if (indexLeft == 0 && indexRight== 0) {
        if (indexParent == 0) {
            a[1] = {0, 0, 0, 0};
            n = 0;
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
        return;
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
        return;
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
            return;
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
            return;
        }
    }
}

int main() {
    ifstream fin("deletion.in");
    ofstream fout("deletion.out");

    a[0] = {0, 0, 0};

    int n;
    fin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        a[i].x = x;
        a[i].left = y;
        a[i].right = z;
        a[y].parent = i;
        a[z].parent = i;
    }

    int x;
    fin >> x;

    extract(x, n);

    fout << n << "\n";
    if (n != 0) {
        queue<int> q;
        q.push(begining);
        int i = 1;
        while (!q.empty()) {
            elm temp = {a[q.front()].x, a[q.front()].left, a[q.front()].right};
            q.pop();

            if (temp.left != 0) {
                q.push(temp.left);
                i++;
                temp.left = i;
            }

            if (temp.right != 0) {
                q.push(temp.right);
                i++;
                temp.right = i;
            }
            fout << temp.x << " " << temp.left << " " << temp.right << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}

