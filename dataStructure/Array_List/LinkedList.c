#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int val;
    struct ListNode *link;
} ListNode;

ListNode* create_Node(int val,ListNode *link);
void insert_Node(ListNode** head,int loc,ListNode* add);
void delete_Node(ListNode** head,int loc,ListNode* delete);
void display(ListNode* head);                         //show list
ListNode* search_Node(ListNode* head,int val);       //node search
ListNode* concat(ListNode* head1, ListNode* head2);  //list concat

void main(){

    struct ListNode *list1=NULL,*list2=NULL;
    
    for(int i=1;i<5;i++){
        insert_Node(&list1,0,create_Node(i,NULL));    //list 1 item :4,3,2,1 
        insert_Node(&list2,0,create_Node(i+10,NULL)); //list 2 item :14,13,12,11
    }
    display(list1);
    display(list2);

    list1=concat(list1,list2);                         //list 1 item 4,3,2,1,14,13,12,11
    display(list1);
    insert_Node(&list1,4,create_Node(40,NULL));     //list 1 item 4,3,2,40,1,14,13,12,11
    delete_Node(&list1,4,list1);                    //list 1 item 4,3,2,1,14,13,12,11
    display(list1);
    
}

ListNode* create_Node(int val,ListNode *link){
    ListNode* list;
    list=(ListNode*)malloc(sizeof(ListNode));
    if(list==NULL) perror("메모리 할당 에러");

    list->val=val;
    list->link=link;

    return list;
}
void insert_Node(ListNode** head,int loc,ListNode* add){
  //해당 리스트가 비어있다면
    if(*head==NULL){
        add->link=NULL;
        *head=add;
    }
    //위치를 지정하지 않으면 리스트 첫번째에 삽입
    else if(loc==0){
        add->link=*head;
        *head=add;
    }
    //지정한 위치 사이에 삽입
    else {
        ListNode* p=*head;

        for(int i=0;i<loc-2;i++) p=p->link;
        add->link=p->link;
        p->link=add;
    }
}
void delete_Node(ListNode** head,int loc,ListNode* delete){
  //해당 리스트가 비어있다면
    if(*head==NULL){
        perror("삭제할 노드가 없습니다");
    }
    //위치를 지정하지 않으면 리스트 첫번째 삭제
    else if(loc==0){
        (*head)=(*head)->link;
    }
    //지정한 위치 뒤에 노드 삭제
    else {
        ListNode* p=*head;
        for(int i=0;i<loc-2;i++) {p=p->link; delete=delete->link;}
        delete=delete->link;
        p->link=delete->link;   
    }
    free(delete);
}
void display(ListNode* head){
    ListNode* p = head;
    while(p!=NULL){
        printf("%d ",p->val);
        p=p->link;
    }
    printf("\n");
}
ListNode* search_Node(ListNode* head, int val){
    ListNode *p=head;

    while (p!=NULL)
    {
        if(p->val==val)return p;
        p=p->link;
    }
    printf("탐색 결과 해당 값은 존재 하지 않습니다.\n");
    return NULL;
}
ListNode* concat(ListNode* head1, ListNode* head2){
    if(head1==NULL) return head2;
    else if(head2==NULL)return head1;
    else{
        ListNode* p=head1;
        while (p->link!=NULL) p=p->link;
        p->link=head2;
        return head1;
    }
    return NULL;
}