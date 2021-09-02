#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct map {
private:
    struct elm {
        string key;
        vector<string> data;

        elm(const string& l1) {
            key = l1;
        }
    };

    vector<elm> list[50000];

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
        int fl = -1, i;
        for (i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                fl = i;
                break;
            }
        }
        if (fl == -1) {
            elm temp(key);
            list[index].push_back(temp);
            list[index][list[index].size() - 1].data.push_back(x);
        }
        else {
            for (int i = 0; i < list[index][fl].data.size(); i++) {
                if (list[index][fl].data[i] == x) {
                    return;
                }
            }
            list[index][fl].data.push_back(x);
        }
    }

    void erase(const string& key, const string& x) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                for (int j = 0; j < list[index][i].data.size(); j++) {
                    if (list[index][i].data[j] == x) {
                        list[index][i].data.erase(list[index][i].data.begin() + j);
                        break;
                    }
                }
                break;
            }
        }
    }

    void eraseAll(const string& key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                list[index].erase(list[index].begin() + i);
                break;
            }
        }
    }

    string get(const string& key) {
        string ans = "";
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                ans = ans + to_string(list[index][i].data.size()) + " ";
                for (int j = 0; j < list[index][i].data.size(); j++) {
                    ans = ans + list[index][i].data[j] + " ";
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
