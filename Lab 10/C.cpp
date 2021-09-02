#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int v1, v2, weight;
};

bool comp(edge e1, edge e2) {
    return e1.weight < e2.weight;
}

//Остовное дерево 3
int main() {
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");

    int n, m;
    fin >> n >> m;

    vector <edge> edges;
    vector <int> color(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        edges.push_back({x - 1, y - 1, z});
    }

    sort(edges.begin(), edges.end(), comp);
    int count = 1, size = 0;
    long long sum = 0;

    for (int i = 0; i < m; ++i) {
        if (n - 1 == size) {
            break;
        }
        if (color[edges[i].v1] == 0 && color[edges[i].v2] == 0) {
            color[edges[i].v1] = count;
            color[edges[i].v2] = count;
            count++;
            sum += edges[i].weight;
            size++;
        }

        else if (color[edges[i].v1] != 0 && color[edges[i].v2] == 0) {
            color[edges[i].v2] = color[edges[i].v1];
            sum += edges[i].weight;
            size++;
        }

        else if (color[edges[i].v1] == 0 && color[edges[i].v2] != 0) {
            color[edges[i].v1] = color[edges[i].v2];
            sum += edges[i].weight;
            size++;
        }

        else if (color[edges[i].v1] != color[edges[i].v2]) {
            int clr1 = color[edges[i].v1];
            int clr2 = color[edges[i].v2];
            for (int j = 0; j < n; ++j) {
                if (color[j] == clr2) {
                    color[j] = clr1;
                }
            }
            size++;
            sum += edges[i].weight;
        }
    }

    fout << sum;

    fin.close();
    fout.close();
    return 0;
}