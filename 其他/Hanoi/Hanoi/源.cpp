#include<iostream>
using namespace std;
void Hanoi(int n, char start, char temp, char end) {
	if (n == 1)
		cout << start << "->" << end<<endl;
	else {
		Hanoi(n - 1, start,end,temp);
		cout << start << "->" << end<<endl;
		Hanoi(n - 1, temp,start,end);
	}
}
int main() {
	int n;
	cin >> n;
	Hanoi(n, '1', '2', '3');
	return 0;
}