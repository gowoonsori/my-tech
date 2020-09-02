#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode{
    int val;
    struct StackNode *link;
} StackNode;

typedef struct{
    StackNode *top;
}LinkedStackType;

/*스택 초기화*/
void init(LinkedStackType *s);
/*스택이 비었는지 검사*/
int is_empty(LinkedStackType *s);
void push(LinkedStackType* s, int val);
int pop(LinkedStackType *s);
int peek(LinkedStackType s);

int main(){
    LinkedStackType s;
    init(&s);

    for(int i=1;i<6;i++) push(&s,i);
    for(int i=0;i<5;i++) printf("%d ",pop(&s));
    if(is_empty(&s)==1) printf("\nStack is empty\n");

    sleep(10000);
}

void init(LinkedStackType *s){
    s->top=NULL;
}
int is_empty(LinkedStackType *s){
    return (s->top==NULL);
}
void push(LinkedStackType* s, int val){
    StackNode *p= (StackNode*)malloc(sizeof(StackNode));
    /*메모리 할당 에러*/
    if(p==NULL){
        fprintf(stderr,"malloc error\n");
        return;
    }

    p->val=val;
    p->link=s->top;
    s->top=p;
}
int pop(LinkedStackType *s){
    if(is_empty(s)){
        fprintf(stderr,"stack is empty\n");
        exit(1);
    }
    else{
        StackNode *p=s->top;
        int val=p->val;
        s->top=p->link;
        free(p);
        return val;
    }
}
int peek(LinkedStackType s){
    if(s.top==NULL){
        fprintf(stderr,"error");
        exit(1);
    }
    return s.top->val;
}