#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int val;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

ListNode* create_Node(int val);
void init_list(ListNode *head);
void insert_Node(ListNode** head,int loc,ListNode *node);
void delete_Node(ListNode** head,int loc);
void display(ListNode *head);
ListNode* search_Node(ListNode* head, int val);
ListNode* concat(ListNode* head1, ListNode* head2);

void main(){
    ListNode* list1=NULL;
    ListNode* list2=NULL;

    for(int i=1;i<6;i++) {
        insert_Node(&list1,0,create_Node(i));     //item 5,4,3,2,1
        insert_Node(&list2,0,create_Node(i+10));  //item 15,14,13,12,11
    }
    display(list1);
    display(list2);

    delete_Node(&list1,3);  //list1 item 5,4,2,1
    delete_Node(&list2,0);  //list2 item 14,13,12,11
    list1=concat(list1,list2); //list1 item 5,4,2,1,14,13,12,11
    display(list1);

    if(search_Node(list1,15)!=NULL)printf("value exist.\n"); //search value 15
    
}

ListNode* create_Node(int val){
    ListNode* p=(ListNode*)malloc(sizeof(ListNode));
    p->val=val;
    init_list(p);
    return p;
}
void init_list(ListNode *head){
    head->prev=head;
    head->next=head;
}

//삽입을 스택과 같이 초기값0을 주어지면 리스트 끝이 아닌 앞에 삽입
void insert_Node(ListNode** head,int loc,ListNode* node){
    ListNode *p= *head;
    if(p==NULL)  *head=node;
    else if(loc==0){
        node->next=p;
        p=p->prev;
        node->prev=p;
        p->next=node;
        (*head)->prev=node;
        (*head)=node;
    }
    else{
        for(int i=0;i<loc-2;i++)p=p->next;
            node->next=p->next;
            node->prev=p;
            p->next=node;
            p=node->next;
            p->prev=node;
    }
}

void display(ListNode* head){
    ListNode* p=head;
    while (p->next!=head)
    {
        printf("%d ",p->val);
        p=p->next;
    }

    printf("%d \n",p->val);
}

void delete_Node(ListNode** head,int loc){
    ListNode *delete=*head;
    ListNode *p= *head;
    if(p==NULL)  {perror("삭제할 노드가 없습니다.\n"); exit(1);}
    else if(loc==0){
        p=p->prev;
        *head=(*head)->next;
        p->next=*head;
        (*head)->prev=p;
    }
    else{
        for(int i=0;i<loc-2;i++) {p=p->next; delete=delete->next;}
        delete=delete->next;
        p->next=delete->next;
        delete->next->prev=p;
    }
     free(delete);
}

ListNode* search_Node(ListNode* head, int val){
    ListNode *p=head;

    do{
        if(p->val==val)return p;
        p=p->next;
    }while(p!=head);
    printf("value not exist\n");
    return NULL;
}

ListNode* concat(ListNode* head1, ListNode* head2){
    if(head1==NULL) return head2;
    else if(head2==NULL)return head1;
    else{
        ListNode *p=head1;
        ListNode *t=head2;
        p=p->prev;
        t=t->prev;
        p->next=head2;
        head2->prev=p;
        t->next=head1;
        head1->prev=t;
        return head1;
    }
    return NULL;
}