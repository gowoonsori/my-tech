#include <iostream>

enum Color{ RED , BLACK };
        struct node{
            int key;
            node* left;
            node* right;
            node* parent;
            Color color;
        };
typedef node* NodePtr;

class RB_TREE{
    private:
        NodePtr root;
        NodePtr leafNode;

        void initializeNULLNode(NodePtr node, NodePtr p) {
		    node->key = 0;
		    node->parent = p;
		    node->left = nullptr;
		    node->right = nullptr;
		    node->color = BLACK;
	    }

        void InsertFixUp(node* z){
            /*root 노드가 아니고 부모 색이 red라면*/
                while(z != root && z->parent->color == RED){
                    node* grandparent = z->parent->parent;
                    node* uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
                    bool side = (z->parent == grandparent->left) ? true : false;    //if left : 1 / right : 0

                    /*case 1*/
                    if(uncle && uncle->color == RED){
                        z->parent->color = BLACK;
                        uncle->color = BLACK;
                        grandparent->color = RED;
                        z = grandparent;
                    }
                    /*case 2*/
                    else{
                        /*case 2-1
                         *부모가 할아버지의 왼쪽일 경우 -> z가 p[z]의 오른쪽 자식일 경우 rotate left
                         *부모가 할아버지의 오른쪽일 경우 -> z가 p[z]의 왼쪽 자식일 경우 rotate right
                         */
                        if( z == (side ? z->parent->right : z->parent->left)){
                            z = z->parent;
                            side ? RotateLeft(z) : RotateRight(z);
                        }
                        /*case 2-2*/
                        z->parent->color = BLACK;
                        grandparent->color = RED;
                        side ? RotateRight(grandparent) : RotateLeft(grandparent);
                    }
                }
                root->color = BLACK;
        }
        void DelteFixUp(node *x){
                    
        }
        /* u의 위치에 v를 이식 */
        void Transplant(node *u, node *v){
            if(u->parent == nullptr) root = v; 
            else if( u == u->parent->left) u->parent->left = v;
            else u->parent->right = v;

            v->parent = u->parent;
        }
        void RotateLeft(node* x){
            node *y;

            y = x->right;
            x->right = y->left;
            if (y->left) y->left->parent = x;
            y->parent = x->parent;

            if (!x->parent){
                root = y;
            }
            else if (x == x->parent->left){
                x->parent->left = y;
            } 
            else{
                x->parent->right = y;
            }
            x->parent = y;
            y->left = x;

        }      
        void RotateRight(node* y){
           node *x;

            x = y->left;
            y->left = x->right;
            if (x->right) x->right->parent = y;
            x->parent = y->parent;
        
            if (!y->parent){
                root = x;
            }
            else if (y == y->parent->left){
                y->parent->left = x;
            }
            else{
                y->parent->right = x;
            }

            y->parent = x;
            x->right = y;
        }

    public:
        RB_TREE(){
            leafNode = new node;
            leafNode->color = BLACK;
            leafNode->left = nullptr;
            leafNode->right = nullptr;
            root = leafNode;
        }
        node* GetRoot(){
            return root;
        }     
        node* IsKey(int item){
            node* t = root;
            node* parent = NULL;

            /*key값을 찾거나 없다면 break*/
            while (t != NULL && t->key != item) {
                parent = t;
                t = (item < parent->key) ? parent->left : parent->right;
            }
            return t;
        }
        node* tree_minimum(node *x){
	        while(x->left != leafNode){
		        x = x->left;
	        }
	        return x;
        }

        void Insert(int item){ 
            if(IsKey(item)){
                std::cout <<"!!! " << item <<" is already exists !!!\n";
                return;
            }
            else{
                node *x =this->root, *y= nullptr;    // x : 삽입할 곳 찾기위한 포인터 / y : 삽입할 곳의 부모노드
                node* z = new node();
                z->key = item;
                z->color = RED;
                z->parent = nullptr;
                z->left = leafNode;
                z->right = leafNode;

            /*BST의 삽입 연산*/
                while(x != leafNode){
                    y = x;
                    if(x->key < item) x = x->right;  
                    else x = x->left; 
                }

                z->parent = y;

                if(y == nullptr) root = z;
                else if(z->key > y->key) y->right = z;
                else y->left = z;
                z->parent = y;

                if (z->parent == nullptr){
			        z->color = BLACK;
			        return;
		        }

		        // if the grandparent is null, simply return
		        if (z->parent->parent == nullptr) {
			        return;
		        }

                InsertFixUp(z);
            }
        }
        
        bool Delete(int item){
            node *z = IsKey(item);

            if(!z){
                std::cout <<"!!! " << item <<" is not exists !!!\n";
                return false;
            }
            else{
                node *x, *xp;
	            Color OriginalColor = z->color;

	            if(!z->left){
                    xp = z->parent;
		            Transplant(z,x= z->right);
	            }
	            else if(!z->right){
                    xp = z->parent;
		            Transplant(z,x= z->left);
	            }
	            else{
		            node* y = tree_minimum(z->right);
		            OriginalColor = y->color;  //r
		            x = y->right;       //y의 오른쪽 자식

		            if(y->parent == z ){ //z의 오른쪽 자식이 가장 작은 key(=y는 왼쪽 child가 없음)
                        if(x) x->parent = y;  
                        xp = y;
                        Transplant(z,z->right);
                        y->left = z->left;
                        y->left->parent = y;
                    }
		            else{
			            Transplant(y, y->right);
			            y->right = z->right;
			            y->right->parent = y;
                    }
		            Transplant(z, y);
		            y->left = z->left;
		            y->left->parent = y;
		            y->color = z->color;
	            }
                delete z;  
                if(OriginalColor == BLACK) DelteFixUp(x);
                return true;
            }
        }
        void Inorder(node* target ) {
            if (target == leafNode) return;
                Inorder(target->left);
                std::cout << target->key << " ";
                Inorder(target->right);
        }
        void Postorder(node* target ) {
            if (target == leafNode) return;
                Postorder(target->left);
                Postorder(target->right);
                std::cout << target->key << " ";
        }
        void Preorder(node* target ) {
            if (target == leafNode) return;
                std::cout << target->key << " ";
                Preorder(target->left);
                Preorder(target->right);
        }
};



int main(){
    RB_TREE tree;
    tree.Insert(18);
    tree.Insert(10);
    tree.Insert(17);
    tree.Insert(16);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(30);
    tree.Insert(19);
    tree.Insert(15);
    tree.Inorder(tree.GetRoot());
}