# Kruskal's Algorithm

그래프 중에서 `MST (Minumum Spannig Tree)`를 찾는 알고리즘중에 하나이다.

`Union-Find`알고리즘을 이용하며, 간선 (edge)의 가중치(weight)를 `오름차순으로 정렬`하여 가중치가 `사이클이 생기지 않는` 낮은 간선을 먼저 선택하는 방법.

사이클의 여부를 확인할때 `union-find` 알고리즘을 이용하여 찾게 된다.

<br>[union find 알고리즘 설명 보기](./DisjointSet-unionFind.md)

<br>

## 특징

- 탐욕적인 방법( Greedy Method )

- 간선 선택 기반 알고리즘
- 간선 선택 단계에서 사이클을 포함하지 않고 최소 비용 간선을 선택
- 부분 트리집합을 병합하면서 하나의 트리로 확장
- 희소그래프에 적합 ( V > E )
- 정렬 속도가 시간복잡도에 영향

<br>

## Pesudo Code

```
algorithm Kruskal(G) is
    T := ∅
    for each v ∈ G.V do
        MAKE-SET(v)
    for each (u, v) in G.E ordered by weight(u, v), increasing do
        if FIND-SET(u) ≠ FIND-SET(v) then
           T := T ∪ {(u, v)}
           UNION(FIND-SET(u), FIND-SET(v))
    return T
```

<br>

## 구현

```
1. 그래프의 edge(간선)의 가중치(비용)을 작은것 부터 큰 순서대로(오름차순)으로 정렬 한다.

2. 모든 간선에 대해 해당 간선의 두 vertex(정점)가 같은 집합에 속하는지 검사(Find)한다.

3-1. 두 vertex(정점)의 부분집합들이 서로 다르다면, 합쳐(union) 준다.

3-2. 두 vertex(정점)의 부분집합이 같은 집합이라면, 사이클이 생성되기 때문에 패스한다.

4. 총 선택한 edge(간선)의 비용을 계산해준다.
```

기본적으로 사이클이 생성되는지 검사하기 위해 `union-find`알고리즘이 쓰이며, kruskal 알고리즘의 `시간복잡도`는 edge를 `정렬하는 속도`와 밀접한 연관이 있다.

<br><br>

## 시간복잡도

make_set 하는데 O(V), 정렬하는데 걸리는 시간은 T (간선 E를 가지고 정렬 => O(E), O(1), O(ElgE), O(E^2) 등등 이 될 수있다.)

Union하기 위해 집합이 속하는지 검사하는 Find가 O(E)번 일어나며, Find 에 O(lgV)번 일어난다.
<br>따라서 Union을 끝내는데 O(ElgV)만큼 걸린다.

때문에 O(ElgV + T)만큼 걸리게 된다.

구현하는 데 있어, 우선 본인의 힘으로 작성해보고 도저히 안되겠을 때 아래의 코드를 보자.

<br><br>

## 구현 코드

구현 방법은 사람마다 정말 다양하니 참고만 하도록 하자

<details>
  <summary style="font-Weight : bold; font-size : 15px; color : #FE642E;" > 소스코드  c++ ( 접기 / 펼치기 )</summary>
  <div>

```cpp
#include <iostream>
#include <algorithm>    //sort
#include <vector>       //vector
#include <cstdlib>      //rand
#include <ctime>        //time

typedef struct edge {
    int src;    //출발 vertex
    int dest;   //도착 vertex
    int weight; //가중치(비용)
} edge;

class Edge {
   private:
    edge e;

   public:
    Edge(int src = 0, int dest = 0, int weight = 0) {
        this->e.src = src;
        this->e.dest = dest;
        this->e.weight = weight;
    }
    int getSrc() { return this->e.src; }
    int getDest() { return this->e.dest; }
    int getWeight() { return this->e.weight; }
    bool operator<(Edge &edge) { return this->e.weight < edge.e.weight; }
};

int Kruskal(std::vector<Edge> &);
int Find(std::vector<int> &, int);
bool Union(std::vector<int> &, std::vector<int> &, int, int);
void randomPush(std::vector<Edge> &);   //graph에 사이클 없는 연결그래프 무작위 생성

int V;

int main() {
    std::vector<Edge> g;    //graph g
    int minimum_weight = 0; //minimum cost

    randomPush(g);  //간선 random 삽입

    /*edge info print*/
    std::cout << "edge info : \n";
    std::for_each(g.begin(), g.end(), [](Edge a) {
        std::cout << "src : " << a.getSrc() << " desc : " << a.getDest() << " weight : " << a.getWeight() << std::endl;
    });

    minimum_weight = Kruskal(g);    //kruskal algorithm

    std::cout << "minimum cost : " << minimum_weight << std::endl;  //minimum cost print

    return 0;
}

int Kruskal(std::vector<Edge> &g) {
    int sum = 0;

    /*set, rank 초기화 == > make_set */
    std::vector<int> set(V);
    std::vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) {
        set[i] = i;
    }

    sort(g.begin(), g.end());  //오름차순으로 정렬

    /*minumum edge 선택*/
    std::cout << "\nselected edge : \n";
    for (int i = 0; i < g.size(); i++) {
        if (Union(set, rank, g[i].getSrc(), g[i].getDest())) {
            std::cout << "edge : " << g[i].getSrc() << " " << g[i].getDest() << " weight : " << g[i].getWeight() << std::endl;
            sum += g[i].getWeight();
        }
    }
    return sum;
}

int Find(std::vector<int> &set, int x) {
    if (set[x] == x)
        return x;
    return set[x] = Find(set, set[x]);
}

bool Union(std::vector<int> &set, std::vector<int> &rank, int x, int y) {
    x = Find(set, x);
    y = Find(set, y);

    if (x == y) return false;

    /*집합에 안속해있다면  union*/
    if (rank[x] < rank[y])
        set[x] = y;

    else if (rank[x] > rank[y])
        set[y] = x;
    else {
        set[y] = x;
        rank[x]++;
    }
    return true;
}

/*vertex수 입력받은 후 그래프 간선 가중치 random 삽입*/
void randomPush(std::vector<Edge> &g) {
    std::cout << "create number of Vertex : ";
    std::cin >> V;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < V - 1; i++) {
        g.push_back(Edge(i, i + 1, rand() % 100));
        for (int j = i + 1; j < V; j += (rand() % 4)) {
            g.push_back(Edge(i, j, rand() % 100));
        }
    }
    for (int i = V - 1; i > 0; i--) {
        g.push_back(Edge(i, i - 1, rand() % 100));
        for (int j = i - 1; j > 0; j -= (rand() % 4)) {
            g.push_back(Edge(i, j, rand() % 100));
        }
    }
}
```

  </div>
</details>

<br><br>
