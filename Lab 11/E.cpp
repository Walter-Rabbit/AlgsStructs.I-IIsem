#include <fstream>
#include <vector>
#include <algorithm>

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

//Цикл отрицательного веса (Форд-Беллман)
int main() {
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    long long n;
    vector<edge> edges;
    fin >> n;

    long long inf = 8e18;

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            long long x;
            fin >> x;
            if (x != 1e9) {
                edges.push_back({i, j, x});
            }
        }
    }

    vector<bool> fl(n, true);
    for (long long k = 0; k < n; ++k) {
        if (!fl[k]) {
            continue;
        }
        vector<long long> dist(n, inf);
        vector<long long> prev(n, -1);
        dist[k] = 0;
        long long p = -1;
        for (long long i = 0; i < n; ++i) {
            p = -1;
            for (auto &edge : edges) {
                if (dist[edge.v1] < inf) {
                    if (dist[edge.v2] > dist[edge.v1] + edge.weight) {
                        dist[edge.v2] = max(dist[edge.v1] + edge.weight, -inf);
                        fl[edge.v2] = false;
                        prev[edge.v2] = edge.v1;
                        p = edge.v2;
                    }
                }
            }
        }

        if (p == -1) {
            continue;
        } else {
            for (long long i = 0; i < n; ++i) {
                p = prev[p];
            }

            vector<long long> path;
            long long i = p;
            while (true) {
                path.push_back(i);
                if (i == p && path.size() > 1) {
                    break;
                }
                i = prev[i];
            }
            reverse(path.begin(), path.end());

            fout << "YES\n";
            fout << path.size() << "\n";
            for (auto t : path) {
                fout << t + 1 << " ";
            }
        }
        fin.close();
        fout.close();
        return 0;
    }

    fout << "NO";

    fin.close();
    fout.close();
    return 0;
}