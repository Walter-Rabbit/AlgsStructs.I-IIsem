#include <vector>
#include <list>
#include <fstream>
#include <stack>
#include <algorithm>

/*Гамильтонов путь*/

using namespace std;

void visit(vector <list <int>> &data, vector <int> &colors, int x, stack <int> &topology) {
    colors[x] = 1;
    for (auto i : data[x]) {
        if (colors[i] == 0) {
            visit(data, colors, i, topology);
        }
    }
    topology.push(x);
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
    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");

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

    if (n == 1) {
        fout << "YES";
        fin.close();
        fout.close();
        return 0;
    }
    else {
        int a = topology.top();
        topology.pop();
        while (!topology.empty()) {
            int b = topology.top();
            topology.pop();
            if (find(data[a].begin(), data[a].end(), b) == data[a].end()) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            }
            a = b;
        }
    }
    fout << "YES";
    fin.close();
    fout.close();
    return 0;
}