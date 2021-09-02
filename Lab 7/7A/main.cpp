#include <fstream>

using namespace std;

struct elm {
    int left, right;
    int height;
};

elm a[200001];
int ans[200001];

int balance(int i) {
    return -a[a[i].left].height + a[a[i].right].height;
}

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");

    int n;
    fin >> n;

    for (int i = 1; i <= n; ++i) {
        int trash, x, y;
        fin >> trash >> x >> y;
        a[i] = {x, y, 1};
    }

    for (int i = n; i > 0; --i) {
        ans[i] = balance(i);
        a[i].height += max(a[a[i].left].height, a[a[i].right].height);
    }

    for (int i = 1; i <= n; ++i) {
        fout << ans[i] << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}