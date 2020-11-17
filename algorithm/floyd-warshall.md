# 플로이드-워셜 알고리즘 (Floyd-Warshall algorithm)

벨만-포드 알고리즘과 다익스트라 알고리즘과 달리 모든 최단 경로를 구하는 알고리즘 (All pairs shortest path algorithm)
_(물론 두 알고리즘도 모든 정점에대해 수행하면 모든 최단 경로를 구할 수 있다.)_

<br>

## 특징

- 음의 가중치 허용
- optimal substructure 개념 이용
- 배열을 이용하여 구현
- 밀집그래프에서 모든 edge간 경로 구할때 적합

<br>

## Pesudo Code

```
 let dist be a |V| × |V| array of minimum distances initialized to ∞
 let p be a |V| × |V| array of previous node initialized to null
 for each edge (u,v)
    dist[u][v] ← w(u,v)  // edge (u,v)의 가중치
    next[u][v] ← u      // 연결된 edge는 시작값으로 초기화

 for each vertex v
    dist[v][v] ← 0      //사이클을 허용하지 않으니 자기자신은 0

 for i from 1 to |V|
    for j from 1 to |V|
       for k from 1 to |V|
          if (dist[i][j] > dist[i][k] + dist[k][j])
             dist[i][j] ← dist[i][k] + dist[k][j]
             next[i][j] ← next[k][j]
```

<br>

## 구현 방법

1. 그래프 edge가 주어졌을때, edge들의 정보를 이용하여 각 edge간 거리 정보를 저장할 distance 2차원 행렬과 경로를 구하기 위해 이전 노드를 저장할 previous 2차원 행렬생성한다.

2. distance 행렬은 Infinity로 previous 행렬은 NIL(-1)로 초기화한다.
3. 그래프 G의 edge들의 가중치의 정보를 이용해 distance행렬을 초기화하고 자기의 거리는 0으로 초기화
4. 3중 반복문을 이용하여, 현재까지 계산된 i - j까지의 경로 값보다 사이에 k를 경유하는 경로 값이 더 작다면 값을 바꿔준다.

<br>

## 시간복잡도

매번 모든 노드들의 조합에 대해서 현재까지의 최단 경로를 구하고 총 \|V-1\|번 반복하기 때문에 O(\|V\|^3)의 시간복잡도를 갖는다.

i-j까지의 경로 중 k를 경유하는 값이 더작다면 값을 교환하는 방식으로 k는 V-1번 이 올 수 있으며 목적지 노드인 j도 V-1번, i도 V-1번으로 총 O(\|V\|^3)의 시간을 갖는다.

<br>

## 구현 코드

<br>

아래 코드는 사이클이없는 방향의 그래프이고, 양의 가중치를 무작위로 생성한 그래프이다.

<details>
    <summary style="font-Weight : bold; font-size : 15px; color : #FE642E;" > 소스코드  c++ ( 접기 / 펼치기 )</summary>
    <div>

```cpp
#include <time.h>  //시간 측정

#include <algorithm>  //for_each
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
#include <string>
#include <vector>

#define INFINITY 214000000
#define NIL -1
#define II std::pair<int, int>  // first = weight, second = dest

typedef struct edge {
    int src;     //출발 vertex
    int dest;    //도착 vertex
    int weight;  //가중치(비용)
} edge;

class Graph {
   private:
    edge e;

   public:
    Graph(int src = 0, int dest = 0, int weight = 0) {
        this->e.src = src;
        this->e.dest = dest;
        this->e.weight = weight;
    }
    int getSrc() { return this->e.src; }
    int getDest() { return this->e.dest; }
    int getWeight() { return this->e.weight; }
};

void CalcTime();
void randomPush(std::vector<Graph> &);     // graph에 사이클 없는 연결그래프 cost값 무작위 생성
void print_edge_info(std::vector<Graph>);  // graph 간선들 보기
void make_adj_matrix(std::vector<Graph>, std::vector<std::vector<int>> &);  //주어진 그래프를 인접행려로 표현
std::vector<std::vector<II>> floyd_warshall(std::vector<std::vector<int>>);

int V;                                 // vertex 개수
clock_t start, finish, used_time = 0;  //실행 시간 측정을 위한 변수

int main() {
    std::vector<Graph> g;                       // graph g
    std::vector<std::vector<II>> shortestPath;  // first = cost / second = previous node
    std::vector<std::vector<int>> adjMatrix;

    randomPush(g);       //간선 random 삽입
    print_edge_info(g);  // edge info print

    make_adj_matrix(g, adjMatrix);  //주어진 그래프를 인접행렬로 만들기

    start = clock();
    shortestPath = floyd_warshall(adjMatrix);
    finish = clock();

    std::cout << "\ncost : \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (shortestPath[i][j].first == INFINITY)
                std::cout << "INF"
                          << " ";
            else
                std::cout << shortestPath[i][j].first << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\npath : \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (shortestPath[i][j].second == NIL)
                std::cout << "NIL"
                          << " ";
            else
                std::cout << shortestPath[i][j].second << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            std::cout << "src -> " << i + 1 << " dest : " << j + 1 << " path : ";
            int p = shortestPath[i][j].second;
            std::string str = "";

            while (p != NIL) {
                str = std::to_string(p + 1) + " " + str;
                p = shortestPath[i][p].second;
            }
            std::cout << str << std::endl;
        }
        std::cout << std::endl;
    }

    CalcTime();
    return 0;
}

std::vector<std::vector<II>> floyd_warshall(std::vector<std::vector<int>> matrix) {
    std::vector<std::vector<II>> dp(V, std::vector<II>(V, {0, 0}));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dp[i][j].first = matrix[i][j];
            dp[i][j].second = (dp[i][j].first != INFINITY) ? i : NIL;
        }
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            for (int k = 0; k < V; k++) {
                if (dp[i][j].first > dp[i][k].first + dp[k][j].first) {
                    dp[i][j].first > dp[i][k].first + dp[k][j].first;
                    dp[i][j].second = dp[k][j].second;
                }
            }
        }
    }
    return dp;
}

void make_adj_matrix(std::vector<Graph> g, std::vector<std::vector<int>> &adj) {
    adj.assign(V, std::vector<int>(V, INFINITY));
    for (int i = 0; i < g.size(); i++) {
        int src = g[i].getSrc();
        int dest = g[i].getDest();
        int weight = g[i].getWeight();

        if (adj[src][dest] > weight) {
            adj[src][dest] = weight;
        }
    }
}

/*vertex수 입력받은 후 그래프 간선 가중치 random 삽입*/
void randomPush(std::vector<Graph> &g) {
    std::cout << "create number of Vertex : ";
    std::cin >> V;

    srand((unsigned int)time(NULL));
    for (int i = 0; i < V - 1; i++) {
        g.push_back(Graph(i, i + 1, rand() % 1000));
        for (int j = i + 1; j < V; j++) {
            g.push_back(Graph(i, j, rand() % 1000));
        }
    }
    for (int i = (rand() % 3); i < V - 1; i += (rand() % 10)) {
        g.push_back(Graph(i, i + 1, rand() % 1000));
        for (int j = i + 1; j < V; j += (rand() % 10)) {
            g.push_back(Graph(i, j, rand() % 1000));
        }
    }
}

void print_edge_info(std::vector<Graph> g) {
    std::cout << "edge info : \n";
    std::for_each(g.begin(), g.end(), [](Graph a) {
        std::cout << "src : " << a.getSrc() + 1 << " desc : " << a.getDest() + 1 << " weight : " << a.getWeight() << std::endl;
    });
}

//실행 시간을 측정 및 출력하는 함수
void CalcTime() {
    used_time = finish - start;
    printf("\n*********** result **********\n     time : %lf sec\n", (double)(used_time) / CLOCKS_PER_SEC);
}
```

</div>

</details>
