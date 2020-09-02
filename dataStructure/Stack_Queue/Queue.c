#include<stdio.h>
#include<stdlib.h>


typedef struct QueueNode{
    int val;
    struct QueueNode *link;
} QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
}LinkedQueueType;

int peek(LinkedQueueType *q);
void init(LinkedQueueType *q);
void inqueue(LinkedQueueType *q,int val);
int dequeue(LinkedQueueType *q);

int main(){
    LinkedQueueType q;
    init(&q);

    for(int i=0;i<3;i++) inqueue(&q,i+1);
    for(int i=0;i<3;i++) printf("dequeue value is %d\n",dequeue(&q));
    
    return 0;
}
int is_empty(LinkedQueueType* q){
    if(q->front==NULL){
        return 1;
    }
    return 0;
}

/*초기화 함수*/
void init(LinkedQueueType *q){
    q->front=NULL;
    q->rear=NULL;
}
/*데이터 삽입 함수*/
void inqueue(LinkedQueueType *q,int val){
    /*노드 생성후 데이터 입력*/
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->val=val;
    /*큐가 비었다면 새로 생성*/
    if(is_empty(q)){
        node->link=NULL;
        q->front=node;
        q->rear=node;
    }
    else{
        q->rear->link=node;
        q->rear=node;
        node->link=NULL;
    }
}
/*데이터 삭제 함수*/
int dequeue(LinkedQueueType *q){
    if(is_empty(q)){
        fprintf(stderr,"que is empty\n");
    }
    else{
        QueueNode *p=q->front;
        int val=p->val;
        q->front=p->link;
        if(q->front==NULL) q->rear=NULL;
        free(p);

        return val;
    }
}
int peek(LinkedQueueType *q){
    if(is_empty(q)) {
        fprintf(stderr,"que is empty\n");
        return -1;
    }
    else return q->front->val;
}


