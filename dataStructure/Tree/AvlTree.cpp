/*
* C++ 이용하여 AVL Tree 구현하기
* 
* 목적 : AVL Tree 공부 하기 위해 작성했으며, 
*       C++ 이용하여 작성하시는 분들에게 도움이 되고자 했다. 
* 
* 설명 : key 값은 int만 가능 하며 중복 key는 허용 x
*       이중 연결 리스트로 구현
* 
*       각 case에 대한 설명은 github에 적어 놓았다.
*
* 작성자 : gowoonsori 
* github : https://github.com/gowoonsori
*/

#include <iostream>

struct node
{
    int key;
    node *left;
    node *right;
    node *parent;
    int height;
};

typedef node *NodePtr;

class AVLTREE
{
private:
    NodePtr root; //루트 노드

    //key값이 있는지 없는지 검사 있으면 pointer 값, 없으면 nullptr
    NodePtr IsKey(int item)
    {
        NodePtr t = root;
        NodePtr parent = NULL;

        /*key값을 찾거나 없다면 break*/
        while (t != NULL && t->key != item)
        {
            parent = t;
            t = (item < parent->key) ? parent->left : parent->right;
        }
        return t;
    }

    bool Insert(int item)
    {
    }

    void InsertFixUp(NodePtr z)
    {
    }

    bool Delete(int item)
    {
    }

    void DelteFixUp(NodePtr x)
    {
    }

    /* u의 위치에 v를 이식 */
    void Transplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }
    /*x를 중심으로 왼쪽으로 회전*/
    void RotateLeft(NodePtr x)
    {
        NodePtr y;

        y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }
    /*x를 중심으로 오른쪽으로 회전*/
    void RotateRight(NodePtr y)
    {
        NodePtr x;

        x = y->left;
        y->left = x->right;
        if (x->right)
            x->right->parent = y;
        x->parent = y->parent;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }

        y->parent = x;
        x->right = y;
    }

    /*show tree*/
    void print_helper(NodePtr root, std::string indent, bool last)
    {
        // print the tree structure on the screen
        if (root != leafNode)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "R----";
                indent += "     ";
            }
            else
            {
                std::cout << "L----";
                indent += "|    ";
            }

            std::string sColor = (root->color == RED) ? "RED" : "BLACK";
            std::cout << root->key << "(" << sColor << ")" << std::endl;
            print_helper(root->left, indent, false);
            print_helper(root->right, indent, true);
        }
    }

    /*중위순회*/
    void Inorder(NodePtr target)
    {
        if (target == leafNode)
            return;
        Inorder(target->left);
        std::cout << target->key << " ";
        Inorder(target->right);
    }
    /*후위순회*/
    void Postorder(NodePtr target)
    {
        if (target == leafNode)
            return;
        Postorder(target->left);
        Postorder(target->right);
        std::cout << target->key << " ";
    }
    /*전위순회*/
    void Preorder(NodePtr target)
    {
        if (target == leafNode)
            return;
        std::cout << target->key << " ";
        Preorder(target->left);
        Preorder(target->right);
    }

public:
    AVLTREE()
    {
        int key = 0;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
        int height = 0;
    }
    //최솟값 찾기
    NodePtr tree_minimum(NodePtr x)
    {
        while (x->left != leafNode)
        {
            x = x->left;
        }
        return x;
    }
    //최댓값 찾기
    NodePtr tree_maximum(NodePtr x)
    {
        while (x->right != leafNode)
        {
            x = x->right;
        }
        return x;
    }

    void DisplayMenuBoard()
    {
        std::cout << "               Menu " << std::endl;
        std::cout << "          1. Insert Key     " << std::endl;
        std::cout << "          2. Delete Key     " << std::endl;
        std::cout << "          3. Show Tree      " << std::endl;
        std::cout << "          4. choose order   " << std::endl;
        std::cout << "          5. show Menu      " << std::endl;
        std::cout << "          6. clear Display  " << std::endl;
        std::cout << "          7. exit           " << std::endl;
        std::cout << std::endl;
    }
    void SelectMenu()
    {
        DisplayMenuBoard();
        int i = -1;

        while (i != 8)
        {
            std::cout << "--> select   :   ";
            std::cin >> i;
            switch (i)
            {
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

    void Insert_helper()
    {
        int item;
        std::cout << "Key to insert  :  ";
        std::cin >> item;
        if (!Insert(item))
        {
            std::cout << "!!! " << item << " is already exists !!!\n";
            return;
        }
        return;
    }
    void Delete_helper()
    {
        int item;
        std::cout << "Key to delete  :  ";
        std::cin >> item;
        if (!Delete(item))
        {
            std::cout << "!!! " << item << " is not exists !!!\n";
            return;
        }
        return;
    }
    void Order_helper()
    {
        int i;
        std::cout << "         == Order Menu ==" << std::endl;
        std::cout << "          1. PreOrder" << std::endl;
        std::cout << "          2. InOrder" << std::endl;
        std::cout << "          3. PostOrder" << std::endl;
        std::cout << "          4. exit" << std::endl;
        std::cout << " --> select  :  ";

        std::cin >> i;
        switch (i)
        {
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

int main()
{
    AVLTREE tree;
    tree.SelectMenu();

    return 0;
}