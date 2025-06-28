#include <iostream>
#include <algorithm> 
#include <string> 

using namespace std;
int main(){
    string in;

    cin>>in;

    transform(in.begin(), in.end(), in.begin(), ::toupper);

    if (in == "QUENTE")
    {
        cout<<28<<endl;
    }
    else if (in == "FRIO")
    {
        cout<<24<<endl;
    }
    else if (in == "MUITO")
    {
        cout<<20<<endl;
    }
    else if (in == "EXTREMAMENTE")
    {
        cout<<18<<endl;
    }
    else{
        cout<<"COMANDO INVALIDO"<<endl;
    }
    return 0;
}