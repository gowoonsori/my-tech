`RB-Tree`를 응용한 트리로 RB-Tree의 많은 조건을 일부 제거하여 구현을 더 간단하게 만든 트리로 균형을 맞추기 위해 레벨의 개념을 사용한 트리이다.

부모와 레벨이 같은 자식 노드의 연결을 `수평 링크`라고 하며, 이 노드를 구분하기 위해 RED라는 개념을 이용한다.

<br><br>

## 1. 특징

- 왼쪽 자식은 RED가 될 수 없다.

- 연속으로 RED가 올 수 없다. (이중 RED 불가 == 이중 수평 링크)
- 루트에서 null가지 leafnode까지의 경로에는 동일한 수의 블랙 노드가 존재한다. (RB Tree의 규칙)
- 모든 leaf node의 레벨은 1이다
- 모든 왼쪽 자식의 레벨은 부모의 레벨보다 1 낮다
- 모든 오른쪽 자식의 레벨은 부모와 같거나 1 낮다
- 모든 오른쪽 손자의 레벨은 할아버지 노드보다 낮다
- 1보다 큰 레벨의 모든 노드들은 2개의 자식을 갖는다

<br>

{{% swipe-image src="./intro.png" %}}

왼쪽 트리를 얼핏 보면 RB-Tree같지만 왼쪽 자식은 RED를 갖지 않는 AA-Tree이고, 이를 레벨을 기준으로 보면 오른쪽과 같이 그려 볼 수 있다.

<br><br>

## 2. 사용 기법

### 📌 Split

이중 수평 링크(이중 red)일 시 해결하기 위한 방법으로 지금까지 다른 BBST와 동일하게 rotate의 개념이다.

<br>

{{% swipe-image src="./split.png" %}}

이중 red가 생기는 경우는 위 사진과 같이 무조건 오른쪽 방향으로 생기기 때문에 할아버지 노드(35) 기준으로 left방향으로만 rotate시키고 색을 바꿔 주면 된다.

특징으로 Split을 수행하면 level이 달라진다.

<br>

### 📌 Skew

red가 왼쪽자식으로 위치 한 경우 규칙에 위배되기 때문에 해결하는 방법으로 문제가 되는 노드(40)과 부모 노드(50)을 right rotate 시키고 색을 바꿔 이중 레드로 만드는 방법이다.

{{% swipe-image src="./skew.png" %}}

Skew는 회전을 수행해도 기본적으로 동일한 level선상에서 바뀐다.

<br><br>

## 3. 구현

위에서 말한 것처럼 실제 구현에 있어, 실제 red / black의 값을 갖는 데이터를 추가하지 않아도 구현이 가능하다. 대신 level을 저장할 데이터를 추가해야 한다.

### 📌 삽입

BST규칙에 맞게 삽입 후 문제가 되는 노드를 Split과 Skew를 통해 rebalancing하며 root까지 올라가면서 규칙에 위배되지 않을 때 까지 split과 skew를 수행하면 된다.

<br>

### 📌 삭제

#### 1. 삭제할 노드가 red leafnode

그냥 제거하면 된다.

#### 2. 삭제할 노드가 하나의 leaf node 자식을 갖는 내부 노드 인 경우

삭제할 노드는 검은색이고, 자식은 레드일 수 밖에 없기 때문에 자식과 값을 교환 후, 삭제하면 된다.

#### 3. 두개의 자식이 있고 successor가 red일 경우

이는 red가 leafnode일 경우밖에 없기 때문에 값을 교환 후 leafnode를 삭제하면 된다.

#### 4. 두개의 자식이 있고 successor가 한 개의 leaf node 자식을 갖는 경우

값을 교환 후 2번 규칙 적용하면 된다.

#### 5. 두개의 자식이 있고, Successor가 black leaf node 이거나 삭제할 노드가 black leaf node 일 경우

black leaf node를 삭제 시 레벨 2이상의 노드는 2개의 자식을 갖는 다는 규칙이 깨지므로 아래와 같은 과정을 수행해주어야 한다.

<br>

{{% swipe-image src="./d1.png" %}}

Leaf node를 삭제하고 그 부모 노드(15)의 레벨을 한 단계 감소시킨다.

{{% swipe-image src="./d2.png" %}}

할아버지 노드(30)의 레벨과 부모 노드의 레벨이 2이상 차이 난다면 할아버지 레벨도 1감소시킨다.
{{% swipe-image src="./d3.png" %}}

또, 할아버지 노드의 오른쪽 자식(80)이 red일 경우 오른쪽 자식도 레벨 1감소 시킨다.
{{% swipe-image src="./d4.png" %}}

그 후, 할아버지 노드(30)를 기준으로 skew, 할아버지 오른쪽 자식(80)의 노드 기준으로 skew 한다.
{{% swipe-image src="./d5.png" %}}

할아버지(30) 오른쪽 손자 노드(80)를 기준으로 skew를 수행한다.

{{% swipe-image src="./d6.png" %}}

그 후, 할아버지 노드(30)을 기준으로 split을 수행한다.

{{% swipe-image src="./d7.png" %}}

마지막으로 할아버지 노드의 오른쪽 자식(60)을 기준으로 split을 수행한다.

<br>

### 📌 순회 과정

일반 BST와 동일하게 전위 / 중위 /후위 로 순회를 하는 방법이 있다.

<br>

### 📌 탐색 과정

AA Tree또한, BBST이므로 탐색 방법은 동일하고 O(lgn)의 시간 복잡도를 보장한다.

<br><br>

## 4. 시간 복잡도

삽입과 삭제 과정에서 rotate가 일어나는데 이는 O(1)만큼의 시간이 소요되고 이 rotate가 최대 O(lgn) 만큼 일어나기 때문에 O(lgn)의 시간 복잡도를 갖는다.

<br><br>

## 5. RB Tree와 비교

RB-Tree와 비교해서 자식의 왼쪽에 있냐 오른쪽에 있냐 대칭이지도 않고 무조건 한쪽방향으로만 회전도 할 수 있고 case 수도 훨씬 적어 구현이 간단하며, red/black은 설명을 쉽게 하기 위해 구분 지어 설명한 것이지 실제 구현에 있어서는 red/black의 값을 갖는 추가 데이터가 필요하지 않다. (자식이지만 같은 레벨에 있는 자식을 red라고 명명했을 뿐)

<br><br><br>

## 구현 코드

[github으로 보기](https://github.com/gowoonsori/my-tech/blob/master/dataStructure/Tree/aaTree.cpp)

<details>
<summary style="font-Weight : bold; font-size : 15px; color : #F90000;" >  📃 구현 코드 (c++) ( 접기 / 펼치기 )</summary>
<div>

```cpp
/*
 * C++ 이용하여 AA Tree 구현하기
 *
 * 목적 : AA Tree 공부 하기 위해 작성했으며,
 *       C++ 이용하여 작성하시는 분들에게 도움이 되고자 했다.
 *
 * 설명 : key 값은 int만 가능 하며 중복 key는 허용 x
 *       단순 연결 리스트로 구현
 *
 *       class AA Tree
 *
 *       변수 :   root => root node
 *
 *       생성자 : AATREE =>  root 를 null로 초기화
 *
 *       함수 :   IsKey => key값이 있는지 검사하는 함수
 *
 *               Insert => 재귀를 이용한 삽입 함수 (return void)
 *               Delete => 재귀를 이용한 삭제 함수 (return void)
 *
 *               split(x) => x가 이중 레드를 가지고 있다면 rotate (return void)
 *               skewy(x) => x의 왼쪽자식이 레드일때 level변화 없이 교환 (return void)
 *
 *               Inorder,Preorder,Postorder => 순회 함수
 *               tree_minimum(x), tree_maximum(x) => 노드 x 기준으로 가장 왼쪽, 오른쪽 return 함수
 *
 *               DisplayMenu, SelectMenu => 초기 Menu판 print 함수
 *               Insert_helper,Delete_helper,order_helper,print_helper => 각각 이벤트 수행시 입력받고 조건 에러 처리 위한 함수 와 tree print
 * 해주는 함수
 *
 *        Balancing에서 각 case에 대한 설명은 github에 적어 놓았다.
 *
 * 작성자 : gowoonsori
 * github : https://github.com/gowoonsori/my-tech/tree/master/dataStructure/Tree
 */

#include <algorithm>  // max() 함수 이용
#include <iostream>

struct node {
    int key;
    node *left = nullptr;
    node *right = nullptr;
    int level = 1;
};
typedef node *NodePtr;

class AATree {
   private:
    NodePtr root;  //루트 노드

    // key값이 있는지 없는지 검사 있으면 pointer 값, 없으면 nullptr
    NodePtr IsKey(int item) {
        NodePtr t = root;

        /*key값을 찾거나 없다면 break*/
        while (t != nullptr && t->key != item) {
            t = (item < t->key) ? t->left : t->right;
        }
        return t;
    }

    /*새로운 key 삽입함수로 root노드 반환*/
    void Insert(int item, NodePtr &x) {
        /*새로운 노드 삽입*/
        if (!x) {
            NodePtr y = new node;
            y->key = item;
            x = y;
            return;
        } else if (x->key < item) {
            Insert(item, x->right);
        } else {
            Insert(item, x->left);
        }

        /*재귀적으로 Insert를 수행하기 때문에 삽입 위치부터 루트까지 올라가며
          규칙이 위배되는 지 검사하여 skew, split 수행이 가능하다.*/
        skew(x);
        split(x);
    }

    /*key 삭제 함수*/
    void Delete(int item, NodePtr &x) {
        static NodePtr y, p;  // y : 삭제할 노드가 red leaf인지 판별하기 위한 포인터
                              // p : 자식이 두개인 경우 successor와 값을 교환후 삭제하기 위한 포인터

        if (!x) return;
        y = x;
        if (item < x->key) {
            Delete(item, x->left);
        } else {
            p = x;
            Delete(item, x->right);
        }

        /*삭제할 노드가 red leaf이거나 successor가 red leaf일때*/
        if (x == y) {
            p->key = x->key;
            x = x->right;
            delete y;
        } else {
            /*x의 레벨과 자식의 레벨이 2이상 차이날경우*/
            if ((x->left && x->left->level < x->level - 1) || (x->right && x->right->level < x->level - 1)) {
                /*x의 레벨을 감소 시키고 x의 오른쪽 자식이 레드 일경우 자식도 레벨 감소*/
                if (x->right->level > --x->level) {
                    x->right->level = x->level;
                }
                skew(x);
                skew(x->right);
                skew(x->right);
                split(x);
                split(x);
            }
        }
    }
    void split(NodePtr &x) {
        /*x의 손자와 x의 레벨이 같을때 == 이중 레드*/
        if (x->right && x->right->right && x->right->right->level == x->level) {
            NodePtr y = x->right;
            x->right = y->left;
            y->left = x;
            x = y;
            x->level++;
        }
    }

    void skew(NodePtr &x) {
        /*x의 왼쪽자식이 레드일때 레벨의 변화 없이 값 교환*/
        if (x->left && x->left->level == x->level) {
            NodePtr y = x->left;
            x->left = y->right;
            y->right = x;
            x = y;
        }
    }

    /*y를 중심으로 오른쪽으로 회전*/

    /*show tree*/
    void print_helper(NodePtr root, std::string indent, bool last) {
        // print the tree structure on the screen
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "     ";
            } else {
                std::cout << "L----";
                indent += "|    ";
            }

            std::cout << root->key << " (" << root->level << ")" << std::endl;
            print_helper(root->left, indent, false);
            print_helper(root->right, indent, true);
        }
    }

    /*중위순회*/
    void Inorder(NodePtr target) {
        if (target == nullptr) return;
        Inorder(target->left);
        std::cout << target->key << " ";
        Inorder(target->right);
    }
    /*후위순회*/
    void Postorder(NodePtr target) {
        if (target == nullptr) return;
        Postorder(target->left);
        Postorder(target->right);
        std::cout << target->key << " ";
    }
    /*전위순회*/
    void Preorder(NodePtr target) {
        if (target == nullptr) return;
        std::cout << target->key << " ";
        Preorder(target->left);
        Preorder(target->right);
    }

   public:
    AATree() { this->root = nullptr; }
    //최솟값 찾기
    NodePtr tree_minimum(NodePtr x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }
    //최댓값 찾기
    NodePtr tree_maximum(NodePtr x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }

    void DisplayMenuBoard() {
        std::cout << "         ** AA Tree **     " << std::endl;
        std::cout << "                            " << std::endl;
        std::cout << "              Menu          " << std::endl;
        std::cout << "          1. Insert Key     " << std::endl;
        std::cout << "          2. Delete Key     " << std::endl;
        std::cout << "          3. Show Tree      " << std::endl;
        std::cout << "          4. choose order   " << std::endl;
        std::cout << "          5. show Menu      " << std::endl;
        std::cout << "          6. clear Display  " << std::endl;
        std::cout << "          7. exit           " << std::endl;
        std::cout << std::endl;
    }
    void SelectMenu() {
        DisplayMenuBoard();
        int i = -1;

        while (i != 8) {
            std::cout << "(show Menu : 5) -->  select :   ";
            std::cin >> i;
            switch (i) {
                case 1:
                    Insert_helper();
                    break;
                case 2:
                    Delete_helper();
                    break;
                case 3:
                    print_helper(root, "", true);
                    break;
                case 4:
                    Order_helper();
                    break;
                case 5:
                    DisplayMenuBoard();
                    break;
                case 6:
                    system("cls");
                    DisplayMenuBoard();
                    break;
                case 7:
                    return;
                default:
                    std::cout << " !!! Wrong entered !!!\n" << std::endl;
            }
        }
    }

    void Insert_helper() {
        int item;
        std::cout << "Key to insert  :  ";
        std::cin >> item;
        if (IsKey(item)) {
            std::cout << "!!! " << item << " is already exists !!!\n";
            return;
        }
        Insert(item, root);
        return;
    }

    void Delete_helper() {
        int item;
        std::cout << "Key to delete  :  ";
        std::cin >> item;
        if (!IsKey(item)) {
            std::cout << "!!! " << item << " is not exists !!!\n";
            return;
        }
        Delete(item, root);
        return;
    }

    void Order_helper() {
        int i;
        std::cout << "         == Order Menu ==" << std::endl;
        std::cout << "          1. PreOrder" << std::endl;
        std::cout << "          2. InOrder" << std::endl;
        std::cout << "          3. PostOrder" << std::endl;
        std::cout << "          4. exit" << std::endl;
        std::cout << " --> select  :  ";

        std::cin >> i;
        switch (i) {
            case 1:
                Preorder(this->root);
                std::cout << std::endl;
                break;
            case 2:
                Inorder(this->root);
                std::cout << std::endl;
                break;
            case 3:
                Postorder(this->root);
                std::cout << std::endl;
                break;
            case 4:
                return;
            default:
                std::cout << " !!! Wrong enter !!!\n" << std::endl;
                break;
        }
        return;
    }
};

int main() {
    AATree tree;
    tree.SelectMenu();

    return 0;
}
```

</div>
</details>

<br><br>
