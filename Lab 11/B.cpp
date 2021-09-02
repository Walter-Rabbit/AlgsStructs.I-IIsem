#include <fstream>

using namespace std;

//Кратчайший путь от каждой вершины до каждой (Флойд-Уоршелл)
int main() {
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");

    int n, m;
    fin >> n >> m;
    int dist[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = 10e8;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        dist[x - 1][y - 1] = min(dist[x - 1][y - 1], z);
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << dist[i][j] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}