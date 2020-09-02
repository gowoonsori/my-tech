#include <iostream>
#include <cstring>

using namespace std;

int graph[1001][1001];
int visited[1001];
int N,M,V;

void dfs(int v){
    cout<< v << " ";
    visited[v]=1;
    for(int i=1; i<=N ;i++){
        if(graph[v][i] && !visited[i])
            dfs(i);
    }

}

int main(){
    int a,b;

    memset(graph,0,sizeof(graph));
    memset(visited,0,sizeof(visited));

    cout <<"정점, 간선, 시작 정점 : ";
    cin >> N >> M >> V;
    for(int i=0; i<M; i++){
        cout << "연결된 두 정점 번호 : ";
        cin >>  a >> b;
        graph[a][b]=1;
        graph[b][a]=1;
    }
    dfs(V);
}