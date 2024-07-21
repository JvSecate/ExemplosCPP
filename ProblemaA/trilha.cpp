#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>

# define INF 0x3f3f3f3f

using namespace std;


void addNo(map<string, vector<pair<string, int>>> &adj, const string &u, const string &v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

vector<string> dijkstra(const map<string, vector<pair<string, int>>> &adj, const string &origem, const string &destino) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    
    map<string, int> dist;
    map<string, string> pai;
    
    for (const auto &node : adj) {
        dist[node.first] = INF;
    }
    dist[origem] = 0;
    pq.push(make_pair(0, origem));

    while (!pq.empty()) {
        int distAtual = pq.top().first;
        string noAtual = pq.top().second;
        pq.pop();

        if (noAtual == destino) break;

        for (const auto &neighbor : adj.at(noAtual)) {
            string noVizinho = neighbor.first;
            int peso = neighbor.second;

            int distNova = distAtual + peso;
            if (distNova < dist[noVizinho]) {
                dist[noVizinho] = distNova;
                pai[noVizinho] = noAtual;
                pq.push(make_pair(distNova, noVizinho));
            }
        }
    }

    vector<string> path;
    for (string at = destino; at != origem; at = pai[at]) {
        path.push_back(at);
        if (pai.find(at) == pai.end()) {
            return {};
        }
    }
    path.push_back(origem);
    reverse(path.begin(), path.end());

    return path;
}

int main() {

    int n, m;
    string s, b;
    cin >> n >> m;
    cin >> s >> b;

    map<string, vector<pair<string, int>>> adj;

    string a, z;
    int d;

    while (cin >> a >> z >> d) {
        addNo(adj, a, z, d);
    }

    vector<string> path = dijkstra(adj, s, b);

    cout<<"Percurso: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << "--> ";
        }
    }
    
    cout<<endl;
    return 0;
}