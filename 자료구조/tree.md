# 트리 ( Tree )

```
그래프의 일종으로, 여러 노드가 한개의 노드를 가리킬 수 없는 구조

선형구조가 아닌 (비선형), 부모자식의 관계를 가지는 계층형 구조
```

<br>

## 개념

---

- `Node (노드)` : 트리를 구성하고 있는 각각의 요소를 의미한다.

- `Edge (간선)` : 트리를 구성하기 위해 노드와 노드를 연결하는 선을 의미한다.
- `Root Node (루트 노드)` : 트리 구조에서 최상위에 있는 노드를 의미한다.
- `Terminal Node` ( = `leaf Node`, 단말 노드) : 하위에 다른 노드가 연결되어 있지 않은 노드를 의미한다.
- `Internal Node` (내부노드, 비단말 노드) : 단말 노드를 제외한 모든 노드로 루트 노드를 포함한다.

<br>

## 종류

---

```
- Binary tree  : 부모 노드가 자식 노드를 최대 2개씩만 갖는 트리

- Ternary tree : 자식 노드를 2개 이상 갖고 있는 트리
```

<br>

### ✔ 완전 이진 트리 (Complete binary tree)

마지막 레벨을 제외한 **모든 서브트리의 레벨이 같아야** 하고, 마지막 레벨은 `왼쪽`부터 채워져 있어야 한다.

<Br>

### ✔ 정 이진 트리 (Full binary tree)

자식 노드가 **없거나** **2개**인 트리

<Br>

### ✔ 포화 이진 트리 (Perfect binary tree)

빈 공간이 없이 `모든 노드`가 **2개**의 자식을 갖고 있는 트리

<Br>

### ✔ 이진 탐색 트리 (Binary search tree)

부모노드 보다 작은 값의 노드는 왼쪽 child, 큰 값의 노드는 오른쪽 child로 구성되어 있는 tree.

key값의 `중복`이 **허용되지 않는다.**

<br>

## Binary Tree 순회 방법

---

```
- 전위 순회 : root를 제일 먼저 순회
- 중위 순회 : root를 중간에 순회
- 후위 순회 : root를 제일 나중에 순회
```

<br>

## 이진 탐색 트리 ( Binary Search Tree )

---

```
key값은 중복되지 않으며, 부모의 키가 왼쪽 자식보다는 크며, 오른쪽 자식 보다는 작다.

왼쪽과 오른쪽 서브트리도 이진 탐색 트리이다.
```

탐색 연산은 O(logn)을 갖으며 (엄밀히 말하면 O(h), h는 높이 ), 한쪽으로 치우쳐진 `편향 트리(Skewed Tree)`가 되면 **worst case**로 `O(n)`을 갖는다.

[코드 보기 (c++)](https://gist.github.com/gowoonsori/cb2e95f1e2ede219694ad082cef34cd1)

<br>

## Binary Search Tree의 단점

---

배열보다 많은 메모리를 사용했지만 시간복잡도가 같게되는 비효율적이 상황이 발생하기도 한다.

➡ **Rebalancing 기법의 등장**

<br><br>

## Balanced Tree

- [AVL Tree](/dataStructrue/AvlTree.md)
- [Red Black Tree](/dataStructrue/redBlackTree.md)
- [Splay Tree](/dataStructrue/SplayTree.md)
- [AA Tree](/dataStructrue/aaTree.md)
