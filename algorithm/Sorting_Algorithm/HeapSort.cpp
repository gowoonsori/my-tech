#include <iostream>
#include <cstdlib>  //time
#include <ctime>    //rand, srand
#include <time.h>   //시간 측정

using namespace std;

#define MAX_ARRAY_SIZE 64

int maxValue=0;     //가장 큰 값을 담을 변수

clock_t start, finish, used_time=0;    //실행 시간 측정을 위한 변수

//배열의 item을 random으로 삽입
void input_random(int *array,int arrlen){
    srand((unsigned int)time(NULL));
    for(int i=0;i<arrlen;i++){
        array[i]=rand()%99 + 1;
        maxValue = (maxValue < array[i]) ? array[i] : maxValue;   
    }
}

void display(int *array,int arrlen){
    for(int i=0; i<arrlen;i++){
        cout.width(3);
        cout << i+1 <<". ";
        cout.width(2);
        cout << array[i] << endl;
    }
}

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void){
    used_time=finish-start;
    printf("\n*********** result **********\n     time : %lf sec\n", (double)(used_time)/CLOCKS_PER_SEC);
}


void heapify(int* array,int arrlen){

/*인덱스 0을 루트(부모 노드)로 삼고 인덱스 1(왼쪽 자식)부터 maxHeap형태로
 *만들어 주기 위해 swap*/
    for(int i=1; i < arrlen ; i++){
        int child = i;
        while(child > 0){
            int parent = (child -1) /2;

            if(array[parent] < array[child]){
                swap(array[parent],array[child]);
            }
            child = parent;
        }
    }
}

void HeapSort(int *array, int arrlen){
    heapify(array,arrlen);  //maxHeap형태로 만들어준다.

    for(int i= arrlen-1 ; i>=0; i--){
        swap(array[i],array[0]);    //가장 큰 숫자(루트)를 맨 뒷 노드로 swap해준다.
        heapify(array,i);           //swap한 마지막 노드를 제외하고 heapify를 해준다.
    }                               //결과적으로 큰 숫자들이 뒤에 오게 되며 오름차순으로 정렬이 된다.
}

int main(){
    int *array = new int[MAX_ARRAY_SIZE];

    input_random(array,MAX_ARRAY_SIZE);     //배열에 랜덤값 삽입
    start = clock();
    HeapSort(array,MAX_ARRAY_SIZE);         //계수 정렬
    finish = clock();
    display(array,MAX_ARRAY_SIZE);          //show array
    CalcTime();
    
    return 0;
}