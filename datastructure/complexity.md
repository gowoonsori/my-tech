# ◼ 자료구조 시간/공간 복잡도

<br>
<br>

|               자료구조               |               |               |                  |                 | 시간복잡도 (Time Complexity) |               |                  |                 | 공간복잡도 (space Complexity) |
| :----------------------------------: | :-----------: | :-----------: | :--------------: | :-------------: | :--------------------------: | :-----------: | :--------------: | :-------------: | :---------------------------: |
|                                      |    average    |               |                  |                 |            Worst             |               |                  |                 |             Worst             |
|                                      | 접근 (Access) | 탐색 (Search) | 삽입 (Insertion) | 삭제 (Deletion) |        접근 (Access)         | 탐색 (Search) | 삽입 (Insertion) | 삭제 (Deletion) |
|             배열 (Array)             |     Θ(1)      |     Θ(n)      |       Θ(n)       |      Θ(n)       |             O(1)             |     O(n)      |       O(n)       |      O(n)       |             O(n)              |
|             스택 (Stack)             |     Θ(n)      |     Θ(n)      |       Θ(1)       |      Θ(1)       |             O(n)             |     O(n)      |       O(1)       |      O(1)       |             O(n)              |
|              큐 (Queue)              |     Θ(n)      |     Θ(n)      |       Θ(1)       |      Θ(1)       |             O(n)             |     O(n)      |       O(1)       |      O(1)       |             O(n)              |
| 단일 연결리스트 (Single-Linked-List) |     Θ(n)      |     Θ(n)      |       Θ(1)       |      Θ(1)       |             O(n)             |     O(n)      |       O(1)       |      O(1)       |             O(n)              |
| 이중 연결리스트 (Doubly-Linked-List) |     Θ(n)      |     Θ(n)      |       Θ(1)       |      Θ(1)       |             O(n)             |     O(n)      |       O(1)       |      O(1)       |             O(n)              |
|       스킵 리스트 (Skip List)        |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |             O(n)             |     O(n)      |       O(n)       |      O(n)       |           O(nlogn)            |
|       해시 테이블 (Hash Table)       |      N/A      |     Θ(1)      |       Θ(1)       |      Θ(1)       |             N/A              |     O(n)      |       O(n)       |      O(n)       |             O(n)              | O(n) |
|       이진 트리 (Binary Tree)        |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |             O(n)             |     O(n)      |       O(n)       |      O(n)       |             O(n)              |
|      직교 트리 (Cartesian Tree)      |      N/A      |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |             N/A              |     O(n)      |       O(n)       |      O(n)       |             O(n)              |
|           B-트리 (B-Tree)            |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |           O(logn)            |    O(logn)    |     O(logn)      |     O(logn)     |             O(n)              |
|   레드-블랙 트리 (Red-Black Tree)    |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |           O(logn)            |    O(logn)    |     O(logn)      |     O(logn)     |             O(n)              |
|              Splay Tree              |      N/A      |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |             N/A              |    O(logn)    |     O(logn)      |     O(logn)     |             O(n)              |
|               AVL Tree               |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |           O(logn)            |    O(logn)    |     O(logn)      |     O(logn)     |             O(n)              |
|               KD Tree                |    Θ(logn)    |    Θ(logn)    |     Θ(logn)      |     Θ(logn)     |             O(n)             |     O(n)      |       O(n)       |      O(n)       |             O(n)              |

---
