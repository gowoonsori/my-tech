/*
 * C++ 이용하여 Splay Tree 구현하기
 *
 * 목적 : Splay Tree 공부 하기 위해 작성했으며,
 *       C++ 이용하여 작성하시는 분들에게 도움이 되고자 했다.
 *
 * 설명 : key 값은 int만 가능 하며 중복 key는 허용 x
 *       단순 연결 리스트로 구현
 *
 *       class SplayTree
 *
 *       변수 :   root => root node
 *
 *       생성자 : SplayTree =>  root 를 null로 초기화
 *
 *       함수 :   IsKey => key값이 있는지 검사하는 함수
 *
 *               Insert => 일반 BST의 삽입함수에 끝에 Splay 추가 (return void)
 *               Delete => Splay후 successor를 root로 만드는 함수 (return void)
 *               Splay(x) => x를 root로 재조정 함수 ( return void)
 *               replace(x,y) => 삭제할 x와 successor 위치를 바꿔주는 함수 (return void)
 *
 *               RotateRight(x) => x기준 오른쪽으로 회전
 *               RotateLeft(x) => x기준 왼쪽으로 회전
 *
 *               Inorder,Preorder,Postorder => 순회 함수
 *               tree_minimum(x), tree_maximum(x) => 노드 x 기준으로 가장 왼쪽, 오른쪽 return 함수
 *
 *               DisplayMenu, SelectMenu => 초기 Menu판 print 함수
 *               Insert_helper,Delete_helper,order_helper,print_helper => 각각 이벤트 수행시 입력받고 조건 에러 처리 위한 함수 와 tree print
 * 해주는 함수
 *
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
    node *parent = nullptr;
};
typedef node *NodePtr;

class SplayTree {
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
    void Insert(int item) {
        /*새로운 노드 삽입*/
        if (this->root == nullptr) {
            NodePtr x = new node;
            x->key = item;
            this->root = x;
            return;
        }
        NodePtr y;  //삽입할 x의 부모노드 y
        NodePtr y_next = this->root;

        /*부모노드 y찾기*/
        while (y_next) {
            y = y_next;
            y_next = (y->key > item) ? y->left : y->right;
        }

        /*y의 자식으로 x붙여주기*/
        NodePtr x = new node;
        x->key = item;
        x->parent = y;
        if (y->key > item)
            y->left = x;
        else
            y->right = x;

        Splay(x);
    }

    /*key 삭제 함수*/
    void Delete(int item) {
        node *z = IsKey(item);
        Splay(z);  //삭제할 노드를 root로 올린 후 resturcture

        if (!z->left)  // left child가 null
            replace(z, z->right);
        else if (!z->right)  // left child가 null이 아니고 right child가 null일때
            replace(z, z->left);
        else {                                 //자식이 둘다있을때
            node *y = tree_minimum(z->right);  // find successor

            /*succesoor가 z의 오른쪽 자식일때*/
            if (y->parent != z) {
                replace(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            replace(z, y);
            y->left = z->left;
            y->left->parent = y;
        }

        delete z;
    }

    /* x를 기준으로 splay*/
    void Splay(NodePtr x) {
        /*x가 root가 될때까지*/
        while (x->parent) {
            NodePtr p = x->parent;
            NodePtr g = p->parent;

            /*x의 부모 노드가 root라면*/
            if (!x->parent->parent) {
                if (x->parent->left == x)
                    RotateRight(x->parent);
                else
                    RotateLeft(x->parent);
            }
            /*zig zig*/
            else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                RotateRight(x->parent->parent);
                RotateRight(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                RotateLeft(x->parent->parent);
                RotateLeft(x->parent);
            }
            /*zig zag*/
            else if (x->parent->left == x && x->parent->parent->right == x->parent) {
                RotateRight(x->parent);
                RotateLeft(x->parent);
            } else {
                RotateLeft(x->parent);
                RotateRight(x->parent);
            }
        }
    } /*x를 중심으로 왼쪽으로 회전*/
    void RotateLeft(NodePtr x) {
        NodePtr y = x->right;

        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }
    /*x를 중심으로 오른쪽으로 회전*/
    void RotateRight(NodePtr x) {
        NodePtr y = x->left;

        x->left = y->right;
        if (y->right) {
            y->right->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        x->parent = y;
        y->right = x;
    }

    /* 삭제시 */
    void replace(NodePtr u, NodePtr v) {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v) v->parent = u->parent;
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

            std::cout << root->key << std::endl;
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
    SplayTree() { this->root = nullptr; }
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
        std::cout << "         ** Splay Tree **     " << std::endl;
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
        Insert(item);
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
        Delete(item);
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
    SplayTree tree;
    tree.SelectMenu();

    return 0;
}