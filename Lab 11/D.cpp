#include <fstream>
#include <vector>

using namespace std;

struct edge {
    long long v1, v2;
    long long weight;
};

void dfs(long long v, vector<vector<long long>> &list, vector<bool> &color) {
    color[v] = true;
    for (auto i : list[v]) {
        if (!color[i]) {
            dfs(i, list, color);
        }
    }
}

//Кратчайшие пути и прочее (Форд-Беллман)
int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");

    long long n, m, start;
    vector<edge> edges;
    fin >> n >> m >> start;
    start--;

    long long inf = 8e18;
    vector<long long> dist(n, inf);
    vector<vector<long long>> list(n);
    vector<long long> neg;

    for (long long i = 0; i < m; ++i) {
        long long x, y, z;
        fin >> x >> y >> z;
        edges.push_back({x - 1, y - 1, z});
        list[x - 1].push_back(y - 1);
    }

    dist[start] = 0;
    for (long long i = 0; i < n - 1; ++i) {
        for (auto & edge : edges) {
            if (dist[edge.v1] < inf) {
                if (dist[edge.v2] > dist[edge.v1] + edge.weight) {
                    dist[edge.v2] = max(dist[edge.v1] + edge.weight, -inf);
                }
            }
        }
    }

    for (auto & edge : edges) {
        if (dist[edge.v1] < inf) {
            if (dist[edge.v2] > dist[edge.v1] + edge.weight) {
                dist[edge.v2] = max(dist[edge.v1] + edge.weight, -inf);
                neg.push_back(edge.v2);
            }
        }
    }

    vector<bool> color(n, false);
    for (auto i : neg) {
        dfs(i, list, color);
    }

    for (long long i = 0; i < n; ++i) {
        if (color[i]) {
            fout << "-\n";
        }
        else if (dist[i] == inf) {
            fout << "*\n";
        }
        else {
            fout << dist[i] << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}