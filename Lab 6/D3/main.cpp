#include <fstream>
#include <math.h>
#include <vector>
#include <list>

using namespace std;

vector<list<pair<string, string>>> hashTable[1000];
int sizeMap = 1000;

int hashFunc(string str)
{
    int sum = 0;
    int alp = 1;
    for (int i = 0; i < str.length(); i++)
    {
        sum += int(str[i]) * alp;
        alp *= 2;
    }
    return sum % sizeMap;
}

string getMap(string first)
{
    int index = hashFunc(first);
    string ans = "";
    if (hashTable[index].empty())
        return "0";
    int cnt = 0;
    for (int i = 0; i < 1000; i++)
        for (auto j = hashTable[index][i].begin(); j != hashTable[index][i].end(); j++)
            if (j -> first == first)
            {
                ans += j -> second + " ";
                cnt++;
            }
    ans = to_string(cnt) + " " + ans;
    return ans;
}

void putMap(string first, string second)
{
    int index1 = hashFunc(first);
    int index2 = hashFunc(second);
    if (hashTable[index1].empty())
        hashTable[index1].resize(1000);
    for (auto i : hashTable[index1][index2])
        if (i.first == first && i.second == second)
            return;
    hashTable[index1][index2].push_back({first, second});
}

void deleteMap(string first, string second)
{
    int index1 = hashFunc(first);
    int index2 = hashFunc(second);
    if (hashTable[index1].empty()) {
        return;
    }
    for (auto i = hashTable[index1][index2].begin(); i != hashTable[index1][index2].end(); i++)
        if (i -> first == first && i -> second == second)
        {
            hashTable[index1][index2].erase(i);
            break;
        }
}

void deleteallMap(string first)
{
    int index = hashFunc(first);
    if (hashTable[index].empty()) {
        return;
    }
    for (int i = 0; i < 1000; i++)
        for (auto j = hashTable[index][i].begin(); j != hashTable[index][i].end(); j++)
            if (j -> first == first)
            {
                auto k = next(j, 1);
                hashTable[index][i].erase(j);
                j = next(k, -1);
            }
}

int main()
{
    fstream fin, fout;
    fin.open("multimap.in", ios::in);
    fout.open("multimap.out", ios::out);
    string com;
    string first, second;
    while (fin >> com >> first)
    {
        if (com == "put")
        {
            fin >> second;
            putMap(first, second);
        }
        if (com == "get")
            fout << getMap(first) << "\n";
        if (com == "delete")
        {
            fin >> second;
            deleteMap(first, second);
        }
        if (com == "deleteall")
            deleteallMap(first);
    }
    fin.close();
    fout.close();
    return 0;
}
