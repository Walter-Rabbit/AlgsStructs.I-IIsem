#include <vector>
#include <list>
#include <stack>
#include <fstream>

/*Топологическая сортировка*/

using namespace std;

void visit(vector <list <int>> &data, vector <int> &colors, int x, stack <int> &topology) {
    colors[x] = 1;
    for (auto i : data[x]) {
        if (colors[i] == 1) {
            colors[0] = -1;
            return;
        }
        if (colors[i] == 0) {
            visit(data, colors, i, topology);
        }
    }
    topology.push(x + 1);
    if (colors[0] != -1) {
        colors[x] = 2;
    }
}

void dfs(vector <list <int>> &data, vector <int> &colors, stack <int> &topology) {
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == 0) {
            visit(data, colors, i, topology);
        }
    }
}

int main() {
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    int n, m;
    fin >> n >> m;

    vector <int> colors(n, 0);
    vector <list <int>> data(n);
    stack <int> topology;

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        data[x - 1].push_back(y - 1);
    }

    dfs(data, colors, topology);

    if (colors[0] == -1) {
        fout << -1;
        return 0;
    }
    while (!topology.empty()) {
        int a = topology.top();
        fout << a << " ";
        topology.pop();
    }

    fin.close();
    fout.close();
    return 0;
}