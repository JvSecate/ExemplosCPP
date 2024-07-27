#include <iostream>
#include <string>
using namespace std;

int main() {
    string ent;
    int num = 0, par = 0, impar = 0;
    cin >> ent;

    for (char digit : ent) {
        num = digit - '0';
        if (num % 2 == 0) {
            par += num;
        } else {
            impar += num;
        }
    }

    if (par % 3 == 0) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    if (impar % 3 == 0) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
