#include <iostream>

using namespace std;

int main(){
	int entrada, fahrenheit;
	cin >> entrada;
	fahrenheit = (entrada * 9/5) + 32;
	cout << entrada << " graus celsius equivale a " << fahrenheit << " graus fahrenheit" << endl;
	
	return 0;
}
