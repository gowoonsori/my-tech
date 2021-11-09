#include <time.h>  //시간 측정

#include <algorithm>  //for_each
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define INFINITY 2140000000
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
void make_adj_list(std::vector<Graph>, std::vector<std::vector<II>> &);     //주어진 그래프를 인접리스트로 표현
void make_adj_matrix(std::vector<Graph>, std::vector<std::vector<int>> &);  //주어진 그래프를 인접행려로 표현

std::vector<int> dijkstra_heap(std::vector<std::vector<II>>, int);
std::vector<int> dijkstra_array(std::vector<std::vector<int>>, int);

int V;                                 // vertex 개수
clock_t start, finish, used_time = 0;  //실행 시간 측정을 위한 변수

int main() {
    std::vector<Graph> g;  // graph g
    std::vector<int> shortestPath;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<II>> adjList;

    randomPush(g);       //간선 random 삽입
    print_edge_info(g);  // edge info print

    make_adj_matrix(g, adjMatrix);  //주어진 그래프를 인접행렬로 만들기
    make_adj_list(g, adjList);      //주어진 그래프를 인접리스트로 만들기

    start = clock();
    // shortestPath = dijkstra_heap(adjList, 0);  // binary heap을 이용한 구현
    shortestPath = dijkstra_array(adjMatrix, 0);  // array 이용한 구현
    finish = clock();

    for (int i = 0; i < V; i++) {
        std::cout << "dest : " << i << " (cost : " << ((shortestPath[i] == INFINITY) ? "no path" : std::to_string(shortestPath[i])) << " )"
                  << std::endl;
    }
    CalcTime();
    return 0;
}

std::vector<int> dijkstra_heap(std::vector<std::vector<II>> adjList, int start) {
    std::set<II> q;                            //이진힙으로 queue 만들기 ( set은 red-black tree로 만들어짐 )
    std::vector<int> vertex_key(V, INFINITY);  // vertex의 최소 weight값 계산
    std::vector<bool> selected(V, false);      //선택된 vertex인가

    vertex_key[start] = 0;
    q.insert(II(0, start));  //시작 노드 가중치 0으로 시작
    std::cout << "\nstart : " << start << std::endl;

    /*Vertex만큼 반복*/
    while (!q.empty()) {
        /*extract min*/
        int select_key = q.begin()->second;
        int min_of_key = q.begin()->first;
        q.erase(q.begin());

        selected[select_key] = true;

        /*decrease key*/
        for (auto e : adjList[select_key]) {
            if (!selected[e.second] && vertex_key[e.second] > e.first + vertex_key[select_key]) {
                q.erase({vertex_key[e.second], e.second});  //같은 노드로 향하는 간선중 weight가 더 작은 간선이 있다면 그 전 간선은 삭제
                q.insert({e.first, e.second});  //큐에 삽입
                vertex_key[e.second] = e.first + vertex_key[select_key];
            }
        }
    }
    return vertex_key;
}

std::vector<int> dijkstra_array(std::vector<std::vector<int>> adjMatrix, int start) {
    std::vector<int> vertex_key(V, INFINITY);  // vertex의 최소 weight값 계산
    std::vector<bool> selected(V, false);      //선택된 vertex인가

    vertex_key[start] = 0;
    std::cout << "\nstart : " << start << std::endl;

    /*Vertex만큼 반복*/
    for (int i = 0; i < V; i++) {
        /*extract min*/
        int select_idx = -1, min_of_key = INFINITY;
        for (int j = 0; j < V; j++) {
            if (!selected[j] && min_of_key > vertex_key[j]) {
                select_idx = j;
                min_of_key = vertex_key[j];
            }
        }

        selected[select_idx] = true;

        /*decrease key*/
        for (int j = 0; j < V; j++) {
            if (!selected[j] && vertex_key[j] > adjMatrix[select_idx][j] + vertex_key[select_idx]) {
                vertex_key[j] = adjMatrix[select_idx][j] + vertex_key[select_idx];
            }
        }
    }
    return vertex_key;
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
    }
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
        std::cout << "src : " << a.getSrc() << " desc : " << a.getDest() << " weight : " << a.getWeight() << std::endl;
    });
}

//실행 시간을 측정 및 출력하는 함수
void CalcTime() {
    used_time = finish - start;
    printf("\n*********** result **********\n     time : %lf sec\n", (double)(used_time) / CLOCKS_PER_SEC);
}
