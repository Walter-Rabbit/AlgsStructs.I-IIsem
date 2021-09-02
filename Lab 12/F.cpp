#include <vector>
#include <list>
#include <fstream>

using namespace std;

struct vertex {
    list<int> kids;
    int w;

    int colored = 0, uncolored = 0;
};

int root;
void dfs(vector <vertex> &data, int x) {

    for (auto i : data[x].kids) {
        dfs(data, i);
    }

    if (data[x].kids.empty()) {
        if (data[x].w > 0) {
            data[x].colored = data[x].w;
        }
        return;
    }

    int sum_for_colored = 0, sum_for_uncolored = 0;
    for (auto i : data[x].kids) {
        sum_for_colored += data[i].uncolored;
        sum_for_uncolored += max(data[i].colored, data[i].uncolored);
    }

    data[x].uncolored = sum_for_uncolored;
    data[x].colored = sum_for_colored;
    if (data[x].w > 0) {
        data[x].colored += data[x].w;
    }
}

/* Дерево (сумма) */
int main() {
    ifstream fin("selectw.in");
    ofstream fout("selectw.out");

    int n;
    fin >> n;

    vector<vertex> data(n + 1);

    for (int i = 1; i <= n; ++i) {
        int x, y;
        fin >> x >> y;
        if (x != 0) {
            data[x].kids.push_back(i);
            data[i].w = y;
        }
        else {
            root = i;
            data[i].w = y;
        }
    }

    dfs(data, root);

    fout << max(data[root].colored, data[root].uncolored);

    fin.close();
    fout.close();
    return 0;
}