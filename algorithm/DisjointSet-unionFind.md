# Disjoint Set

번역하면 `서로소 집합`으로 서로 중복 되지 않는 부분 집합들로 이루어진 집합(set).

한마디로 교집합이 존재 하지 않는 부분집합들로 이루어진 집합.

<br>

# Union-Find

`Union` : 두개의 집합을 하나의 집합으로 합치는 것.

`Find` : 어떤 원소가 주어졌을 때 이 원소가 속한 집합을 반환하는(찾는) 것.

집합들을 `tree`구조로 나타내어 해당원소가 어떤 집합에 속하는지 판단할때 각 집합의 대표값(root)을 이용해서 집합이 같은지를 비교.

<br>

## 구현 방법

- 연결리스트

```cpp
typedef struct node{
    int data;
    struct node* parent;
    struct node* next;
}node;

void MakeSet(node* p,int x){
     p->data = x;
     p->parent = p;//처음은 다 원소가 하나씩있는 집합이므로 자기 자신이 root
     p->next=null;
}

void Find(node* p,int x){
    if(p->parent->data == x) return x;  //root값이 자기 자신이라면 집합의 대표값
    else return Find(p->parent,x);  //재귀적으로 집합 대표값 찾기
}

void Union(node* p1,node* p2,int x,int y){
    x = Find(p1,x);
    y = Find(p2,y);
    p1->next = p2;
    p2->parent = p1;
}
```

<br>

- Disjoint Set Forest ( Tree )

```cpp
int root[n];

void MakeSet(int x){
     root[x] = x;    //처음은 다 원소가 하나씩있는 집합이므로 자기 자신이 root
}

void Find(int x){
    if(root[x] == x) return x;  //root값이 자기 자신이라면 집합의 대표값
    else return Find(root[x]);  //재귀적으로 집합 대표값 찾기
}

void Union(int x,int y){
    x = Find(x);
    y = Find(y);
    root[y] = x;
}
```

<br>

## 시간 복잡도

`연결리스트`로 구현시` O(nlgn)`의 시간을 갖으며 `Tree`로 구현해도 불균형한 트리 (예 : skewd tree)와 같게 되면 연결리스트와 다를 것이 없어진다.

<br>

## 문제점

find시에 재귀적으로 찾기 때문에 만약에 set의 tree구조가 선형적인 형태라고 한다면 최악의 경우로 O(n)만큼의 시간이 소요 되게 된다.

➡ `path compression (경로 압축)`기법 사용

<br>

또한, union시에 깊이가 작은 트리에 깊이가 깊은 트리를 붙이게 되면 깊이가 더 증가하여 시간에 악영향을 준다.

➡ `union by rank` 기법 사용

<br><br>

## path compression (경로 압축)

find 연산 수행시마다 트리의 구조를 평평하게 만드는 방법.

각 root값을 재귀적으로 가리키는 것이 아닌 해당 집합의 속하는 원소는 `모두 동일한 root`를 가리키게 만드는 방법

```cpp
void Find(int x){
    /*find수행마다 해당 parent값을 root로 초기화*/
    if(root[x] != x) root[x] = Find(root[x]);
    else return root[x];
}
```

<br>

## union by rank

항상 깊이가 깊은 트리에 작은 트리를 붙여 깊이를 유지하는 방법.

깊이가 서로 같은 트리라면, 깊이를 1증가 시킨다.

```cpp
int root[n];
int rank[n];

void MakeSet(int x){
    root[x] = x;    //처음은 다 원소가 하나씩있는 집합이므로 자기 자신이 root
    rank[x] = 0;    //깊이도 0으로 초기화
}

void Union(int x,int y){
    x = Find(x);    //입력받은 x값의 root값을 저장
    y = Find(y);    //입력받은 y값의 root값을 저장

    if(x==y)  return; //root가 같다면 같은 집합

    if(rank[x] < rank[y])  root[x] = y; //x의 root를 y로 변경
    else if(rank[x] > rank[y]) root[y]= x; //y의 root를 x로 변경
    else{
        root[y] = x;
        rank[x]++;  //깊이가 같다면 x에 y를 붙였으므로 x깊이 증가
    }

```

<br>

## 두 기법을 적용 후 시간 복잡도

`O(lgn)`

<br>

## 활용

`Disjoint Set 자료구조`는 집합의 분할을 모델링 하기 때문에 `무방향 그래프(undirected graph)` 의 `연결된 요소들을 추적` 할 수 있어, 사이클이 발생하는지 / 같은 요소에 속하는지 확인 할 수 있다.

대표적으로 `MST`를 찾는 `Kruskal 알고리즘`에 이용된다.
