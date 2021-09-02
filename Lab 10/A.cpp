#include <fstream>
#include <vector>

using namespace std;

//Степени вершин
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;
    vector <int> a(n, 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        if (x != y) {
            a[x - 1]++;
            a[y - 1]++;
        }
        else {
            a[x - 1]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        fout << a[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
