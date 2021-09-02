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
        if (a[x - 1][y - 1]) {
            fout << "YES";
            return 0;
        }
        a[x - 1][y - 1] = true;
        a[y - 1][x - 1] = true;
    }

    fout << "NO";

    fin.close();
    fout.close();
    return 0;
}
