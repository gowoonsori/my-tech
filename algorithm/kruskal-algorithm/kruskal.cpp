#include <algorithm>  //sort
#include <cstdlib>    //rand
#include <ctime>      //time
#include <iostream>
#include <vector>  //vector

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
    bool operator<(Graph &edge) { return this->e.weight < edge.e.weight; }
};

int Kruskal(std::vector<Graph> &);
int Find(std::vector<int> &, int);
bool Union(std::vector<int> &, std::vector<int> &, int, int);

void randomPush(std::vector<Graph> &);     // graph에 사이클 없는 연결그래프 무작위 생성
void print_edge_info(std::vector<Graph>);  // graph 간선들 보기

int V;  // vertex 개수

int main() {
    std::vector<Graph> g;    // graph g
    int minimum_weight = 0;  // minimum cost

    randomPush(g);  //간선 random 삽입

    /*edge info print*/
    print_edge_info(g);  // edge info print

    minimum_weight = Kruskal(g);  // kruskal algorithm

    std::cout << "minimum cost : " << minimum_weight << std::endl;  // minimum cost print

    return 0;
}

int Kruskal(std::vector<Graph> &g) {
    int sum = 0;

    /*set, rank 초기화 == > make_set */
    std::vector<int> set(g.size());
    std::vector<int> rank(g.size(), 0);
    for (int i = 0; i < g.size(); i++) {
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
    if (set[x] == x) return x;
    return set[x] = Find(set, set[x]);
}

bool Union(std::vector<int> &set, std::vector<int> &rank, int x, int y) {
    x = Find(set, x);
    y = Find(set, y);

    if (x == y) return false;

    /*집합에 안속해있다면 union*/
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
void randomPush(std::vector<Graph> &g) {
    std::cout << "create number of Vertex : ";
    std::cin >> V;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < V - 1; i++) {
        g.push_back(Graph(i, i + 1, rand() % 1000));
        for (int j = i + 1; j < V; j += (rand() % 4)) {
            g.push_back(Graph(i, j, rand() % 1000));
        }
    }
    for (int i = V - 1; i > 0; i--) {
        g.push_back(Graph(i, i - 1, rand() % 1000));
        for (int j = i - 1; j > 0; j -= (rand() % 4)) {
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