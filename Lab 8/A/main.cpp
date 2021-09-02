#include <fstream>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    short n, m;
    fin >> n >> m;
    bool a[100][100] = {false};


    for (short i = 0; i < m; ++i) {
        short x, y;
        fin >> x >> y;
        a[x - 1][y - 1] = true;
    }

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            fout << a[i][j] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
