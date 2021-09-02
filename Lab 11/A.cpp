#include <fstream>
#include <vector>

using namespace std;

struct vertex {
    int v;
    long long weight;
};

//Кратчайший путь (Дейкстра)
int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    long long n, start, end;
    fin >> n >> start >> end;
    start--;
    end--;

    vector<vector<vertex>> g(n);
    vector<long long> dist(n, LLONG_MAX);
    vector<int> prev(n, 0);
    vector<bool> check(n, false);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long x;
            fin >> x;
            if (i != j && x != -1) {
                g[i].push_back({j, x});
            }
        }
    }

    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        int newVertex = -1;
        for (int j = 0; j < n; ++j) {
            if (!check[j] && (newVertex == -1 || dist[j] < dist[newVertex])) {
                newVertex = j;
            }
        }

        if (dist[newVertex] == LLONG_MAX) {
            break;
        }

        check[newVertex] = true;

        for (int j = 0; j < g[newVertex].size(); ++j) {
            int to = g[newVertex][j].v;
            long long length = g[newVertex][j].weight;
            if (dist[newVertex] + length < dist[to]) {
                dist[to] = dist[newVertex] + length;
                prev[to] = newVertex;
            }
        }
    }

    if (dist[end] == LLONG_MAX) {
        fout << -1;
    }
    else {
        fout << dist[end];
    }

    fin.close();
    fout.close();
    return 0;
}