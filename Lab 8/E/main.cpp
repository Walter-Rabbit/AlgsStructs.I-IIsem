#include <fstream>
#include <queue>
#include <list>

std::list <int> a[30000];
int lengths[400000];
int n, m;

void bfs(int start) {
    int check[400000] = {0};
    std::queue<int> q;

    q.push(start);
    while (!q.empty()) {
        int t = q.front();
        q.pop();

        for (auto i : a[t]) {
            if (i != start && (lengths[i] == 0 || lengths[i] > lengths[t] + 1)) {
                lengths[i] = lengths[t] + 1;
                q.push(i);
            }
        }
        check[t] = true;
    }
}

int main() {
    std::ifstream fin("pathbge1.in");
    std::ofstream fout("pathbge1.out");

    fin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        a[x - 1].push_back(y - 1);
        a[y - 1].push_back(x - 1);
    }

    std::queue<int> q;

    bfs(0);

    for (int i = 0; i < n; ++i) {
        fout << lengths[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
