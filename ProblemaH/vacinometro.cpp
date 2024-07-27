#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	long long int num1, num2;
	float resul=0.0;
	
	cin>>num1;
	cin>>num2;
	resul = static_cast<float>(num2)/static_cast<float>(num1);
	resul = resul * 100; 
	cout<<fixed<<setprecision(1)<<resul<<"%"<<endl; 
	return 0;
}
