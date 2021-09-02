#include <vector>
#include <list>
#include <queue>
#include <fstream>

/*Игра*/

using namespace std;

void visit(vector <list <int>> &data, vector <int> &colors, int x, queue <int> &topology) {
    colors[x] = 1;
    for (auto i : data[x]) {
        if (colors[i] == 0) {
            visit(data, colors, i, topology);
        }
    }
    topology.push(x);
    colors[x] = 2;
}

int main() {
    ifstream fin("game.in");
    ofstream fout("game.out");

    int n, m, start;
    fin >> n >> m >> start;
    start--;

    vector <int> colors(n, 0);
    vector <list <int>> data(n), reverse(n);
    queue <int> topology;

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        data[x - 1].push_back(y - 1);
        reverse[y - 1].push_back(x - 1);
    }

    visit(data, colors, start, topology);

    vector <int> win(n, -1);

    while (!topology.empty()) {
        int x = topology.front();
        for (auto i : reverse[x]) {
            if (win[i] == -1) {
                win[i] = -win[x];
            }
        }
        topology.pop();
    }

    if (win[start] == -1) {
        fout << "Second player wins";
    }
    else {
        fout << "First player wins";
    }

    fin.close();
    fout.close();
    return 0;
}