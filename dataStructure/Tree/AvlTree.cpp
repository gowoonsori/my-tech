/*
* C++ 이용하여 Red Black Tree 구현하기
* 
* 목적 : Red Black Tree 공부 하기 위해 작성했으며, 
*       C++ 이용하여 작성하시는 분들에게 도움이 되고자 했다. 
* 
* 설명 : key 값은 int만 가능 하며 중복 key는 허용 x
*       단순 연결 리스트로 구현
* 
*       class AVLTree
* 
*       변수 :   root node => 초기 null
*       
*       생성자 : RBTREE =>  root 를 null로 초기화
*       
*       함수 :   IsKey => key값이 있는지 검사하는 함수
*               Insert => 재귀를 통한 삽입 함수 (최종적으로 root를 return)
*               InsertFixUp => 삽입 후 규칙 깨졌을 시 재조정 함수
*               Delete => 삭제 함수
*               DeleteFixUp => 삭제 후 규칙 깨졌을 시 재조정 함수
*               Transplant => 삭제 시 이용하며, 삭제할 노드의 자식 노드를 부모노드에 연결해주는 함수
*               RotateRight(x) => x기준 오른쪽으로 회전
*               RotateLeft(x) => x기준 왼쪽으로 회전
*
*               Inorder,Preorder,Postorder => 순회 함수
*               tree_minimum(x), tree_maximum(x) => 노드 x 기준으로 가장 왼쪽, 오른쪽 return 함수
*
*               DisplayMenu, SelectMenu => 초기 Menu판 print 함수
*               Insert_helper,Delete_helper,order_helper,print_helper => 각각 수행시 입력받고 조건 에러 처리 위한 함수 와 tree print 해주는 함수
*
*       InsertFixUp과 DeleteFixUp에서 각 case에 대한 설명은 github에 적어 놓았다.
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
    int height = 1;
};
typedef node *NodePtr;

class AVLTREE {
   private:
    NodePtr root;  //루트 노드

    //key값이 있는지 없는지 검사 있으면 pointer 값, 없으면 nullptr
    NodePtr IsKey(int item) {
        NodePtr t = root;

        /*key값을 찾거나 없다면 break*/
        while (t != NULL && t->key != item) {
            t = (item < t->key) ? t->left : t->right;
        }
        return t;
    }

    /*새로운 key 삽입함수로 root노드 반환*/
    NodePtr Insert(NodePtr r, int item) {
        /*새로운 노드 삽입*/
        if (r == nullptr) {
            NodePtr z = new node;
            z->key = item;
            r = z;
            return r;
        } else if (r->key < item) {  //item이 key값보다 크다면 오른쪽으로 이동
            r->right = Insert(r->right, item);
        } else {  //item이 key값보다 작다면 왼쪽으로 이동
            r->left = Insert(r->left, item);
        }
        InsertFixUp(r, item);  //새로운 노드가 추가되었으므로 재귀적으로 부모노드들 높이 1증가 시켜주고
                               //Balace Factor 측정하여 2이상이라면 재조정함수
        return r;
    }

    /* 높이값 갱신하고 balance Factor 측정후 재조정*/
    void InsertFixUp(NodePtr &r, int item) {
        r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
        int bF = getBalanceFactor(r);

        //case 1 (left left)
        if (bF > 1 && item < r->left->key) {
            r = RotateRight(r);
        }
        //case 2 (left right)
        else if (bF > 1 && item > r->left->key) {
            r->left = RotateLeft(r->left);
            r = RotateRight(r);
        }
        //case 3 (right right)
        else if (bF < -1 && item > r->right->key) {
            r = RotateLeft(r);
        }
        //case 4 ( right left)
        else if (bF < -1 && item < r->right->key) {
            r->right = RotateRight(r->right);
            r = RotateLeft(r);
        }
    }

    bool Delete(int item) {
        return false;
    }

    void DelteFixUp(NodePtr x) {
    }

    /*높이 getter */
    int getHeight(NodePtr r) {
        if (r == nullptr)
            return 0;
        else
            return r->height;
    }

    /*좌우 자식 깊이 비교하여 Balnace Factor get*/
    int getBalanceFactor(NodePtr r) {
        return getHeight(r->left) - getHeight(r->right);
    }

    /*x를 중심으로 왼쪽으로 회전*/
    NodePtr RotateLeft(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        y->left = x;

        //위치가 바뀌었으므로 높이 재조정
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }
    /*y를 중심으로 오른쪽으로 회전*/
    NodePtr RotateRight(NodePtr y) {
        NodePtr x = y->left;
        y->left = x->right;
        x->right = y;

        //위치가 바뀌었으므로 높이 재조정
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

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

            std::cout << root->key << std::endl;
            print_helper(root->left, indent, false);
            print_helper(root->right, indent, true);
        }
    }

    /*중위순회*/
    void Inorder(NodePtr target) {
        if (target == nullptr)
            return;
        Inorder(target->left);
        std::cout << target->key << " ";
        Inorder(target->right);
    }
    /*후위순회*/
    void Postorder(NodePtr target) {
        if (target == nullptr)
            return;
        Postorder(target->left);
        Postorder(target->right);
        std::cout << target->key << " ";
    }
    /*전위순회*/
    void Preorder(NodePtr target) {
        if (target == nullptr)
            return;
        std::cout << target->key << " ";
        Preorder(target->left);
        Preorder(target->right);
    }

   public:
    AVLTREE() {
        this->root = nullptr;
    }
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
        std::cout << "         ** AVL Tree **     " << std::endl;
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
            std::cout << "--> select   :   ";
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
                    std::cout << " !!! Wrong entered !!!\n"
                              << std::endl;
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
        this->root = Insert(this->root, item);
        return;
    }

    void Delete_helper() {
        int item;
        std::cout << "Key to delete  :  ";
        std::cin >> item;
        if (!Delete(item)) {
            std::cout << "!!! " << item << " is not exists !!!\n";
            return;
        }
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
                std::cout << " !!! Wrong enter !!!\n"
                          << std::endl;
                break;
        }
        return;
    }
};

int main() {
    AVLTREE tree;
    tree.SelectMenu();

    return 0;
}