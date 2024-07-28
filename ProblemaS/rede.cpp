#include <iostream>
#include <vector>

using namespace std;

void addNo(vector <pair<int, int> > adj[], int a,
                                     int b, int p){
    adj[a].push_back(make_pair(b, p));
    adj[b].push_back(make_pair(a, p));                         
}

int main(){
    int n, m, u, v, p;
    cin>>n>>m;

    vector<pair<int, int> > adj[100];
    for (int i = 0; i < m; i++)
    {  
        cin>>u>>v>>p;
        addNo(adj, u, v, p);
    }
    
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (auto no : adj[i]) {
            dist[i][no.first] = no.second;
        }
    }
}