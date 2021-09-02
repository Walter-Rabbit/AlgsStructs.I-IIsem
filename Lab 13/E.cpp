#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct vertex {     //Бор
    vector<int> _ended_lines;
    vector<vertex*> _children;
    vertex* _suffix_link;
    vertex* _parent;
    bool _is_visited;

    explicit vertex(int n, vertex* parent = nullptr, vertex* suffix_link = nullptr) {
        _parent = parent;
        _suffix_link = suffix_link;
        _is_visited = false;
        _children.assign(n, nullptr);
    }

    void add_line(const string& line, int index, int number) {
        if (line.length() == index) {
            _ended_lines.push_back(number);
            return;
        }

        //Создание новой вершины в боре и связывания родителя с новой вершиной
        if (_children[line[index] - 'a'] == nullptr) {
            _children[line[index] - 'a'] = new vertex((int) _children.size(), this);
        }

        _children[line[index] - 'a']->add_line(line, index + 1, number);
    }

    void set_suffix_link(int index, vertex* root) {
        vertex* parent = _parent;
        parent = parent->_suffix_link;

        //Ищем ссылку на нужную вершину
        while (parent != nullptr && parent->_children[index] == nullptr) {
            parent = parent->_suffix_link;
        }

        if (parent == nullptr) {
            _suffix_link = root;
        }
        else {
            _suffix_link = parent->_children[index];
        }
    }
};

void bfs(vertex* root) {
    queue<pair<vertex*, int>> q;
    for (int i = 0; i < root->_children.size(); ++i) {
        if (root->_children[i] != nullptr) {
            q.push({root->_children[i], i});
        }
    }

    while (!q.empty()) {
        vertex* current_vertex = q.front().first;
        int current_index = q.front().second;
        q.pop();

        for (int i = 0; i < current_vertex->_children.size(); ++i) {
            if (current_vertex->_children[i] != nullptr) {
                q.push({current_vertex->_children[i], i});
            }
        }

        //Проставляем линки
        current_vertex->set_suffix_link(current_index, root);
    }
}

void find(vertex* trie, const string& line, vector<vertex*>& is_visited) {
    vertex* current_vertex = trie;

    for (char i : line) {
        is_visited.push_back(current_vertex);

        if (current_vertex != nullptr && current_vertex->_children[i - 'a'] == nullptr) {
            while (current_vertex != nullptr && current_vertex->_children[i - 'a'] == nullptr) {
                current_vertex = current_vertex->_suffix_link;
            }
        }

        if (current_vertex == nullptr) {
            current_vertex = trie;
        }
        else {
            current_vertex = current_vertex->_children[i - 'a'];
        }
    }

    is_visited.push_back(current_vertex);
}

int main() {
    ifstream fin("search4.in");
    ofstream fout("search4.out");

    vertex trie(26);
    trie._parent = &trie;

    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        string sub_line;
        fin >> sub_line;
        trie.add_line(sub_line, 0, i);
    }
    string line;
    fin >> line;

    vector<vertex*> is_visited;
    bfs(&trie);     //Прокидываем линки
    find(&trie, line, is_visited);

    vector<bool> visited_lines(n, false);
    for (auto v : is_visited) {
        auto current_vertex = v;

        while (current_vertex != nullptr) {
            if (current_vertex->_is_visited) {
                break;
            }

            if (!current_vertex->_ended_lines.empty()) {
                for (auto i : current_vertex->_ended_lines) {
                    visited_lines[i] = true;
                }
            }

            current_vertex->_is_visited = true;
            current_vertex = current_vertex->_suffix_link;
        }
    }

    for (auto i : visited_lines) {
        if (i) {
            fout << "YES\n";
        }
        else {
            fout << "NO\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}