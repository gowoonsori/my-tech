
# 트리
------
그래프의 일종으로, 여러 노드가 한개의 노드를 가리킬 수 없는 구조<br>
위의 자료구조와 다르게 선형구조가 아닌, 부모자식의 관계를 가지는 계층형 구조<br>

## 종류
```
- Binary tree  : 부모 노드가 자식 노드를 최대 2개씩만 갖는 트리
- Ternary tree : 자식 노드를 2개 이상 갖고 있는 트리
```
#### :heavy_check_mark: 완전 이진 트리 (Complete binary tree)
마지막 레벨을 제외한 모든 서브트리의 레벨이 같아야 하고, 마지막 레벨은 왼쪽부터 채워져 있어야 한다.

#### :heavy_check_mark: 정 이진 트리 (Full binary tree)
자식 노드가 없거나 2개인 트리

#### :heavy_check_mark: 포화 이진 트리 (Perfect binary tree)
빈 공간이 없이 모든 노드가 2개의 자식을 갖고 있는 트리

#### :heavy_check_mark: 이진 탐색 트리 (Binary search tree)
부모노드 보다 작은 값의 노드는 왼쪽 child, 큰 값의 노드는 오른쪽 child로 구성되어 있는 tree<br>
key값의 중복이 허용되지 않는다.
<br>

## Binary Tree 순회 방법
```
- 전위 순회 : root를 제일 먼저 순회
- 중위 순회 : root를 중간에 순회
- 후위 순회 : root를 제일 나중에 순회
```
