# Red Black Tree

BST (이진 탐색 트리)를 기반으로 둔 Tree.

각 노드는 값(key)말고도 색을 갖고 색은 레드 or 블랙 2종류다.

삽입, 삭제, 탐색의 시간복잡도는 O(log n)

<br>

## RB Tree 4가지 조건

```
1. Root Property : 루트(root)노드는 블랙(black)이다.
2. External Property : 모든 외부 노드 (external node)는 블랙이다.
3. Depth Property : 모든 단말 노드(leaf node)의 경우 루트부터 외부 노드 까지 방문하는 블랙 노드의 수가 같다.
4. Internal Property : 빨강 노드의 자식은 블랙이다.
    == No Double Red :레드 노드는 두개가 연속해서 올 수 없다.
```

<br>

## 특징

- `BST`의 모든 특징을 갖는다.

- 노드의 자식이 없는 경우 자식을 가리키는 포인터는 NULL값을 저장 ( NULL을 `leaf node`로 간주)
- 루트 노드 부터 단말 노드(leaf node)까지 모든 경로 중 최소 경로와 최대 경로의 크기 비율은 2보다 크지 않다. ( `balanced` 상태 )

<br>

## 사용예

- Java Collection의 ArrayList

- HashMap의 Separate Chaining
- C++ map

<br>

## 장점 (해쉬와 비교해서)

- 순서가 있는 자료일 경우 좋다. ( 해쉬는 순서가 없음 )

- 일관성있는 퍼포먼스를 보여준다. ( 해쉬는 rehashing시 비정상적 시간이 걸릴 수 있음 )
- 해쉬는 페이지폴트를 일으킬 수 있다.
- 연속된 삽입간의 공간 지역성을 유지하기 쉽다. ( 더 적은 I/O 발생)
- 트리는 부정확한 검색에 사용될 수 있다.

<br>

## 구현

- Insert ( 삽입 )

```
BST 특징대로 삽입 후, 삽입 노드의 색깔을 RED로 설정.
삽입 후 RBT의 특징을 위배할 시 노드의 색깔을 조정하고,
Black-Height가 위배되었다면, rotation을 통하여 height을 조정.

이때, 여러 case가 존재하는 데, 새로 삽입한 노드를 z라고 할때,
부모 노드인 p[z]가 부모 노드의 부모 노드인 할아버지 노드 p[p[z]]의 왼쪽 자식인지 오른쪽 자식인지에 따라 case가 나뉘게 된다.
두개의 경우가 서로 대칭이다.

 red-black tree규칙이 위배될때 크게 보면 아래와 같이 2가지의 경우가 존재한다.

🔴 case 1 : z 삼촌이 레드  ➡ 색상 변환 ( Recoloring )

    - z의 부모와 z의 삼촌 노드를 레드에서 블랙으로 바꾸고, z의 할아버지 노드를 블랙에서 레드로 바꾼다.
    - z의 할아버지 노드의 부모노드가 레드인 경우 이 경우를 반복 한다.
    - z의 부모가 블랙을 만날때 종료 되며, 루트까지 올라가게 되면 루트노드를 블랙으로 바꾸고 종료한다. (루트노드까지 올라가게 되면 black-height는 1 증가하게 된다.)


 🔴 case 2 : z의 삼촌이 없거나 블랙 ➡ 회전 ( rotation , restructuring)

  🔸 부모노드 (p[z])가 할아버지 노드 (p[p[z]]) 의 왼쪽 자식일때
    ◾ case 2-1 : z가 p[z]의 오른쪽 자식
      - p[z]를 중심으로 왼쪽으로 회전 시키고, 여전히 레드 블랙트리 특성을 위반하므로 case 2-2를 수행한다.

    ◾ case 2-2 : z가 p[z]의 왼쪽 자식
      - p[p[z]]를 중심으로 오른쪽 회전 시키고, p[z]와 p[p[z]]의 색상을 바꾼다.
      (부모노드는 블랙으로, 할아버지 노드는 레드로)

  🔸 부모노드 (p[z])가 할아버지 노드 (p[p[z]]) 의 오른쪽 자식일때
    ◾ case 2-1 : z가 p[z]의 왼쪽 자식
      - p[z]를 중심으로 오른쪽으로 회전 시키고, 여전히 레드 블랙트리 특성을 위반하므로 case 2-2를 수행한다.

    ◾ case 2-2 : z가 p[z]의 오른쪽 자식
      - p[p[z]]를 중심으로 왼쪽 회전 시키고, p[z]와 p[p[z]]의 색상을 바꾼다.
      (부모노드는 블랙으로, 할아버지 노드는 레드로)

z를 할아버지 노드 ( p[p[z]] )로 바꿔주고 할아버지의 부모가 Red가 아닐때까지 위의 case를 반복해준다.
```

    <br>

- Delete ( 삭제 )

```
BST의 특성을 유지하면서 삭제한 후, 삭제할 노드의 자식노드 개수에 따라 rotation 방법이 달라진다.
또한, 지워진 노드의 색깔이 Black이라면, Black-Height가 1감소한 경로에 black node가 1개 추가되도록 rotaion한다.

NULL node(leaf node) 역시 black 이다.


🔴 case default : 삭제할 노드를 z라 할때, z가 RED라면 그냥 삭제하고, (z의 자식이 두개인 경우는 오른쪽 자식의 가장 작은 key와 key값을 교환 후 z->right의 minimum 노드를 삭제하게 되므로 이 노드의 색이 RED라면)
BLACK이라면,  black-height가 안맞게 되므로 fix up을 수행한다. (이때, double-black개념이 등장한다.)

삭제도 삽입과 마찬가지로 삭제한 노드 z대신 위치할 노드 x가 p[x]의 왼쪽 자식인지 오른쪽 자식인지에 대해 대칭한다.

삭제한 노드 z대신 새로 위치한 노드를 x, 그 형제 노드를 s라고 할때,


🔴 case 1 : s가 RED인 경우

  이때는 s의 자식들은 leafNode 일 수 없다.(조건 5 위반) => 한개라도 leafnode일 시 black-heigh가 달라지므로 무조건 두개를 가지고 있다.

  🔸 x가 부모노드 p[x]의 왼쪽 자식일때
    - s를 BLACK으로 p[x]를 RED로 바꿔준다.
    - p[x]를 left-Rotate 시켜준다.
    - x의 새로운 형제노드를 달아준다. (s = p[x]->right) ==> x의 새로운 형제노드는 원래 s의 왼쪽 자식노드 (left-Rotate시켜주었기 때문)

  🔸 x가 부모노드 p[x]의 오른쪽 자식일때
    - s를 BLACK으로 p[x]를 RED로 바꿔준다.
    - p[x]를 right-Rotate 시켜준다.
    - x의 새로운 형제노드를 달아준다. (s = p[x]->left) ==> x의 새로운 형제노드는 원래 s의 왼쪽 자식노드 (left-Rotate시켜주었기 때문)

  아직 double-black이 남았기 때문에 case 2/3/4를 진행한다.


🔴 case 2 :s가 BLACK, s의 자식들도 BLACK일때
    - x의 double-blackd을 지우고 s를 RED로 바꾼다.
    - p[x]를 x로 해서 계속 한다.
    - 만약, case 1을 거치고 case 2로 왔다면, p[x]는 red였기때문에 종료된다. ( => s의 자식들이 모두 black인 채로 있기 때문에 black-height는 유지)


🔴 case 3 : s는 BLACK, s의 왼쪽 자식이 RED, 오른쪽 자식이 BLACK 인 경우

  🔸 x가 부모노드 p[x]의 왼쪽 자식일때
    - s를 RED, s의 왼쪽 자식을 BLACK으로 바꿔준다.
    - s를 중심으로 right-Rotate 시켜준다.
    - x의 새로운 형제노드를 달아준다. ( s = p[x]->right)

  🔸 x가 부모노드 p[x]의 오른쪽 자식일때
    - s를 RED, s의 왼쪽 자식을 BLACK으로 바꿔준다.
    - s를 중심으로 left-Rotate 시켜준다.
    - x의 새로운 형제노드를 달아준다. ( s = p[x]->left)

  case 3의 경우는 위의 과정을 끝내고 case 4를 이어서 수행한다.


🔴 case 4 : s는 BLACK, s의 오른쪽 자식이 RED인 경우

  🔸 x가 부모노드 p[x]의 왼쪽 자식일때
    - s의 색을 p[x]의 색으로 바꿔준다.
    - p[x]의 색을 BLACK, s의 오른쪽 자식을 BLACK으로 바꿔준다.
    - p[x]에 대해서 left-rotate를 시켜준다.
    - x의 double-black을 제거하고 종료한다.

  🔸 x가 부모노드 p[x]의 오른쪽 자식일때
    - s의 색을 p[x]의 색으로 바꿔준다.
    - p[x]의 색을 BLACK, s의 왼쪽 자식을 BLACK으로 바꿔준다.
    - p[x]에 대해서 right-rotate를 시켜준다.
    - x의 double-black을 제거하고 종료한다.

x가 root이거나 double black이 깨질때까지 반복해준 후, x를 black으로 바꿔준다.
```

   <br>

- Search ( 탐색 )

```
Red Black Tree는 BST의 일종이기 때문에 탐색의 밥법은 일반적인 Bianry Tree의 탐색 방법과 다르지 않다.
```

[코드 보기(c++)](https://gist.github.com/gowoonsori/81cbae744163b40597476fc346d476a5)

<br>

## 시간 복잡도

일반 BST의 skewd한 경우를 balancing기법을 통해 balanced한 tree를 만들었으므로 탐색과정은 원하는 대로 O(lgn)이 나온다.
삽입은 일반 BST에서 최대 2번의 rotate과정과 색 변환이 추가 되었는 데, rotate과정은 포인터변수를 교환해주는 것이므로 O(1)의 시간 복잡도와 색변환도 단순한 변수값 변경이므로 O(1)의 색 변환이 O(lgn)번 일어나기 때문에, O(lgn)을 갖는다.
삭제도 삽입과 동일한 이유이며, rotate과정은 최대 3번이 O(lgn)번 일어나기 때문에 O(lgn)이 나온다.
