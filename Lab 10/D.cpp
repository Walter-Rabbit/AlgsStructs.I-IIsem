#include <fstream>
#include <vector>
#include <list>
#include <stack>

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

void dfsTopology(vector <list <int>> &data, vector <int> &colors, stack <int> &topology) {
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == 0) {
            visit(data, colors, i, topology);
        }
    }
}

void dfs(vector <list <int>> &reverse, int x, int color, vector <int> &colors) {
    colors[x] = color;
    for (auto i : reverse[x]) {
        if (colors[i] == -1) {
            dfs(reverse, i, color, colors);
        }
    }
}

vector <int> condence() {
    vector <int> colors(n, 0);
    vector <list <int>> data(n), reverse(n);
    stack <int> topology;

    dfsTopology(data, colors, topology);

    for (int & color : colors) {
        color = -1;
    }

    int count = 1;
    while (!topology.empty()) {
        int t = topology.top();
        topology.pop();
        if (colors[t] == -1) {
            dfs(reverse, t, count, colors);
            count++;
        }
    }
}