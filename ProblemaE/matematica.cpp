#include <iostream>

using namespace std;

long long FuncaoDeX(long long entrada){
	if(entrada >= 10000000){
		entrada = entrada - 3;
	}else{
		entrada = FuncaoDeX(FuncaoDeX(FuncaoDeX(entrada + 13)));
	}
	return entrada;
}

int main(){
	long long ent;
	cin>> ent;
	cout << FuncaoDeX(ent) << endl;
	return 0;
}
