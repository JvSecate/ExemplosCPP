#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
float toFloat(string input) {

    size_t pos = input.find_first_of("0123456789");
    string num = input.substr(pos);
    return stof(num);
}

int main() {
    string input;
    float quant[4], aux[4], n=1;
    cin>>input;
    cin>>quant[0]>>quant[1]>>quant[2]>>quant[3];
    int valor = toFloat(input)*100;
    float rest;
	float falta;
	int fig;
	fig=((quant[0]*25)+(quant[1]*10)+(quant[2]*5)+(quant[3]*1))/valor;
	
	valor=valor*fig;
	falta=((valor/25)-quant[0]);
    if(falta<0){
		quant[0]=(-1)*falta;
    	falta=0;
	}else{
		quant[0]=0;
	}
	valor=(valor%25)+(falta*25);
	
	falta=((valor/10)-quant[1]);
    if(falta<0){
		quant[1]=(-1)*falta;
    	falta=0;
	}else{
		quant[1]=0;
	}
	valor=(valor%10)+(falta*10);
    
	falta=((valor/5)-quant[2]);
    if(falta<0){
		quant[2]=falta*(-1);
    	falta=0;
	}else{
		quant[2]=0;
	}
	valor=(valor%5)+(falta*5);
	
	falta=((valor/1)-quant[3]);
    if(falta<0){
		quant[3]=(-1)*falta;
    	falta=0;
	}else{
		quant[3]=0;
	}
	valor=(valor%1)+(falta*1);
    
    cout<<fig<<endl<<quant[0]+quant[1]+quant[2]+quant[3]<<endl;
    return 0;
}
