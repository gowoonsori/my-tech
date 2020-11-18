### AVL Tree

---

어떤 노드를 기준으로 하더라도 왼쪽자식의 깊이와 오른쪽 자식의 깊이 차이가 1을 넘지 않는 트리

BST (이진 탐색 트리)를 기반으로 둔 Tree.

삽입, 삭제, 탐색의 시간복잡도는 O(log n)

<br>

- **용어 개념 정리**
  - 균형치 (Balance factor) : 자식노드의 깊이 차이 ( 왼쪽 서브트리의 높이 – 오른쪽 서브트리의 높이 )
    <br>BF는 -1, 0, 1로 이루어져 있으며 이 범위를 벗어난다면, 그 트리의 균형은 깨진것다.

<br>

- **특징**

  - `BST`의 모든 특징을 갖는다.

  - 모든 노드를 기준으로 왼쪽자식의 깊이와 오른쪽 자식의 깊이 차이가 1을 넘지 않는다.
  - AVL Tree가 Red Black Tree보다 더 엄격하기 때문에 `더 빠른 조회`가 가능하나 `삽입 / 삭제`가 RB Tree에 비해 `느리다`.
  - `RB Tree`는 Red/Black을 표현할 때 `1 or 0` 1비트만 있어도 되나 `AVL Tree`는 깊이를 저장할 `int`타입의 저장이 필요하다.

<br>

- **사용 예**
  - 더 빠른 검색이 필요한 DB에 사용

<br>

- **구현**

  - Insert ( 삽입 )

  ```
  BST의 일반 삽입 규칙에 맞게 삽입 후, 첫번째로 불균형한 노드를 찾는다.
  이때 불균형한 노드를 z라고 할때, 자식노드가 y, 손자 노드를 x라 한다.

  해당하는 case에 따라 z를 기준으로 부분트리를 회전을 통해 재배열 시켜준다.(rotation , restructuring)

  🔴 case 1. y는 z의 왼쪽 자식, x는 y의 왼쪽 자식 ( left left )

    ➡ z를 기준으로 right-rotate 시켜준다.

  🔴 case 2. y는 z의 왼쪽 자식, x는 y의 오른쪽 자식 ( left right )

    ➡ y를 기준으로 left-rotate 시켜준 후, z를 기준으로 right-rotate 시켜준다.

  🔴 case 3. y는 z의 오른쪽 자식, x는 y의 오른쪽 자식 ( right right )

     ➡ z를 기준으로 left-rotate 시켜준다.

  🔴 case 4. y는 z의 오른쪽 자식, x는 y의 왼쪽 자식 ( right left )

      ➡ y를 기준으로 right-rotate 시켜준 후, z를 기준으로 left-rotate 시켜준다.
  ```

    <br>

  - Delete ( 삭제 )

  ```
  BST의 일반 삽입 규칙에 맞게 삭제 후, 첫번째로 불균형한 노드를 찾는다.
  이때 불균형한 노드를 z라고 할때, z의 자식노드중 깊이가 큰 자식 노드를 y, y의 자식노드중 깊이가 큰 자식 노드를 x라 하자.

  해당하는 case에 따라 z를 기준으로 부분트리를 회전을 통해 재배열 시켜준다.(rotation , restructuring)
  재배열 과정은 삽입과 동일하다.

  🔴 case 1. y는 z의 왼쪽 자식, x는 y의 왼쪽 자식 ( left left )

    ➡ z를 기준으로 right-rotate 시켜준다.

  🔴 case 2. y는 z의 왼쪽 자식, x는 y의 오른쪽 자식 ( left right )

    ➡ y를 기준으로 left-rotate 시켜준 후, z를 기준으로 right-rotate 시켜준다.

  🔴 case 3. y는 z의 오른쪽 자식, x는 y의 오른쪽 자식 ( right right )

     ➡ z를 기준으로 left-rotate 시켜준다.

  🔴 case 4. y는 z의 오른쪽 자식, x는 y의 왼쪽 자식 ( right left )

      ➡ y를 기준으로 right-rotate 시켜준 후, z를 기준으로 left-rotate 시켜준다.
  ```

  <br>

  - Search ( 탐색 )

  ```
  AVL Tree도 BST의 일종이기 때문에 탐색의 밥법은 일반적인 Bianry Tree의 탐색 방법과 다르지 않다.
  ```

  <br>

  [코드 보기(c++)](/dataStructure/Tree/AvlTree.cpp)
