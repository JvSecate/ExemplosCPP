#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;

    int quant[26] = {0};

    // Count the occurrences of each letter
    for (char ch : str) {
        quant[ch - 'a']++;
    }

    int quantPar = 0;
    int quantImpar = 0;

    for (int i = 0; i < 26; ++i) {
        if (quant[i] > 0) {
            if (quant[i] % 2 == 0) {
                quantPar++;
            } else {
                quantImpar++;
            }
        }
    }

    if(quantImpar < 2){
        cout<<1;
    }
    else{
        cout<<0;
    }

    cout<<endl;
    return 0;
}
