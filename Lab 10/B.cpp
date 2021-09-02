#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct edge {
    int v1, v2;
    double dist;
};

struct vertex {
    int x, y;
};

double dist(vertex v1, vertex v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

bool comp(edge e1, edge e2) {
    return e1.dist < e2.dist;
}

//Не работает
int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");

    int n;
    fin >> n;

    vector <vertex> vertexes;
    vector <edge> edges;
    vector <vector <edge>> sets;

    for (int i = 0; i < n; ++i) {
        int x, y;
        fin >> x >> y;
        vertexes.push_back({x, y});
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({i, j, dist(vertexes[i], vertexes[j])});
        }
    }
    vertexes.clear();

    sort(edges.begin(), edges.end(), comp);

    for (auto & i : edges) {
        if (sets.size() == n - 1) {
            break;
        }
        int fl = -1;
        int v;
        edge e = {};
        for (int j = 0; j < sets.size(); ++j) {
            for (auto k : sets[j]) {
                //Такое ребро уже есть
                if ((k.v1 == i.v1 && k.v2 == i.v2) || (k.v1 == i.v2 && k.v2 == i.v1)) {
                    fl = -2;
                    break;
                }
                //Первая вершина есть во каком-то множестве
                if (k.v1 == i.v1 || k.v2 == i.v1) {
                    fl = j;
                    v = i.v2;
                    e = i;
                    break;
                }
                //Вторая вершина есть во каком-то множестве
                if (k.v1 == i.v2 || k.v2 == i.v2) {
                    fl = j;
                    v = i.v1;
                    e = i;
                    break;
                }
            }
        }
        //Совпадений не нашлось
        if (fl == -1) {
            sets.push_back({i});
        }

        int fl2 = 1;
        if (fl >= 0) {
            //Поиск множества с несовпавшей вершиной
            for (int j = 0; j < sets.size(); ++j) {
                for (auto k : sets[j]) {
                    if (v == k.v1 || v == k.v2) {
                        //Обе вершины НЕ в одном множестве
                        if (j != fl) {
                            sets[j].push_back(e);
                            int to = min(j, fl);
                            int from = max(j, fl);
                            sets[to].insert(sets[to].end(), sets[from].begin(), sets[from].end());
                            sets.erase(sets.begin() + from);
                        }
                        fl2 = 0;
                        j = sets.size();
                        break;
                    }
                }
            }
            //Несовпавшая вершина не нашлась
            if (fl2 == 1) {
                sets[fl].push_back(i);
            }
        }
    }

    double sum = 0;
    if (!sets.empty()) {
        for (auto j : sets[0]) {
            sum += j.dist;
        }
    }

    fout.precision(9);
    fout << sum;

    fin.close();
    fout.close();
}