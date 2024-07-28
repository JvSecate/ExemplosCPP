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
    float quant[4], aux[4], fig = 0 , n=1;
    cin>>input;
    cin>>quant[0]>>quant[1]>>quant[2]>>quant[3];
    float valor = toFloat(input);
    float rest;

    do
    {   
        rest += valor*100;
        cout<<rest<<endl;
        aux[0] = floor(rest/25);
        if (aux[0] > quant[0])
        {
            aux[0] = quant[0];
        }
        rest -= (aux[0]*25);
        cout<<rest<<endl;

        aux[1] = floor(rest/10);
        if (aux[1] > quant[1])
        {
            aux[1] = quant[1];
        }
        rest -= (aux[1]*10);
        cout<<rest<<endl;
        aux[2] = floor(rest/5);
        if (aux[2] > quant[2])
        {
            aux[2] = quant[2];
        }
        rest -= (aux[2]*5);
        cout<<rest<<endl;
        aux[3] = floor(rest/1);
        if (aux[3] > quant[3])
        {
            aux[3] = quant[3];
        }
        rest -= (aux[3]*1);
        cout<<rest<<endl;
        if(rest == 0){
            fig+=n;
            quant[0] -= aux[0];
            quant[1] -= aux[1];
            quant[2] -= aux[2];
            quant[1] -= aux[3];
            break;
        }
        else
        {
            n++;
            valor *= n;
        }

        
    } while (true);
    
    cout<<fig<<endl<<quant[0]+quant[1]+quant[2]+quant[3]<<endl;
    return 0;
}
