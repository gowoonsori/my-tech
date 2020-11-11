# Dijkstra's Algorithm

그래프 중에서 `최단 경로 (shortest path)`를 찾는 알고리즘중에 하나이다.

`우선순위 큐`의 방법을 이용하는 알고리즘이다.

vertex를 한개씩 선택하며 트리를 구성하는 방법으로 `MST`를 찾는 `Prim's 알고리즘`과 굉장히 흡사하다.

Prim 알고리즘에서 vertex_key값 갱신에 dp방법을 추가해주면 된다.

<br><br>

## 특징

- 정점 선택 기반
- 시작 정점부터 출발하여 해당 노드까지의 최소 비용을 기록하는 배열을 이용하여 구하는 방식

- 자료구조중 하나인 `우선순위 큐`를 이용하며, 우선순위 큐를 어떻게 구현했는가가 시간복잡도에 영향

-

<br><br>

## Pesudo Code

```
MST-Prim(G, w, r)
    Q = V[G];
    for each u ∈ Q
        key[u] = INFINITY;
    key[r] = 0;
    p[r] = NULL;
    while (Q not empty)
        u = ExtractMin(Q);
        for each v ∈ Adj[u]
            if (v ∈ Q and w(u,v) < key[v])  //Decrease-key
                p[v] = u;
                key[v] = w(u,v);

```

<br><br>

## 구현 방법

<br>

1. vertex들의 key값을 Infinity로 초기화한다.
1. start vertex의 key값을 0으로 초기화한다. (어떤 vertex를 선택하더라고 MST가 나온다.)
1. 현재 vertex에 인접한 vertex들 중 선택하지 않았고, 가장 vertex의 key값이 작은 vertex을 찾는다. (`exract-min = 최소값 추출`)
1. 현재 vertex를 선택한다.
1. 인접한 vertex중 vertex의 key값보다 간선의 가중치가 더 작다면 key값을 가중치로 갱신 한다. (`decrease -key`)
1. 인접한 vertex중 선택하지 않았고, 가장 vertex의 key값이 작은 vertex를 기준으로 `3번`부터 다시 반복한다.

1. 모든 vertex가 선택되었다면 끝난다.

<br>

### 인접 행렬

---

위에 설명한 `3번 방법`의 extract-min을 아래와 같이 배열로 구현하며, 매번 V회 반복한다.

```cpp
    int v = -1;              //인접 vertex중 가장 작은 가중치를 갖는 vertex
    int min_key = INFINITY;  //인접 vertex중 가장 작은 가중치

    /* 인접 vertex중 가장 작은 가중치를 갖는 vertex 찾기*/
    for (int j = 0; j < V; j++) {
        if (!selected[j] && (min_key > vertex_key[j])) {
            v = j;
            min_key = vertex_key[j];
        }
    }
```

아래는 `5번 방법`으로 인접한 vertex중 vertex의 key값보다 간선의 가중치가 더 작다면 key값을 가중치로 갱신 한다.

```cpp
    for (int j = 0; j < V; j++) {
        if (vertex_key[j] > adjMatrix[v][j]) {
            vertex_key[j] = adjMatrix[v][j];
        }
    }
```

<br>

### 인접 리스트

---

인접 리스트는 인접한 vertex의 가중치를 priority queue를 통해 저장한다.

때문에, `3번 방법의` exract-min은 맨앞에서 pop을 시켜 찾아주면 된다.

```cpp
std::set<II> q;  //이진힙으로 queue 만들기 ( set은 red-black tree로 만들어짐 )
auto u = q.begin();  // extract-min
```

`5번 방법`으로 인접한 vertex중 vertex의 key값보다 간선의 가중치가 더 작다면 key값을 가중치로 갱신 하는 방법은 아래와 같이 인접한 간선의 개수만큼 수행한다.

```cpp
    /*select한 vertex와 인접한 간선인 e*/
        for (auto e : adjList[현재 vertex]) {
            /* 선택되지 않은 vertex이고 해당 vertex의 key값과 edge의 cost를 비교해 cost가 더 작다면*/
            if (!selected[인접한 vertex] && vertex_key[인접한 vertex] > 가중치) {
                q.erase({vertex_key[인접한 vertex], e.second});  //같은 vertex로 향하는 간선중 weight가 더 작은 간선이 있다면 그 전 간선은 삭제
                vertex_key[인접한 vertex] = 가중치;  // vertex key값 갱신
                q.insert({가중치, 인접한 vertex});   //큐에 삽입
            }
        }
```

<br><br>

## 시간 복잡도

<br>

시간복잡도는 초기화하는데 O(\|V\|), MST계산하는데 O(\|V\|) \* T(extract-min) (가장 적은 값 추출하는데 걸린시간) + O(\|E\|) \* T(decrease-key) ( key값 변경하는데 걸리는 시간 )와 같다.

따라서, priority-queue를 어떻게 구현했는지에 따라 시간복잡도가 달라진다.

일반 배열로 구현했을 경우 T(extract)가 O(\|V\|), T(decrease)는 O(1)만큼 걸려 총 O(\|V^2\|)이 걸린다.

binary heap(이진 힙)으로 구현하면 T(extract)가 O(lgV), T(decrease)는 O(lgV)만큼 걸려 총 O(VlgV) + O(ElgV) 이기 때문에 O((E+V)lgV)만큼 걸린다.
<br>무방향 그래프일때 E의 최소값은 V-1로 거의 대부분이 \|E\| > \|V\| 이므로 O(\|E\|lg\|V\|)라고 할 수 있다.

priority queue를 이진 힙이 아닌 fibonacci heap으로 구현하면 decrease-key의 시간을 좀더 줄일 수 있다.
<br>decrease-key시간이 O(1)만큼 걸리기 때문에 O(E+VlgV)라고 할 수 있다.
<br>
O(E) or O(VlgV) 인 이유는 최악의 경우에 E는 O(V^2)이기 때문이다.

<br><br>

## 구현 코드

<br>

아래 코드는 사이클이없는 무방향의 그래프이고, 가중치를 무작위로 생성한 그래프이다.

<details>
    <summary style="font-Weight : bold; font-size : 15px; color : #FE642E;" > 소스코드  c++ ( 접기 / 펼치기 )</summary>
    <div>

```cpp
#include <time.h>  //시간 측정

#include <algorithm>  //for_each
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
#include <set>
#include <vector>

#define INFINITY 2147483647
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

int prim_adjList_heap(std::vector<Graph> &, std::vector<std::vector<II>>,
                      int);  // Adj list와 priority queue 이용해 구현 --> set은 red-black-tree
void make_adj_list(std::vector<Graph>, std::vector<std::vector<II>> &);  //주어진 그래프를 인접리스트로 표현

int prim_adjMatrix(std::vector<Graph> &, std::vector<std::vector<int>>, int);  // Adj matrix로 구현
void make_adj_matrix(std::vector<Graph>, std::vector<std::vector<int>> &);     //주어진 그래프를 인접행렬로 표현

int V;                                 // vertex 개수
clock_t start, finish, used_time = 0;  //실행 시간 측정을 위한 변수

int main() {
    std::vector<Graph> g;    // graph g
    int minimum_weight = 0;  // minimum cost
    std::vector<std::vector<II>> adjList;
    std::vector<std::vector<int>> adjMatrix;

    randomPush(g);       //간선 random 삽입
    print_edge_info(g);  // edge info print

    make_adj_list(g, adjList);      //주어진 그래프를 인접리스트로 만들기
    make_adj_matrix(g, adjMatrix);  //주어진 그래프를 인접행렬로 만들기

    start = clock();
    minimum_weight = prim_adjMatrix(g, adjMatrix, 0);  //인접행렬을 이용한 prim's algorithm (0번노드를 첫 노드로 시작)
    // minimum_weight = prim_adjList_heap(g, adjList, 0);  //인접리스트를 이용한 prim's algorithm (0번노드를 첫 노드로 시작)
    finish = clock();
    std::cout << "\nminimum cost : " << minimum_weight << std::endl;
    CalcTime();

    return 0;
}

int prim_adjList_heap(std::vector<Graph> &g, std::vector<std::vector<II>> adjList, int start) {
    int sum = 0;
    std::set<II> q;                               //이진힙으로 queue 만들기 ( set은 red-black tree로 만들어짐 )
    std::vector<int> vertex_key(V, INFINITY);     // vertex의 최소 weight값 계산
    std::vector<bool> selected(g.size(), false);  //선택된 vertex인가

    vertex_key[start] = 0;
    q.insert(II(0, start));  //시작 노드 가중치 0으로 시작
    std::cout << "\nroute";

    /*vertex 수만큼 반복한다
     while대신 for(int i=0; i < V ; i++)로 해도 무방
    */
    while (!q.empty()) {
        /*extract min*/
        int select_key = q.begin()->second;
        int min_of_key = q.begin()->first;
        q.erase(q.begin());

        if (selected[select_key]) {
            std::cout << " NOT MST" << std::endl;
            exit(1);
        }

        sum += min_of_key;
        selected[select_key] = true;
        std::cout << "dest : " << select_key << " (dis : " << vertex_key[select_key] << ")" << std::endl;

        /*decrease key*/
        for (auto e : adjList[select_key]) {
            if (!selected[e.second] && vertex_key[e.second] > e.first + vertex_key[select_key]) {
                q.erase({vertex_key[e.second], e.second});  //같은 노드로 향하는 간선중 weight가 더 작은 간선이 있다면 그 전 간선은 삭제
                q.insert({e.first, e.second});  //큐에 삽입
                vertex_key[e.second] = e.first + vertex_key[select_key];
            }
        }
    }

    std::cout << std::endl;
    return sum;
}

void make_adj_list(std::vector<Graph> g, std::vector<std::vector<II>> &adj) {
    adj.resize(V);
    bool isEdge;
    for (int i = 0; i < g.size(); i++) {
        isEdge = false;
        int src = g[i].getSrc();
        int dest = g[i].getDest();
        int weight = g[i].getWeight();

        /*동일 vertex로 향하는 간선중 가장 작은 값만가지고 인접 리스트를 만들기 위한 코드*/
        if (adj[src].empty()) {
            adj[src].push_back({weight, dest});
        } else {
            for (int j = 0; j < adj[src].size(); j++) {
                if (adj[src][j].second == dest) {
                    isEdge = true;
                    if (adj[src][j].first > weight) {
                        adj[src][j].first = weight;
                    }
                }
            }
            if (!isEdge) adj[src].push_back({weight, dest});
        }

        isEdge = false;
        if (adj[dest].empty()) {
            adj[dest].push_back({weight, src});
        } else {
            for (int j = 0; j < adj[dest].size(); j++) {
                if (adj[dest][j].second == src) {
                    isEdge = true;
                    if (adj[dest][j].first > weight) {
                        adj[dest][j].first = weight;
                    }
                }
            }
            if (!isEdge) adj[dest].push_back({weight, src});
        }
    }
}

int prim_adjMatrix(std::vector<Graph> &g, std::vector<std::vector<int>> adjMatrix, int start) {
    int sum = 0;
    std::vector<int> vertex_key(V, INFINITY);     // vertex의 최소 weight값 계산
    std::vector<bool> selected(g.size(), false);  //선택된 vertex인가

    vertex_key[start] = 0;  //시작노드 key값 0으로 시작
    std::cout << "\nroute";
    /*vertex 수만큼 반복한다*/
    for (int i = 0; i < V; i++) {
        int select_idx = -1;     //인접 vertex중 가장 작은 가중치를 갖는 vertex
        int min_key = INFINITY;  //인접 vertex중 가장 작은 가중치

        /* 인접 vertex중 가장 작은 가중치를 갖는 vertex 찾기*/
        for (int j = 0; j < V; j++) {
            if (!selected[j] && (min_key > vertex_key[j])) {
                select_idx = j;
                min_key = vertex_key[j];
            }
        }

        /*현재 코드에서는 연결안된 그래프는 주어지지 않기 때문에
          없어도 무방하지만 만약을 위한 에러처리*/
        if (select_idx == -1) {
            std::cout << "Not MST" << std::endl;
            exit(1);
        }

        selected[select_idx] = true;
        sum += min_key;
        std::cout << " -> " << select_idx << "(cost : " << min_key << ")";

        /*인접 vertex의 weight가 vertex_key값보다 작다면 key값 갱신 */
        for (int j = 0; j < V; j++) {
            if (!selected[j] && vertex_key[j] > adjMatrix[select_idx][j]) {
                vertex_key[j] = adjMatrix[select_idx][j];
            }
        }
    }
    std::cout << std::endl;
    return sum;
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
        if (adj[dest][src] > weight) {
            adj[dest][src] = weight;
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
        std::cout << "src : " << a.getSrc() << " desc : " << a.getDest() << " weight : " << a.getWeight() << std::endl;
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

<br><br>
