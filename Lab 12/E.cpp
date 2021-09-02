#include <vector>
#include <list>
#include <iostream>

using namespace std;

struct vertex {
    list<int> kids;

    int colored = 1, uncolored = 0;
};

int root;
void dfs(vector <vertex> &data, int x) {

    for (auto i : data[x].kids) {
        dfs(data, i);
    }

    if (data[x].kids.empty()) {
        return;
    }

    int sum_for_colored = 0, sum_for_uncolored = 0;
    for (auto i : data[x].kids) {
        sum_for_colored += data[i].uncolored;
        sum_for_uncolored += max(data[i].colored, data[i].uncolored);
    }

    data[x].uncolored = sum_for_uncolored;
    data[x].colored = sum_for_colored + 1;
}

/* Выбор вершин дерева */
int main() {
    int n;
    cin >> n;

    vector<vertex> data(n + 1);

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x != 0) {
            data[x].kids.push_back(i);
        }
        else {
            root = i;
        }
    }

    dfs(data, root);

    cout << max(data[root].colored, data[root].uncolored);

    return 0;
}