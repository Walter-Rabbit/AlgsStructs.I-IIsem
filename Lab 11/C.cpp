#include <fstream>
#include <vector>

using namespace std;

struct edge {
    long long v1, v2;
    long long weight;
};

//Кратчайший путь (Форд-Беллман)
int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");

    long long n, m;
    vector<edge> edges(1);
    fin >> n >> m;
    vector<long long> dist(n + 1, LLONG_MAX);

    for (long long i = 1; i <= m; ++i) {
        long long x, y, z;
        fin >> x >> y >> z;
        edges.push_back({x, y, z});
        edges.push_back({y, x, z});
    }
    dist[1] = 0;
    for (;;) {
        bool changes = false;
        for (long long j = 1; j < edges.size(); ++j) {
            if (dist[edges[j].v1] < LLONG_MAX && dist[edges[j].v2] > dist[edges[j].v1] + edges[j].weight) {
                dist[edges[j].v2] = dist[edges[j].v1] + edges[j].weight;
                changes = true;
            }
        }
        if (!changes) {
            break;
        }
    }

    for (long long i = 1; i <= n; ++i) {
        fout << dist[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}