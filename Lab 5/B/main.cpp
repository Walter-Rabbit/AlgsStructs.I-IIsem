#include <fstream>

using namespace std;

struct elm {
    int left_parent, right_parent;
    int key, left, right;
};

bool fl = true;

void rec(elm* a, int i, int mx, int mn) {
    if (fl && mx < a[i].key) {
        mx = a[i].key;
    }
    if (fl && mn > a[i].key) {
        mn = a[i].key;
    }
    if (fl && a[i].left_parent != 0 && a[a[i].left_parent].key >= mn) {
        fl = false;
    }
    if (fl && a[i].right_parent != 0 && a[a[i].right_parent].key <= mx) {
        fl = false;
    }

    if (fl && a[i].right_parent != 0) {
        rec(a, a[i].right_parent, mx, mn);
    }
    if (fl && a[i].left_parent != 0) {
        rec(a, a[i].left_parent, mx, mn);
    }
}

int main() {
    ifstream fin("check.in");
    ofstream fout("check.out");


    int n;
    fin >> n;
    elm a[200001] = {0, 0, 0};
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        a[i].key = x;
        a[i].left = y;
        a[i].right = z;
        if (y != 0) {
            a[y].right_parent = i;
            a[y].left_parent = 0;
        }
        if (z != 0) {
            a[z].left_parent = i;
            a[z].right_parent = 0;
        }
    }
    bool lists[200001] = {false};
    for (int i = 1; i <= n && fl; ++i) {
        if (a[i].left == 0 && a[i].right == 0) {
            lists[i] = true;
        }
    }
    for (int i = 1; i <= n && fl; ++i) {
        if (lists[i]) {
            rec(a, i, -INT_MAX, INT_MAX);
        }
    }

    if (fl) {
        fout << "YES";
    }
    else {
        fout << "NO";
    }

    fin.close();
    fout.close();
    return 0;
}
