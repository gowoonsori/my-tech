#include <time.h>  //시간 측정

#include <algorithm>  //for_each
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
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

std::vector<int> bellman_ford_list(std::vector<std::vector<II>>, int);
std::vector<int> bellman_ford_array(std::vector<std::vector<int>>, int);
std::vector<int> bellman_ford_edge(std::vector<Graph>, int);

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
    // shortestPath = bellman_ford_list(adjList, 0);  // list을 이용한 구현
    // shortestPath = bellman_ford_array(adjMatrix, 0);  // array 이용한 구현
    shortestPath = bellman_ford_edge(g, 0);  // array 이용한 구현
    finish = clock();

    for (int i = 0; i < V; i++) {
        std::cout << "dest : " << i << " (cost : " << ((shortestPath[i] == INFINITY) ? "no path" : std::to_string(shortestPath[i])) << " )"
                  << std::endl;
    }
    CalcTime();
    return 0;
}

std::vector<int> bellman_ford_list(std::vector<std::vector<II>> adjList, int start) {
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
}

std::vector<int> bellman_ford_array(std::vector<std::vector<int>> adjMatrix, int start) {
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
}

std::vector<int> bellman_ford_edge(std::vector<Graph> g, int start) {
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
