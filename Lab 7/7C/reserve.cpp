/*#include <fstream>
#include <iostream>

using namespace std;

struct elm {
    int x;
    int left, right;
    int parent;
};
elm a[200001];
elm ans[200001];

pair <int, int> balance(int n) {
    int i = n;
    pair <int, int> t = {0, 0};
    int left = 0, right = 0;
    if (a[i].left != 0) {
        t = balance(a[i].left);
        left += max(t.first, t.second) + 1;
    }
    if (a[i].right != 0) {
        t = balance(a[i].right);
        right += max(t.first, t.second) + 1;
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
    swap(a, ans);
}

int rotate(int balance, int root) {
    if (balance > 1) {
        if (balance == -1) {
            int indexA = root;
            int indexB = a[indexA].right;
            int indexC = a[indexB].left;
            swap(a[indexA], a[indexC]);
            swap(indexA, indexC);

            a[indexA].right = a[indexC].left;
            a[indexC].left = indexA;
            a[indexB].left = a[indexC].right;
            a[indexC].right = indexB;
            return indexA;
        }
        else {
            int indexA = root;
            int indexB = a[indexA].right;
            swap(a[indexA], a[indexB]);
            swap(indexA, indexB);

            a[indexA].right = a[indexB].left;
            a[indexB].left = indexA;
            return indexA;
        }
    }
    if (balance < -1) {
        if (balance == 1) {
            int indexA = root;
            int indexB = a[indexA].left;
            int indexC = a[indexB].right;
            swap(a[indexA], a[indexC]);
            swap(indexA, indexC);

            a[indexA].left = a[indexC].right;
            a[indexC].right = indexA;
            a[indexB].right = a[indexC].left;
            a[indexC].left = indexB;
            return indexA;
        }
        else {
            int indexA = root;
            int indexB = a[indexA].left;
            swap(a[indexA], a[indexB]);
            swap(indexA, indexB);

            a[indexA].left = a[indexB].right;
            a[indexB].right = indexA;
            return indexA;
        }
    }
    return -1;
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
    a[n] = {x, 0, 0};


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
        a[i] = {x, y, z};
        a[y].parent = i;
        a[z].parent = i;
    }
    int x;
    fin >> x;

    push(x, n);
    rec(1);
    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        fout << a[i].x << " " << a[i].left << " " << a[i].right << "\n";
    }

    fin.close();
    fout.close();
    return 0;
} */