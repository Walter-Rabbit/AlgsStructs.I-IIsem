#include <fstream>
#include <string>
#include <queue>

using namespace std;

queue <unsigned short> data;    //Очередь с данными, куда они записываются // unsigned short, так как в условие указана 2байтная арифметика
pair <string, int> labels[101] = {{"", 0}};     //Массив с метками и индексами этих меток
int indexLabels = 0;    //размер массива меток
int reg[26] = {0};  //массив регистров
int indexComands = 0;   //размер массива со всеми командами
string comands[100100] = {""};  //массив со всеми командами

int find(const string& x) { //Функция поиска нужной метки в массиве меток, возвращает индекс для массива всех команд, где хранится эта метка
    for (int i = 0; i < indexLabels; i++) {
        if (x == labels[i].first) {
            return labels[i].second;
        }
    }
}

void push(unsigned short x) {   //Добавление в очередь
    data.push(x);
}

int getReg(char c) {    //Значение регистра 'буква'
    return reg[c - 'a'];
}

int get() {     //Получение первого элемента очереди
    int y = data.front();
    data.pop();
    return y;
}

void add() {    //Сложение двух первых элементов очереди
    unsigned short x = data.front();
    data.pop();
    unsigned short y = data.front();
    data.pop();
    data.push(x + y);
}

void negativeAdd() {    //Вычитание двух первых элементов очереди
    unsigned short x = data.front();
    data.pop();
    unsigned short y = data.front();
    data.pop();
    data.push(x - y);
}

void multi() {  //Перемножение двух первых элементов очереди
    unsigned short x = data.front();
    data.pop();
    unsigned short y = data.front();
    data.pop();
    data.push(x * y);
}

void divide() { //Деление двух первых элементов очереди
    unsigned short x = data.front();
    data.pop();
    unsigned short y = data.front();
    data.pop();
    if (y == 0) {
        data.push(0);
    }
    else {
        data.push(x / y);
    }
}

void mod() {    //Остаток от деления двух первых элементов очереди
    unsigned short x = data.front();
    data.pop();
    unsigned short y = data.front();
    data.pop();
    if (y == 0) {
        data.push(0);
    }
    else {
        data.push(x % y);
    }
}

void toReg(char c) {    //Засовывании первого элемента очереди в регистр 'буква'
    unsigned short x = data.front();
    data.pop();
    reg[c - 'a'] = x;
}

void fromReg(char c) {  //Добавление в очередь значение регистра 'буква'
    unsigned short x = reg[c - 'a'];
    data.push(x);
}

char ascii() {  //возвращение символа, на номер которого в АСКИИ указывает первый элемент очереди
    char y = (char) (data.front() % 256);
    data.pop();
    return y;
}

char asciiReg(char c) { //возвращение символа, на номер которого в АСКИИ указывает регистр 'буква'
    char y = (char) (reg[c - 'a'] % 256);
    return y;
}

void pushLabel(const string& st, int i) {   //добавление метки и её индекса в массив меток
    string copy = "";
    for (int j = 1; j < st.length(); j++) {
        copy += st[j];
    }
    labels[indexLabels] = {copy, i};
    indexLabels++;
}

int findLabel(const string& st) {   //Поиск метки, возвращается её индекс
    string copy = "";
    for (int j = 1; j < st.length(); j++) {
        copy += st[j];
    }
    return find(copy);
}

int findLabelZero(const string& st) { //Если регистр 'буква' равен 0, то поиск метки
    if (reg[st[1] - 'a']  == 0) {
        string copy = "";
        for (int j = 2; j < st.length(); j++) {
            copy += st[j];
        }
        return find(copy);
    }
    else {
        return -1;
    }
}

int findLabelEqual(const string& st) { //Если регистр 'буква' равен регистру 'буква', то поиск метки
    if (reg[st[1] - 'a']  == reg[st[2] - 'a']) {
        string copy = "";
        for (int j = 3; j < st.length(); j++) {
            copy += st[j];
        }
        return find(copy);
    }
    else {
        return -1;
    }
}

int findLabelGreat(const string& st) { //Если регистр 'буква' больше регистра 'буква', то поиск метки
    if (reg[st[1] - 'a']  > reg[st[2] - 'a']) {
        string copy = "";
        for (int j = 3; j < st.length(); j++) {
            copy += st[j];
        }
        return find(copy);
    }
    else {
        return -1;
    }
}

int main() {
    ifstream fin("quack.in");
    ofstream fout("quack.out");

    string input;

    while (fin >> input && input != "Q") {
        indexComands++; //запись всех команд в массив комнда
        comands[indexComands] = input;
        if (input[0] == ':') { //если эта метка, то записываем её ещё и в массив меток
            pushLabel(input, indexComands);
            continue;
        }
    }

    for (int i = 1; i <= indexComands; i++) { //ифы с командами
        char c0 = comands[i][0], c1 = '-'; //по первым двум сиволам можно определить, что это за комнда
        if (comands[i].length() > 1) {
            c1 = comands[i][1];
        }

        if (c0 >= '0' && c0 <= '9' || c0 == '-' && c1 != '-') {
            push(stoi(comands[i])); //string to integer
            continue;
        }

        if (c0 == '+') {
            add();
            continue;
        }

        if (c0 == '-') {
            negativeAdd();
            continue;
        }

        if (c0 == '*') {
            multi();
            continue;
        }

        if (c0 == '/') {
            divide();
            continue;
        }

        if (c0 == '%') {
            mod();
            continue;
        }

        if (c0 == '>') {
            toReg(c1);
            continue;
        }

        if (c0 == '<') {
            fromReg(c1);
            continue;
        }

        if (c0 == 'P' && c1 == '-') {
            fout << get() << "\n";
            continue;
        }

        if (c0 == 'P' && c1 != '-') {
            fout << getReg(c1) << "\n";
            continue;
        }

        if (c0 == 'C' && c1 == '-') {
            fout << ascii();
            continue;
        }

        if (c0 == 'C' && c1 != '-') {
            fout << asciiReg(c1);
            continue;
        }

        if (c0 == ':') {
            continue;
        }

        if (c0 == 'J') {
            i = findLabel(comands[i]);
            continue;
        }

        if (c0 == 'Z') {
            int j = findLabelZero(comands[i]);
            if (j != -1) {
                i = j;
            }
            continue;
        }

        if (c0 == 'E') {
            int j = findLabelEqual(comands[i]);
            if (j != -1) {
                i = j;
            }
            continue;
        }

        if (c0 == 'G') {
            int j = findLabelGreat(comands[i]);
            if (j != -1) {
                i = j;
            }
            continue;
        }

        if (c0 == 'Q') {
            break;
        }
    }

    fin.close();
    fout.close();
    return 0;
}