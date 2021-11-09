# Topological Sort (위상 정렬)

조건 : 방향이 있고 사이클이 없는 그래프 (Directed Acyclic Graph)

DAG일때, 방향성을 거스르지 않고 나열하는 것.

순서가 있는 작업을 차례로 수행해야할때 순서를 결정해주기 위해 사용하는 알고리즘.

대학 커리큘럼의 선수과목이나 엄무의 일정을 시간 순서대로 배치한것이 그 예이다.

<br><br>

## 특징

---

- 방향이 있는 그래프이어야한다. (directed)

- 사이클이 없어야 한다. (Acyclic)

<br><br>

## Pesudo Code

---

- InDegree 이용방법

```
Topological Sort(G){
    INITIALIZE-InDegree(G.V)
    result ← ∅

    for each indegree[v] == 0
        Q <- v

    for i = 1 to |G.V|
        u = Pop(Q);
        result <- u
        for each v ∈ Adj[u]
            indegree[u] ← indegree[u] - 1
            if (inDegree[u] == 0)
                Q <- u
 }
```

<br>

- dfs 이용방법

```
Topological Sort(G){
    result ← ∅
    visit ← ∅

    for i =1 to |G.V|
        if not visit[i]
            dfs(i)
}

dfs(v){
    visit[v] <- true
    for each v ∈ Adj[u]
        if not visit[u]
            dfs(u)
    result <- v
}
```

<br><br>

## 구현 방법

---

### InDegree 이용

1. 모든 vertex에 대해 InDegree값을 초기화한다.
1. 진입 차수 (indegree)가 0인 값을 큐에 삽입해준다.
1. 큐에서 1개 vertex, v를 pop해준다.
1. v를 stack에 쌓는다. (정렬한 값을 담는 것이 stack)
1. v에 연결된 vertex들의 indegree값을 1감소 시켜준다.
1. 진입 차수가 0인 정점들을 큐에 삽입한다.
1. 3-6번을 Vertex수만큼 반복한다.
1. 만약에 큐가 비어있다면, 사이클이 존재하는 그래프이다.
   <br>_(큐가 비어있다면 indegree가 0인 값이 없었다는 소리. 즉, 사이클 발생)_

<br>

### dfs 이용

1. 방문하지 않은 vertex들을 dfs함수 진행.

1. dfs
   1. 해당 vertex 방문표시
   1. 인접 vertex에 대해 방문하지 않았다면 dfs함수 진행
   1. dfs함수 종료시 stack에 push

<br><br>

## 시간 복잡도

---

- indegree방법은 초기화하는데 O(V), 큐에 삽입, 제거 하는게 O(V)번씩 소요되며, indegree를 1감소 시켜주는게 O(E)번 일어난다. (indegree를 1감소해주는건 edge를 삭제해주는거와 같기 때문)
  <br><br>
  따라서, O(V+E)의 시간복잡도를 갖는다.

- dfs방법또한 모든 vertex에 대해 방문했는지 확인하고, 연결된 모든 E를확인후 dfs수행하기때문에 O(V+E)를 갖는다.
  <br><br>

## 구현 코드

---

<br>

아래 코드는 사이클이없는 무작위의 무방향의 그래프이다.
정렬하게 되면 오름차순으로 정렬되게 edge를 생성하는 그래프

<details>
    <summary style="font-Weight : bold; font-size : 15px; color : #FE642E;" > 소스코드  c++ ( 접기 / 펼치기 )</summary>
    <div>

```cpp
#include <time.h>  //시간 측정

#include <algorithm>  //for_each
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
#include <queue>
#include <vector>

typedef struct edge {
    int src;   //출발 vertex
    int dest;  //도착 vertex
} edge;

class Graph {
   private:
    edge e;

   public:
    Graph(int src = 0, int dest = 0) {
        this->e.src = src;
        this->e.dest = dest;
    }
    int getSrc() { return this->e.src; }
    int getDest() { return this->e.dest; }
};

void CalcTime();
void randomPush(std::vector<Graph> &);     // graph에 사이클 없는 연결그래프 cost값 무작위 생성
void print_edge_info(std::vector<Graph>);  // graph 간선들 보기

void countInDegree(std::vector<Graph>, std::vector<int> &);
std::vector<int> topologicalSort_queue(std::vector<int>, std::vector<Graph>);
std::vector<int> topologicalSort_dfs(std::vector<Graph>);
void dfs(int, std::vector<int> &, std::vector<int> &, std::vector<Graph>, std::vector<int> &);

int V;                                 // vertex 개수
clock_t start, finish, used_time = 0;  //실행 시간 측정을 위한 변수

int main() {
    std::vector<Graph> g;  // graph g
    std::vector<int> inDegree;
    std::vector<int> result;

    randomPush(g);       //간선 random 삽입
    print_edge_info(g);  // edge info print

    countInDegree(g, inDegree);

    start = clock();
    result = topologicalSort_queue(inDegree, g);  // inDegree 이용
    // result = topologicalSort_dfs(g);                    //dfs 이용
    finish = clock();

    /*DFS이용시 SORT PRINT*/
    /* std::cout << "\nTopological Sort : ";
    for (int i = result.size() - 1; i >= 0; i--) {
        std::cout << result[i] << " ";
    } */

    /*INDEGREE방법 이용시 SORT PRINT*/
    for_each(result.begin(), result.end(), [](int v) { std::cout << v << " "; });

    CalcTime();
    return 0;
}

void countInDegree(std::vector<Graph> g, std::vector<int> &inDegree) {
    inDegree.assign(V, 0);
    for (int i = 0; i < g.size(); i++) {
        inDegree[g[i].getDest()]++;
    }
}

std::vector<int> topologicalSort_queue(std::vector<int> inDegree, std::vector<Graph> g) {
    std::vector<int> sort;
    std::queue<int> q;

    /*inDegree가 0인 선행차수가 없는 초기 노드들 큐에 삽입*/
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    /*process*/
    for (int i = 0; i < V; i++) {
        if (q.empty()) {
            std::cout << "No DAG (Direced Acyclic Graph) " << std::endl;
            exit(1);
        }
        int top = q.front();
        q.pop();
        sort.push_back(top);

        /*pop한 정점과 연결된 모든 edge들 indegree 1감소 시키고 0이라면 push*/
        for (int i = 0; i < g.size(); i++) {
            if (g[i].getSrc() == top) {
                inDegree[g[i].getDest()]--;
                if (inDegree[g[i].getDest()] == 0) {
                    q.push(g[i].getDest());
                }
            }
        }
    }
    return sort;
}

std::vector<int> topologicalSort_dfs(std::vector<Graph> g) {
    std::vector<int> sort;                    // vertex를 규칙에 맞게 sort
    std::vector<int> visited(V, false);       //방문한 vertex표시
    std::vector<int> selectVertex(V, false);  //선택한 vertex표시

    /*모든 vertex에 대해 dfs*/
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, selectVertex, g, sort);
        }
    }
    return sort;
}

void dfs(int v, std::vector<int> &visited, std::vector<int> &selectVertex, std::vector<Graph> g, std::vector<int> &sort) {
    /*방문 vertex 표시*/
    visited[v] = true;

    /*연결된 edge들 검사*/
    for (int i = 0; i < g.size(); i++) {
        if (g[i].getSrc() == v) {
            /*방문안한 vertex라면 dfs수행*/
            if (!visited[g[i].getDest()]) {
                dfs(g[i].getDest(), visited, selectVertex, g, sort);
            }
            /*방문한 vertex인데, 아직 선택안한 vertex. 즉, 부모~조상노드 => cycle이 발생*/
            else {
                if (!selectVertex[g[i].getDest()]) {
                    std::cout << "No DAG (Direced Acyclic Graph) " << std::endl;
                    exit(1);
                }
            }
        }
    }

    /*더이상 edge가 없으면 가장 stack에 넣고 표시*/
    selectVertex[v] = true;
    sort.push_back(v);
}

/*vertex수 입력받은 후 그래프 간선 random 삽입*/
void randomPush(std::vector<Graph> &g) {
    std::cout << "create number of Vertex : ";
    std::cin >> V;

    srand((unsigned int)time(NULL));
    for (int i = 0; i < V - 1; i++) {
        g.push_back(Graph(i, i + 1));
        for (int j = i + 2; j < V; j += rand() % 3) {
            g.push_back(Graph(i, j));
        }
    }
}

void print_edge_info(std::vector<Graph> g) {
    std::cout << "edge info : \n";
    std::for_each(g.begin(), g.end(), [](Graph a) { std::cout << "src : " << a.getSrc() << " desc : " << a.getDest() << std::endl; });
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
