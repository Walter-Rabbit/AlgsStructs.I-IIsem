#include <fstream>

using namespace std;

pair <int, int> a[200001];
int mx = 0, n;
bool fl = true;

void rec(int i, int k) {
    if (a[i].first != 0 && fl) {
        rec(a[i].first, k + 1);
    }
    if (a[i].second != 0 && fl) {
        rec(a[i].second, k + 1);
    }
    if (mx < k + 1) {
        mx = k + 1;
        if (mx >= n / 2) {
            fl = false;
        }
    }
}

int main() {
    ifstream fin("height.in");
    ofstream fout("height.out");

    fin >> n;
    for (int i = 1; i <= n; i++) {
        int trash, x, y;
        fin >> trash >> x >> y;
        a[i] = {x, y};
    }
    for (int i = 1; i <= n; i++) {
        rec(i, 0);
    }
    fout << mx;

    fin.close();
    fout.close();
    return 0;
}