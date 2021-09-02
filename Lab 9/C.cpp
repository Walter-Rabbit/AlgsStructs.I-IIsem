#include <vector>
#include <list>
#include <fstream>

/*Двудольный граф*/

using namespace std;

bool fl = true;

void visit(vector <list <int>> &data, vector <int> &colors, int x, int color) {
    colors[x] = -color;
    for (auto i : data[x]) {
        if (colors[i] == -color) {
            fl = false;
        }
        if (colors[i] == 0) {
            visit(data, colors, i, -color);
        }
    }
}

void dfs(vector <list <int>> &data, vector <int> &colors) {
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == 0) {
            visit(data, colors, i, 1);
        }
    }
}

int main() {
    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");

    int n, m;
    fin >> n >> m;

    vector <int> colors(n, 0);
    vector <list <int>> data(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        data[x - 1].push_back(y - 1);
        data[y - 1].push_back(x - 1);
    }

    dfs(data, colors);

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