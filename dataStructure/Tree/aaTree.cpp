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