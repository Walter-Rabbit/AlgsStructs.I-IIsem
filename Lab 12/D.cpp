#include <fstream>
#include <vector>

using namespace std;

bool in_bound(int n, int m, int i, int j) {
    if (i < 0 || j < 0) {
        return false;
    }
    if (i > n - 1 || j > m - 1) {
        return false;
    }
    return true;
}

/* Ход конём */
int main() {
    ifstream fin("knight2.in");
    ofstream fout("knight2.out");

    int n, m;
    fin >> n >> m;
    vector<vector<unsigned long long>> d(n, vector<unsigned long long>(m, 0));

    d[0][0] = 1;

    //Диагонально до правого верхнего угла
    for (int k = 0; k < m; ++k) {
        for (int i = 0, j = k; i < n && j >= 0; ++i, --j) {
            if (in_bound(n, m, i - 1, j + 2)) {
                d[i - 1][j + 2] += d[i][j];
            }

            if (in_bound(n, m, i + 1, j + 2)) {
                d[i + 1][j + 2] += d[i][j];
            }

            if (in_bound(n, m, i + 2, j + 1)) {
                d[i + 2][j + 1] += d[i][j];
            }

            if (in_bound(n, m, i + 2, j - 1)) {
                d[i + 2][j - 1] += d[i][j];
            }
        }
    }

    //Диагонально до конца
    for (int k = 1; k < n; ++k) {
        for (int i = k, j = m - 1; i < n && j >= 0; ++i, --j) {
            if (in_bound(n, m, i - 1, j + 2)) {
                d[i - 1][j + 2] += d[i][j];
            }

            if (in_bound(n, m, i + 1, j + 2)) {
                d[i + 1][j + 2] += d[i][j];
            }

            if (in_bound(n, m, i + 2, j + 1)) {
                d[i + 2][j + 1] += d[i][j];
            }

            if (in_bound(n, m, i + 2, j - 1)) {
                d[i + 2][j - 1] += d[i][j];
            }
        }
    }

    fout << d[n - 1][m - 1];

    fin.close();
    fout.close();
    return 0;
}