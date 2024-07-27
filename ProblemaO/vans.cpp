#include <iostream>

using namespace std;
int main(){
    int h, v, t, res;

    cin >> h >> v >> t;

    res = (t * (v*1000)) / h;
    cout<<res<<endl;
    return 0;
}