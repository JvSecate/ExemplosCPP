#include <iostream>
#include <vector>

using namespace std;

vector<long long int> vec = {1, 1, 1, 2, 2, 3, 4, 5, 7, 9, 12, 16};

long long int termo(int n) {
    while (vec.size() < n) {
        int i = vec.size();
        long long int prox = vec[i-1] + vec[i - 5];
        vec.push_back(prox);
    }
    return vec[n - 1];
}

int main() {
    int n;
    while (cin >> n) {
        cout << termo(n) <<endl;
    }

    return 0;
}
