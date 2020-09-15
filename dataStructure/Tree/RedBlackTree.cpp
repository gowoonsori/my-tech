#include <iostream>

using namespace std;

struct node{
    int key;
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
    string color;
};

class RB_TREE{
    private:
        node* root;

    public:
        RB_TREE() : root(NULL){}
        void insert(int item){ 
            if(root == NULL){
                root = new node();
                root->key = item;
                root->color = "black";
            }
            else{
                node* p = root;

                node* newNode = new node();
                newNode->key = item;
                newNode->color = "red";

                while(p!=NULL){
                    /*item이 key값보다 크다면*/
                    if(p->key < item){
                        /*오른쪽 자식이 없다면 == leaf node라면*/
                        if( p->right == NULL) {
                            p->right = newNode;
                            newNode->parent = p;
                        }
                        else{ p = p->right; }   
                    }
                    /*item이 key값보다 작다면*/
                    else{
                        if(p->left == NULL){
                            p->left = newNode;
                            newNode->parent = p;
                        }
                        else{ p = p->left; }
                    }
                }
                delete p;
                
                /*Internal Property가 위반되는 경우 ( 레드가 두개 연속으로 온경우)*/
                if(newNode->parent->color == "red"){
                    node* grandparent = newNode->parent->parent;
                    node* uncle = (newNode->parent == grandparent->left) ? grandparent->right : grandparent->left;
                    
                    /*case 1*/
                    if(uncle->color == "red"){

                    }
                }

            }
        }
};



int main(){
    RB_TREE tree;
    tree.insert(1);
}