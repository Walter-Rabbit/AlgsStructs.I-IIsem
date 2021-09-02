#include <fstream>
#include <queue>
#include <list>

std::list <int> a[1000000];
int components[100000];
int n, m;

void bfs(int start, int number) {
    bool check[100000] = {false};
    std::queue<int> q;

    q.push(start);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        check[t] = true;
        components[t] = number;

        for (auto i : a[t]) {
            if (!check[i]) {
                q.push(i);
            }
        }


    }
}

int main() {
    std::ifstream fin("components.in");
    std::ofstream fout("components.out");

    fin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        a[x - 1].push_back(y - 1);
        a[y - 1].push_back(x - 1);
    }

    std::queue<int> q;
    int number = 1;

    for (int i = 0; i < n; ++i) {
        if (components[i] == 0) {
            bfs(i, number);
            number++;
        }
    }

    fout << number - 1 << "\n";
    for (int i = 0; i < n; ++i) {
        fout << components[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
