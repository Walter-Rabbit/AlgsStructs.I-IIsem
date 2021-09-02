#include <fstream>
#include <string>

using namespace std;

struct stack {
    long long stack[10000];
    int last = 0;

    void pop() {
        last -= 2;
    }

    long long lastElement() {
        return stack[last];
    }

    long long preLastElement() {
        return stack[last - 1];
    }

    void push(long long x) {
        last++;
        stack[last] = x;
    }
};

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");

    stack a;
    string st;
    while (fin >> st) {
        if (st[0] >= '0' && st[0] <= '9') {
            int x = stoi(st);
            a.push(x);
        }
        else {
            if (st[0] == '+') {
                int x = a.preLastElement() + a.lastElement();
                a.pop();
                a.push(x);
            }
            else if (st[0] == '*') {
                int x = a.preLastElement() * a.lastElement();
                a.pop();
                a.push(x);
            }
            else if (st[0] == '-') {
                int x = a.preLastElement() - a.lastElement();
                a.pop();
                a.push(x);
            }
        }
    }
    fout << a.lastElement();

    fin.close();
    fout.close();
    return 0;
}