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

int prim_adjMatrix(std::vector<Graph> &, std::vector<std::vector<std::vector<int>>>, int);  // Adj matrix로 구현
void make_adj_matrix(std::vector<Graph>, std::vector<std::vector<std::vector<int>>> &);     //주어진 그래프를 인접행렬로 표현

int V;                                 // vertex 개수
clock_t start, finish, used_time = 0;  //실행 시간 측정을 위한 변수

int main() {
    std::vector<Graph> g;    // graph g
    int minimum_weight = 0;  // minimum cost
    std::vector<std::vector<II>> adjList;
    std::vector<std::vector<std::vector<int>>> adjMatrix;

    randomPush(g);       //간선 random 삽입
    print_edge_info(g);  // edge info print

    make_adj_list(g, adjList);      //주어진 그래프를 인접리스트로 만들기
    make_adj_matrix(g, adjMatrix);  //주어진 그래프를 인접행렬로 만들기

    start = clock();
    // minimum_weight = prim_adjMatrix(g, adjMatrix, 0);  //인접행렬을 이용한 prim's algorithm (0번노드를 첫 노드로 시작)
    minimum_weight = prim_adjList_heap(g, adjList, 0);  //인접리스트를 이용한 prim's algorithm (0번노드를 첫 노드로 시작)
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
        auto u = q.begin();  // extract-min
        q.erase(q.begin());  // queue pop

        sum += u->first;             // cost sum
        selected[u->second] = true;  //해당 vertex 선택
        std::cout << " -> " << u->second << "(cost : " << u->first << ")";

        /*select한 vertex와 인접한 edge 찾아 큐에 push*/
        for (auto e : adjList[u->second]) {
            /* 선택되지 않은 vertex이고 해당 vertex의 key값과 edge의 cost를 비교해 cost가 더 작다면*/
            if (!selected[e.second] && vertex_key[e.second] > e.first) {
                q.erase({vertex_key[e.second], e.second});  //같은 노드로 향하는 간선중 weight가 더 작은 간선이 있다면 그 전 간선은 삭제
                vertex_key[e.second] = e.first;  // vertex key값 갱신
                q.insert({e.first, e.second});   //큐에 삽입
            }
        }
    }

    std::cout << std::endl;
    return sum;
}

void make_adj_list(std::vector<Graph> g, std::vector<std::vector<II>> &adj) {
    adj.resize(V);
    for (int i = 0; i < g.size(); i++) {
        int src = g[i].getSrc();
        int dest = g[i].getDest();
        int weight = g[i].getWeight();

        adj[src].push_back({weight, dest});
        adj[dest].push_back({weight, src});
    }
}

int prim_adjMatrix(std::vector<Graph> &g, std::vector<std::vector<std::vector<int>>> adjMatrix, int start) {
    int sum = 0;
    std::vector<int> vertex_key(V, INFINITY);     // vertex의 최소 weight값 계산
    std::vector<bool> selected(g.size(), false);  //선택된 vertex인가

    vertex_key[start] = 0;  //시작노드 key값 0으로 시작
    std::cout << "\nroute";
    /*vertex 수만큼 반복한다*/
    for (int i = 0; i < V; i++) {
        int v = -1;              //인접 vertex중 가장 작은 가중치를 갖는 vertex
        int min_key = INFINITY;  //인접 vertex중 가장 작은 가중치

        /* 인접 vertex중 가장 작은 가중치를 갖는 vertex 찾기*/
        for (int j = 0; j < V; j++) {
            if (!selected[j] && (min_key > vertex_key[j])) {
                v = j;
                min_key = vertex_key[j];
            }
        }

        /*현재 코드에서는 연결안된 그래프는 주어지지 않기 때문에
          없어도 무방하지만 만약을 위한 에러처리*/
        if (v == -1) {
            std::cout << "Not MST" << std::endl;
            exit(1);
        }

        selected[v] = true;
        sum += min_key;
        std::cout << " -> " << v << "(cost : " << min_key << ")";

        /*인접 vertex의 weight가 vertex_key값보다 작다면 key값 갱신 */
        for (int j = 0; j < V; j++) {
            for (int k = 0; k < adjMatrix[v][j].size(); k++) {
                if (vertex_key[j] > adjMatrix[v][j][k]) {
                    vertex_key[j] = adjMatrix[v][j][k];
                }
            }
        }
    }
    std::cout << std::endl;
    return sum;
}

void make_adj_matrix(std::vector<Graph> g, std::vector<std::vector<std::vector<int>>> &adj) {
    adj.assign(V, std::vector<std::vector<int>>(V, std::vector<int>(0)));
    for (int i = 0; i < g.size(); i++) {
        int src = g[i].getSrc();
        int dest = g[i].getDest();
        int weight = g[i].getWeight();

        adj[src][dest].push_back(weight);
        adj[dest][src].push_back(weight);
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