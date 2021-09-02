#include <fstream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct map {
private:
    struct elm {
        string key;
        list<string> data;

        elm(const string& l1) {
            key = l1;
        }
    };

    list<elm> array[50000];

    static int hash(const string& x) {
        int h = 0;
        for (char i : x) {
            h += i;
        }
        if (x.length() > 1) {
            h *= x[1];
        }
        return h % 50000;
    }

public:
    void push(const string& key, const string& x) {
        int index = hash(key);

        for (auto& i : array[index]) {
            if (i.key == key) {
                for (const auto& j : i.data) {
                    if (j == x) {
                        return;
                    }
                }
                i.data.push_back(x);
                return;
            }
        }

        elm temp(key);
        temp.data.push_back(x);
        array[index].push_back(temp);
    }

    void erase(const string& key, const string& x) {
        int index = hash(key);

        for (auto& i : array[index]) {
            if (i.key == key) {
                for (const auto& j : i.data) {
                    if (j == x) {
                        i.data.erase(find(i.data.begin(), i.data.end(), x));
                        return;
                    }
                }
                return;
            }
        }

    }

    void eraseAll(const string& key) {
        int index = hash(key);
        for (auto& i : array[index]) {
            if (i.key == key) {
                i.data.clear();
                return;
            }
        }
    }

    string get(const string& key) {
        string ans;
        int index = hash(key);
        for (const auto& i : array[index]) {
            if (i.key == key) {
                ans += to_string(i.data.size()) + " ";
                for (const auto& j : i.data) {
                    ans += j + " ";
                }
                return ans;
            }
        }
        return "0";
    }

};

int main() {
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");
    string command;
    string key, x;
    map a;
    while (fin >> command) {
        if (command == "put") {
            fin >> key >> x;
            a.push(key, x);
            continue;
        }
        if (command == "delete") {
            fin >> key >> x;
            a.erase(key, x);
            continue;
        }
        if (command == "deleteall") {
            fin >> key;
            a.eraseAll(key);
            continue;
        }
        if (command == "get") {
            fin >> key;
            fout << a.get(key) << "\n";
            continue;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
