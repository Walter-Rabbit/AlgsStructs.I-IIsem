#include <fstream>

using namespace std;

struct elm {
    int x;
    int left, right;
    int height, balance;
    int parent;
};
elm ans[200001];

void balance(int n, elm* a) {
    for (int i = n; i > 0; --i) {
        a[i].balance = -a[a[i].left].height + a[a[i].right].height;
        a[i].height += max(a[a[i].left].height, a[a[i].right].height);
    }
}



/*int k = 1;
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
} */

int main() {
    elm a[2001];
    ifstream fin("rotation.in");
    ofstream fout("rotation.out");

    a[0] = {0, 0, 0, 0, 0, 0};

    int n;
    fin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        a[i].x = x;
        a[i].left = y;
        a[i].right = z;
        a[i].height = 1;
        a[i].balance = 0;
        a[y].parent = i;
        a[z].parent = i;
    }

    balance(n, a);
    if (a[a[1].right].balance == -1) {
        int indexA = 1;
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
        if (a[parentA].x > a[indexC].x) {
            a[parentA].left = indexC;
        }
        else {
            a[parentA].right = indexC;
        }
    }
    else {
        int indexA = 1;
        int indexB = a[indexA].right;
        int parentA = a[indexA].parent;

        a[indexA].right = a[indexB].left;
        a[a[indexA].right].parent = indexA;
        a[indexA].parent = indexB;

        a[indexB].left = indexA;
        a[a[indexB].left].parent = indexB;
        a[indexB].parent = parentA;
        if (a[parentA].x > a[indexB].x) {
            a[parentA].left = indexB;
        }
        else {
            a[parentA].right = indexB;
        }
    }
    //rec(1);

    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        fout << a[i].x << " " << a[i].left << " " << a[i].right << " " << a[i].parent << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
