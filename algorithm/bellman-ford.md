# Prim's Algorithm

그래프 중에서 `최단 경로`를 찾는 알고리즘중에 하나로 한 노드에서 다른 노드까지의 가중치의 합이 가장 작은 경로를 찾는 알고리즘 중 하나이다.

음의 가중치도 계산 할수 있는 알고리즘이다.

Vertex의 개수가 N개일 때, 한 vertex에서 다른 vertex까지 가는데 거치는 edge수는 최소 1개부터, 최대 N-1번 거치게 될 것이다.

이러한 컨셉을 기준으로 어떤 경로까지 가는데 소요되는 cost를 greedy하게 N-1번 반복하여 구하는 방법이다.

`relax`의 개념을 이용하며 relax는 현재 계산된 v노드까지의 거리보다 현재 노드 u까지의 경로와 u에서 v의 가중치 ( `e(u,v)` ) 가 더 작다면 값을 갱신해주는 것.

`relax`는 prim 알고리즘의 `decrease-key`와 유사하며 dp를 추가한 개념

<br><br>

## 특징

- 음의 가중치를 갖는 경로를 포함해도 구할 수 있다.

- 음의 사이클 존재 여부를 알 수 있다. ( 무한 루프 )

- edge 의 정보로 입력이 주어지면 인접행렬, 인접리스트를 안 만들고도 구할 수 있다.

<br><br>

## Pesudo Code

```
BELLMAN-FORD(G, w , s){
    INITIALIZE-SINGLE-SOURCE(G, s)
    for i = 1 to |G.V| - 1
        for each edge (u,v) ∈ G.E
            RELAX (u,v,w)

    for each edge (u,v) ∈ G.E
        if v.d > u.d + w(u,v)
            return false
    return true
}

```

```
RELAX(u,v,w)
    if v.d > u.d + w(u,v)
        v.d = u.d + w(u,v)
        v.π = u
```

<br><br>

## 구현 방법

<br>

1. vertex들의 key값을 Infinity로 초기화한다.
1. start vertex의 key값을 0으로 초기화한다.
1. 모든 edge에 대해 relax를 수행한다.
1. 3번을 V-1번 반복 한다.
1. 4번이 끝나면 최단 경로는 구해졌으며, 음의 사이클이 있는지 아래의 방법으로 검사한다.
1. 모든 edge에 대해 목적지 vertex의 최단 경로 값이 출발지 vertex까지의 최단 경로 값 + w(u,v) 보다 큰지 검사한다.
1. 만약 크다면 음의 사이클이 존재하고 모든 edge에 대해 아니라면 음의 사이클이 존재하지 않는 그래프이다.

<br>

- 인접 행렬

```cpp
    std::vector<int> vertex_key(V, INFINITY);  // vertex의 최소 weight값 계산
    vertex_key[start] = 0;

    std::cout << "\nsrc : " << start << std::endl;
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < V; j++) {
            for (int k = 0; k < V; k++) {
                if (vertex_key[k] > adjMatrix[j][k] + vertex_key[j]) {
                    vertex_key[k] = adjMatrix[j][k] + vertex_key[j];
                }
            }
        }
    }
    for (int j = 0; j < V; j++) {
        for (int k = 0; k < V; k++) {
            if (vertex_key[k] > adjMatrix[j][k] + vertex_key[j]) {
                std::cout << "음의 사이클을 갖는 그래프입니다." << std::endl;
                exit(1);
            }
        }
    }
    return vertex_key;
```

---

<br>

- 인접 리스트

```cpp
std::vector<int> vertex_key(V, INFINITY);  // vertex의 최소 weight값 계산
    int dest, weight;
    vertex_key[start] = 0;

    std::cout << "\nsrc : " << start << std::endl;
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < adjList.size(); j++) {
            for (int k = 0; k < adjList[j].size(); k++) {
                dest = adjList[j][k].second;
                weight = adjList[j][k].first;
                if (vertex_key[dest] > weight + vertex_key[j]) {
                    vertex_key[dest] = weight + vertex_key[j];
                }
            }
        }
    }

    for (int j = 0; j < adjList.size(); j++) {
        for (int k = 0; k < adjList[j].size(); k++) {
            dest = adjList[j][k].second;
            weight = adjList[j][k].first;
            if (vertex_key[dest] > weight + vertex_key[j]) {
                std::cout << "음의 사이클을 갖는 그래프입니다." << std::endl;
                exit(1);
            }
        }
    }

    return vertex_key;
```

<br>

- edge 정보로 주어졌을 경우

```cpp
    std::vector<int> vertex_key(V, INFINITY);  // vertex의 최소 weight값 계산
    int src, dest, weight;
    vertex_key[start] = 0;

    std::cout << "\nsrc : " << start << std::endl;
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < g.size(); j++) {
            src = g[j].getSrc();
            dest = g[j].getDest();
            weight = g[j].getWeight();
            if (vertex_key[dest] > weight + vertex_key[src]) {
                vertex_key[dest] = weight + vertex_key[src];
            }
        }
    }
    for (int j = 0; j < g.size(); j++) {
        src = g[j].getSrc();
        dest = g[j].getDest();
        weight = g[j].getWeight();
        if (vertex_key[dest] > weight + vertex_key[src]) {
            std::cout << "음의 사이클을 갖는 그래프입니다." << std::endl;
            exit(1);
        }
    }
    return vertex_key;
```

---

<br><br>

## 시간 복잡도

초기화하는데 O(\|V\|) 이 소요되고, 최단 경로를 구하는데 O(\|E\|)번의 relax가 \|V-1\|번 반복하기 때문에, O(\|V\|\|E\|)만큼의 시간이 소요된다.
<br>_(relax는 비교후 단순 대입이므로 O(1)의 시간 소요)_

음의 사이클이 존재하는 지 검사하는데 \|E\번 반복하기 때문에, O(\|E\|)만큼의 시간이 소요된다.

따라서 총 O(\|V\|\|E\|)의 시간복잡도를 갖는다.

<br>

<br><br>

## 구현 코드

<br>

아래 코드는 사이클이없는 방향의 그래프이고, 양의 가중치를 무작위로 생성한 그래프이다.

<details>
    <summary style="font-Weight : bold; font-size : 15px; color : #FE642E;" > 소스코드  c++ ( 접기 / 펼치기 )</summary>
    <div>

```cpp

```

</div>

</details>
