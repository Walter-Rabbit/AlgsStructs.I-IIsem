#include <fstream>

using namespace std;

int main() {
	ifstream in("aplusbb.in");
	ofstream out("aplusbb.out");
	
	long long a, b, c;
	in >> a >> b;
	c = a + b * b;
	out << c;
	
	in.close();
	out.close();
	return 0;
}
