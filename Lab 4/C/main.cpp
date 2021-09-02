#include <fstream>
#include <string>

using namespace std;

struct stack {
    char stack[10000];
    int last = 0;

    void pop() {
        last -= 2;
    }

    char lastElement() {
        return stack[last];
    }

    void push(char x) {
        last++;
        stack[last] = x;
    }
};

int main() {
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");

    string x;
    while (fin >> x) {
        stack a;
        int i = 0;
        char key;
        key = x[0];
        while(x[i]) {
            a.push(x[i]);
            if (x[i] == ')' && key == '(' || x[i] == ']' && key == '[') {
                a.pop();
                key = a.lastElement();
                i++;
                continue;
            }
            if (x[i] == '(' || x[i] == '[') {
                key = x[i];
                i++;
                continue;
            }
            if (x[i] == ')' && key == '[' || x[i] == ']' && key == '(') {
                a.last = 1;
                break;
            }
            i++;
        }
        if (a.last == 0) {
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