
# 트리
```
그래프의 일종으로, 여러 노드가 한개의 노드를 가리킬 수 없는 구조

선형구조가 아닌 (비선형), 부모자식의 관계를 가지는 계층형 구조
```
<br>

## 개념
- `Node (노드)` : 트리를 구성하고 있는 각각의 요소를 의미한다.

- `Edge (간선)` : 트리를 구성하기 위해 노드와 노드를 연결하는 선을 의미한다.
- `Root Node (루트 노드)` : 트리 구조에서 최상위에 있는 노드를 의미한다.
- `Terminal Node` ( = `leaf Node`, 단말 노드) : 하위에 다른 노드가 연결되어 있지 않은 노드를 의미한다.
- `Internal Node` (내부노드, 비단말 노드) : 단말 노드를 제외한 모든 노드로 루트 노드를 포함한다.

<br>

## 종류
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
```
- 전위 순회 : root를 제일 먼저 순회
- 중위 순회 : root를 중간에 순회
- 후위 순회 : root를 제일 나중에 순회
```

<br>

## 이진 탐색 트리 ( Binary Search Tree )
------
```
key값은 중복되지 않으며, 부모의 키가 왼쪽 자식보다는 크며, 오른쪽 자식 보다는 작다.

왼쪽과 오른쪽 서브트리도 이진 탐색 트리이다.
```
탐색 연산은 O(logn)을 갖으며 (엄밀히 말하면 O(h), h는 높이 ), 한쪽으로 치우쳐진 `편향 트리(Skewed Tree)`가 되면 **worst case**로 `O(n)`을 갖는다.

배열보다 많은 메모리를 사용했지만 시간복잡도가 같게되는 비효율적이 상황이 발생하기도 한다. 

[코드 보기 (c++)](/dataStructure/Tree/BinarySearchTree.cpp)
<br>

➡ **Rebalancing 기법의 등장**

<br><br>

-**Rebalancing 기법 종류**

### ✔ Red Black Tree
-----

```
BST (이진 탐색 트리)를 기반으로 둔 Tree.
각 노드는 값(key)말고도 색을 갖고 색은 레드 or 블랙 2종류다.

삽입, 삭제, 탐색의 시간복잡도는 O(log n)

1. Root Property : 루트(root)노드는 블랙(black)이다.
2. External Property : 모든 외부 노드 (external node)는 블랙이다.
3. Depth Property : 모든 단말 노드(leaf node)의 경우 루트부터 외부 노드 까지 방문하는 블랙 노드의 수가 같다.
4. Internal Property : 빨강 노드의 자식은 블랙이다. 
    == No Double Red :레드 노드는 두개가 연속해서 올 수 없다.
```
<br>

- 특징
    - `BST`의 모든 특징을 갖는다.
    - 노드의 자식이 없는 경우 자식을 가리키는 포인터는 NULL값을 저장 ( NULL을 `leaf node`로 간주)
    - 루트 노드 부터 단말 노드(leaf node)까지 모든 경로 중 최소 경로와 최대 경로의 크기 비율은 2보다 크지 않다. ( `balanced` 상태 )

<br>

- 사용 예
    - Java Collection의 ArrayList
    - HashMap의 Separate Chaining
    - C++ map

<br>

- 장점 (해쉬와 비교해서)
    - 순서가 있는 자료일 경우 좋다. ( 해쉬는 순서가 없음 )
    - 일관성있는 퍼포먼스를 보여준다. ( 해쉬는 rehashing시 비정상적 시간이 걸릴 수 있음 )
    - 해쉬는 페이지폴트를 일으킬 수 있다.
    - 연속된 삽입간의 공간 지역성을 유지하기 쉽다. ( 더 적은 I/O 발생)
    - 트리는 부정확한 검색에 사용될 수 있다.


<br>

- 구현
    - 삽입
    ```
    BST 특징대로 삽입 후, 삽입 노드의 색깔을 RED로 설정.
    삽입 후 RBT의 특징을 위배할 시 노드의 색깔을 조정하고,
    Black-Height가 위배되었다면, rotation을 통하여 height을 조정.

    이때, 여러 case가 존재하는 데, 새로 삽입한 노드를 z라고 할때, 부모 노드인 p[z]가 부모 노드의 부모 노드인 할아버지 노드 p[p[z]]가 왼쪽 자식인지 오른쪽 자식인지에 따라 case가 나뉘는 데 서로 대칭이므로 왼쪽일 때만 살펴 보겠습니다.

    🔴 case 1 : z 삼촌이 레드  ➡ 색상 변환 ( Recoloring )

        - z의 부모와 z의 삼촌 노드를 레드에서 블랙으로 바꾸고, z의 할아버지 노드를 블랙에서 레드로 바꾼다.
        - z의 할아버지 노드의 부모노드가 레드인 경우 이 경우를 반복 한다.
        - z의 부모가 블랙을 만날때 종료 되며, 루트까지 올라가게 되면 루트노드를 블랙으로 바꾸고 종료한다. (루트노드까지 올라가게 되면 black-height는 1 증가하게 된다.)

     🔴 case 2 : z의 삼촌이 없거나 블랙 ➡ 회전 ( rotation , restructuring)
        
        - case 2-1 : z가 p[z]의 오른쪽 자식
            -> p[z]를 중심으로 왼쪽으로 회전 시키고, 여전히 레드 블랙트리 특성을 위반하므로 case 2-2를 수행한다.
        - case 2-2 : z가 p[z]의 왼쪽 자식
            -> p[p[z]]를 중심으로 오른쪽 회전 시키고, p[z]와 p[p[z]]의 색상을 바꾼다.
    ```

    <br>

    - 삭제
    ```
    BST의 특성을 유지하면서 삭제한 후, 삭제할 노드의 자식노드 개수에 따라 rotation 방법이 달라진다.
    또한, 지워진 노드의 색깔이 Black이라면, Black-Height가 1감소한 경로에 black node가 1개 추가되도록 rotaion한다.

    NULL node(leaf node) 역시 black 이다.

    
    🔴 case default : 삭제할 노드를 z라 할때, z가 RED라면 그냥 삭제하고,
    검은색인 경우, 그 자리를 대체하는 노드를 검은색으로 바꿔준다.
    but, 검은색으로 새로 칠한 노드의 색이 원래 검은색이라면 이중 흑색노드가 되므로 별도로 처리해주어야한다.

    삭제도 삽입과 마찬가지로 삭제한 노드 대신에 새로온 노드가 왼쪽 자식인지, 오른쪽 자식인지에 대해 대칭한다. 이번에도, 왼쪽의 경우만 살펴보겠다.


    삭제한 노드 z대신 새로 위치한 노드를 x, 그 형제 노드를 s라고 할때,
    🔴 case 1 : s가 RED인 경우 ➡ 
        이때는 s의 자식들은 leafNode 일 수 없다.(조건 5 위반)

        - s를 BLACK으로 p[x]를 RED로 바꿔준다.
        - p[x]를 left-Rotate 시켜준다.
        - x의 새로운 형제노드를 달아준다. (s = p[x]->right) ==> x의 새로운 형제노드는 원래 s의 왼쪽 자식노드 (left-Rotate시켜주었기 때문) 

        아직 double-black이 남았기 때문에 case 2/3/4를 진행한다.

    🔴 case 2 :s가 BLACK, s의 자식들도 BLACK일때 ➡
        - x의 double-blackd을 지우고 s를 RED로 바꾼다.
        - p[x]를 x로 해서 계속 한다.
        - 만약, case 1을 거치고 case 2로 왔다면, p[x]는 red였기때문에 종료된다. ( => s의 자식들이 모두 black인 채로 있기 때문에 black-height는 유지)

    🔴 case 3 : s는 BLACK, s의 왼쪽 자식이 RED, 오른쪽 자식이 BLACK 인 경우 ➡
        - s를 RED, s의 왼쪽 자식을 BLACK으로 바꿔준다.
        - s를 중심으로 right-Rotate 시켜준다.
        - x의 새로운 형제노드를 달아준다. ( s = p[x]->right)

        case 3의 경우는 위의 과정을 끝내고 case 4를 이어서 수행한다.

    🔴 case 4 : s는 BLACK, s의 오른쪽 자식이 RED인 경우 ➡
        - s의 색을 p[x]의 색으로 바꿔준다.
        - p[x]의 색을 BLACK, s의 오른쪽 자식을 BLACK으로 바꿔준다.
        - p[x]에 대해서 left-rotate를 시켜준다.
        - x의 double-black을 제거하고 종료한다.
    ```
    [코드 보기(c++)]([코드 보기 (c++)](/dataStructure/Tree/RedBlackTree.cpp))