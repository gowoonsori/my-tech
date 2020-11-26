# Red Black Tree

BST (이진 탐색 트리)를 기반으로 둔 Tree.

`Splaying`이라는 기법이 사용되며, 이는 특정 노드에 대해 접근을 하면, 이를 루트로 위치하도록 재배치 하는 기법의 트리

삽입, 삭제, 탐색의 시간복잡도는 O(log n)

<br>
<br>

## 특징

- 구현이 단순

- 많이 접근한 노드에 대해서 빠른 접근이 가능하다
- 접근 빈도가 불균등하거나 비 랜덤 패턴의 경우 O(lgn)보다 더 유리하다.
- AVL-Tree와 RB-Tree와 달리 추가 데이터 저장 필요 없다.
- 최악의 경우 높이가 선형, 즉 O(n)이 나올 수 있다.
- 세그먼트 트리로 이용이 가능하다. (k번째 원소 찾기, 구간 합, lazy Propagation, 구간 뒤집기 모두 쉽게 할 수 있다.) x노드를 접근한다면, splay를 통해 root로 올라오면서 x보다 작은 노드들은 Left에, 큰 노드들은 Right에 모이는 특성을 이용

<br>

## 사용 예

- 캐시, Garbage Collector 알고리즘

<br>

## 사용 기법

- Splay : rotate를 기본으로, 탐색/삽입/삭제한 노드를 root에 위치할 때 까지 rotate시켜가는 기법

  이도 RB Tree와 마찬가지로 부모 노드가 할아버지 노드의 어느 자식인지에 따라 대칭이다.

  - Zig : 기준 노드 x, z의 부모 노드 y가 root일 때, y를 기준으로 rotate

  - Zig-Zig : x의 할아버지 노드, z가 있을 때, z에 대해 자식 y의 방향과 y에 대해 x의 방향이 같을 때 (z->y 방향 == y->x 방향 )

    - y가 z에 왼쪽 자식일 때 : right-rotate(z) 후 right-rotate(y)

    - y가 z에 오른족 자식일때 : left-rotate(z)후 left-rotate(y)

  - Zig-Zag: x의 할아버지 노드, z가 있을 때, z에 대해 자식 y의 방향과 y에 대해 자식 x의 방향이 다를 때 (z->y 방향 != y->x 방향)

    - y가 z에 왼쪽 자식일 때 : right-rotate(y) 후 left-rotate(y)

    - y가 z에 오른족 자식일때 : left-rotate(y)후 right-rotate(y)

## 구현

### node 구조체

접근할 노드 x에 대해 그 부모, 할아버지 노드에 접근이 가능해야 하므로 따로 트리를 만들던지, 노드 구조체에 부모를 가리킬 포인터를 추가 생성해주면 된다.

### Insert ( 삽입 )

BST 규칙에 맞게 삽입 후 삽입한 노드를 x(기준)으로 `Splay`를 실행하면 된다.

<br>

### Delete ( 삭제 )

삭제할 노드(x)를 `Splay`를 통해 root로 올린 후, x의 successor를 root로 재조정 해주면 된다.

### Search ( 탐색 )

일반 BST와 같이 현재 노드key가 찾고자하는 key보다 작으면 왼쪽, 크면 오른쪽으로 내려가면서 찾고, 찾은 노드에 대해 `Splay`를 수행한다.

[코드 보기(c++)](/dataStructure/Tree/SplayTree.cpp)

<br>

## 시간 복잡도

삽입/탐색 시 가장 작은 숫자나 가장 큰 숫자를 접근한다면, 트리는 O(n)으로 선형적인 트리가 생성이 되지만, 무작위 splay를 통해 구조를 바꿔 줄 수도 있고, 자주 접근 하는 노드는 O(lgn)보다 빠르게 접근이 가능하기 때문에 상각 O(lgn)으로 볼 수 있다.
