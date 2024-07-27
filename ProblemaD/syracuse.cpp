#include <iostream>
using namespace std;

int main(){

    long long int num = 0;
    int cont;
    while (cin>>num)
    {
        cont = 0;
        while(num!=1){
            if (num%2 == 0)
            {
                num /= 2;
                cont++;
            }
            else{
                num = (num*3)+1;
                cont++;
            }
        }
        cout<<cont<<endl;
    }
    
    return 0;
}
