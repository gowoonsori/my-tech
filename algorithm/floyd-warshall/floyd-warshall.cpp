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
