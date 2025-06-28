#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, V, r = 1;
    vector<int> j = {0, 0, 0};

    cin >> N;
    while (N != -1) {
        
        N -= 1;
        cin >> V;
        while (V != -1) {
            switch (V) {
                case 1:
                    j[N] += 5;
                    break;
                case 2:
                    j[N] += 10;
                    break;
                case 3:
                    j[N] += 15;
                    break;
                case 4:
                    j[N] += 20;
                    break;
                case 5:
                    j[N] += 50;
                    break;
                case 0:
                    N = (N + 1) % 3;
                    break;
            }
            cin >> V;
        }
        if (r > 1) {
            cout << endl;
        }
        cout << "RODADA " << r << endl;
        if (j[0] > j[1] && j[0] > j[2]) {
            cout << "Ganhador com " << j[0] << " pontos" << endl
                 << "Jogador 1" << endl;
        } else if (j[1] > j[0] && j[1] > j[2]) {
            cout << "Ganhador com " << j[1] << " pontos" << endl
                 << "Jogador 2" << endl;
        } else if (j[2] > j[1] && j[2] > j[0]) {
            cout << "Ganhador com " << j[2] << " pontos" << endl
                 << "Jogador 3" << endl;
        } else if (j[0] == j[1] && j[0] != j[2]) {
            cout << "Empate com " << j[0] << " pontos" << endl
                 << "Jogador 1, Jogador 2" << endl;
        } else if (j[0] == j[2] && j[0] != j[1]) {
            cout << "Empate com " << j[0] << " pontos" << endl
                 << "Jogador 1, Jogador 3" << endl;
        } else if (j[2] == j[1] && j[2] != j[0]) {
            cout << "Empate com " << j[1] << " pontos" << endl
                 << "Jogador 2, Jogador 3" << endl;
        } else if (j[2] == j[1] && j[2] == j[0]) {
            cout << "Empate com " << j[0] << " pontos" << endl
                 << "Jogador 1, Jogador 2, Jogador 3" << endl;
        }
        j = {0, 0, 0};
        

        cin >> N;
        r++;
    }

    return 0;
}
