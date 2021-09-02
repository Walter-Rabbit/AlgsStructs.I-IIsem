#include <fstream>
#include <iostream>

using namespace std;

struct elm {
    int x;
    int left, right;
    int parent;
};
int begining = 1;
elm a[200001];
elm ans[200001];

pair <int, int> balancing(int n) {
    a[0] = {0, 0, 0, 0};
    int i = n;
    pair <int, int> t = {0, 0};
    int left = 0, right = 0;
    if (a[i].left != 0) {
        t = balancing(a[i].left);
        left += max(t.first, t.second) + 1;
    }
    else {
        left++;
    }
    if (a[i].right != 0) {
        t = balancing(a[i].right);
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

int k = 1;
void rec(int i) {
    int pos = k;
    ans[pos].x = a[i].x;
    if (a[i].left != 0) {
        k++;
        ans[pos].left = k;
        rec(a[i].left);
    }
    if (a[i].right != 0) {
        k++;
        ans[pos].right = k;
        rec(a[i].right);
    }
}

int rotate(int balance, int root) {
    if (balance > 1) {
        pair <int, int> t = balancing(a[root].right);
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
        pair <int, int> t = balancing(a[root].left);
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

void push(int x, int& n) {
    int i = 1;
    if (n == 0) {
        a[1] = {x, 0, 0};
        n++;
        return;
    }
    while (true) {
        if (x == a[i].x) {
            return;
        }
        if (x < a[i].x && a[i].left != 0) {
            i = a[i].left;
            continue;
        }
        if (x < a[i].x && a[i].left == 0) {
            a[i].left = n + 1;
            break;
        }
        if (x > a[i].x && a[i].right != 0) {
            i = a[i].right;
            continue;
        }
        if (x > a[i].x && a[i].right == 0) {
            a[i].right = n + 1;
            break;
        }
    }
    n++;
    a[n] = {x, 0, 0, i};

    int j = n;
    while (j != 0) {
        pair <int, int> t = balancing(j);
        j = rotate(t.second - t.first, j);
    }
}

int main() {
    ifstream fin("addition.in");
    ofstream fout("addition.out");

    a[0] = {0, 0, 0};

    int n;
    fin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        a[i].x = x;
        a[i].left = y;
        a[i].right = z;;
        a[y].parent = i;
        a[z].parent = i;
    }
    int x;
    fin >> x;

    push(x, n);
    rec(begining);
    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        fout << ans[i].x << " " << ans[i].left << " " << ans[i].right << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}