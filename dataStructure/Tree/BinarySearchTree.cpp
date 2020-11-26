#include <Windows.h>

#include <iostream>

enum { _Preorder = 1, _Inorder, _Postorder };

template <typename T>
class Node {
   public:
    T key;
    Node* LNode;
    Node* RNode;
    Node(T key = 0, Node* LNode = NULL, Node* RNode = NULL) {
        this->key = key;
        this->LNode = NULL;
        this->RNode = RNode = NULL;
    }
};

template <typename T>
class BST {
   private:
    Node<T>* root;

   public:
    BST() : root(NULL) {}
    void add(Node<T>* node);
    void Delete(T item);
    bool search_loop(T item);
    void Preorder(Node<T>* target);
    void Inorder(Node<T>* target);
    void Postorder(Node<T>* target);
    void showTree(int element);
};

template <typename T>

bool BST<T>::search_loop(T item) {
    Node<T>* s = this->root;
    while (s != NULL) {
        if (s->key == item)
            return true;  // key가 존재한다면 true
        else if (s->key > item)
            s = s->LNode;  // key가 item보다 크다면 왼쪽으로 이동
        else
            s = s->RNode;  // key가 item보다 작다면 오른쪽으로 이동
    }
    return false;
}

template <typename T>
void BST<T>::add(Node<T>* node) {
    T item = node->key;
    /*트리가 비어있다면*/
    if (this->root == NULL) {
        this->root = node;
        return;
    }
    /*값이 존재하면*/
    if (search_loop(item)) {
        std::cout << "값이 이미 존재합니다" << std::endl;
        return;
    }
    /*item 삽입*/
    Node<T>* s = this->root;

    while (1) {
        /*item이 key값보다 크다면*/
        if (s->key < item) {
            if (s->RNode == NULL) {
                s->RNode = node;
                return;
            }
            s = s->RNode;
        } else {
            if (s->LNode == NULL) {
                s->LNode = node;
                return;
            }
            s = s->LNode;
        }
    }
}

template <typename T>
void BST<T>::Delete(T item) {
    Node<T>* t = this->root;
    Node<T>* parent = NULL;
    Node<T>*child, *succ, *succ_p;

    /*key값을 찾거나 없다면 break*/
    while (t != NULL && t->key != item) {
        parent = t;
        t = (item < parent->key) ? parent->LNode : parent->RNode;
    }

    /*-----탐색 종료------*/
    /*값이 없다면*/
    if (t == NULL) {
        std::cout << "해당 값이 존재 하지 않습니다." << std::endl;
        return;
    }

    /*자식노드가 없거나 1개라면*/
    if (t->RNode == NULL || t->LNode == NULL) {
        child = (t->LNode == NULL) ? t->RNode : t->LNode;
        if (parent != NULL) {
            if (parent->LNode == t)
                parent->LNode = child;
            else
                parent->RNode = child;
            delete (t);
        }
        /*삭제할 노드가 root라면*/
        else {
            delete (t);
            this->root = child;
        }
    }

    /*2개의 자식이 있다면 오른쪽 child의 가장 작은 값을 attach*/
    else {
        succ_p = t;
        succ = t->RNode;

        /*오른쪽 child의 가장 작은 값 찾기*/
        /*succ_p == 가장 작은 값의 부모 노드*/
        /*succ 는 가장 작은 값의 노드*/
        while (succ->LNode != NULL) {
            succ_p = succ;
            succ = succ->LNode;
        }

        /*삭제하려는 노드의 오른쪽 child의 leftnode가 있다면
        succ_p leftnode의 rightnode를
        succ_p의 왼쪽에 연결*/
        if (succ_p->LNode == succ) {
            succ_p->LNode = succ->RNode;
        }
        /*삭제하려는 노드의 오른쪽child의 left node가 없다면
        오른쪽 child의 right node를 삭제할 노드의 오른쪽에 연결*/
        else
            succ_p->RNode = succ->RNode;

        /*삭제할 노드와 교환 후 삭제*/
        t->key = succ->key;
        t = succ;
        delete (t);
    }
    return;
}

//전위 순회
template <typename T>
void BST<T>::Preorder(Node<T>* target) {
    if (target == NULL) return;
    std::cout << target->key << " ";
    this->Preorder(target->LNode);
    this->Preorder(target->RNode);
}

//중위 순회
template <typename T>
void BST<T>::Inorder(Node<T>* target) {
    if (target == NULL) return;
    this->Inorder(target->LNode);
    std::cout << target->key << " ";
    this->Inorder(target->RNode);
}

//후위 순회
template <typename T>
void BST<T>::Postorder(Node<T>* target) {
    if (target == NULL) return;
    this->Postorder(target->LNode);
    this->Postorder(target->RNode);
    std::cout << target->key << " ";
}

template <typename T>
void BST<T>::showTree(int element) {
    switch (element) {
        case _Preorder:
            this->Preorder(this->root);
            std::cout << std::endl;
            break;
        case _Inorder:
            this->Inorder(this->root);
            std::cout << std::endl;
            break;
        case _Postorder:
            this->Postorder(this->root);
            std::cout << std::endl;
            break;
        default:
            break;
    }
}

int main() {
    BST<int> tree;
    tree.add(new Node<int>(35));
    tree.add(new Node<int>(18));
    tree.add(new Node<int>(68));
    tree.add(new Node<int>(99));
    tree.add(new Node<int>(26));
    tree.add(new Node<int>(7));
    tree.add(new Node<int>(12));
    tree.add(new Node<int>(3));
    tree.add(new Node<int>(30));
    tree.add(new Node<int>(22));
    tree.showTree(1);
    tree.showTree(2);
    tree.showTree(3);
    tree.Delete(18);
    tree.showTree(1);

    return 0;
}