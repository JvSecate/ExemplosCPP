#include <iostream>

using namespace std;
int main() {
    float gasolina, etanol;
    cin >> gasolina >> etanol;
    if((etanol / gasolina)< 0.7) {
        cout << "ETANOL" << endl;
    }else {
        cout << "GASOLINA" << endl;
    }
    return 0;
}

