#include <iostream>
#include <string>

using namespace std;

int main(){
    string l1, l2, msg, aux;
    
    getline(cin, l1);
    getline(cin, l2);
    getline(cin, msg);

    int num;
    int cont = 0, se = 1;
    for (char ch : msg) {
        
        aux += ch;
        cont++;
        if (cont == 5)
        {
            if (aux == "11011")
            {
                se = 1;
            }
            else if (aux == "11111")
            {
                se = 2;
            }
            else{
                if (se == 1)
                {
                    num = stoi(aux, 0, 2);
                    cout << l1.at(num);

                }
                else
                {
                    num = stoi(aux, 0, 2);
                    cout << l2.at(num);
                }
                
                
            }
            cont = 0;
            aux = "";
        }
        
    }

    cout<<endl;
    return 0;
}