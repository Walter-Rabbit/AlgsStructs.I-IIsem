#include <fstream>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    short n;
    fin >> n;
    bool a[100][100] = {false};

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            fin >> a[i][j];
        }
    }

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            if (a[i][j] != a[j][i] || (a[i][j] && i == j)) {
                fout << "NO";
                return 0;
            }
        }
    }

    fout << "YES";

    fin.close();
    fout.close();
    return 0;
}
