#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void bfs(vector<bool> &visited,vector<vector<int>> edge,vector<int> &distance, int node){
    queue<int> q;
    q.push(node);
    visited[0] = true;
    visited[node] = true;
    
    while(!q.empty()){
        node = q.front();
        q.pop();
        
        for(int i=0; i < edge.size(); i++){
            if(edge[i][0] == node && !visited[edge[i][1]]){
                int n =edge[i][1];
                distance[n] = distance[node] + 1;
                q.push(n);
                visited[n] = true;
            }
            else if(edge[i][1] == node && !visited[edge[i][0]]){
                int n =edge[i][0];
                distance[n] = distance[node] + 1;
                q.push(n);
                visited[n] = true;
            }
        }
    }  
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    vector<bool> visited(n+1,false);
    vector<int> distance(n+1, 0);
    
    bfs(visited,edge,distance, 1);
    
    sort(distance.begin(), distance.end(), greater<int>());
    int max_dis = distance[0];
    for(int d : distance) if(d == max_dis) answer++;
    
    return answer;
}
