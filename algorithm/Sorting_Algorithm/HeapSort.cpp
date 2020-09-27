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

/*top-down*/
void top_down_heapify(int* array,int arrlen){
/*인덱스 0을 루트(부모 노드)로 삼고 인덱스 1(왼쪽 자식)부터 maxHeap형태로
 *만들어 주기 위해 swap 
 */
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

/*bottom-up*/
void bottom_up_heapify(int* array,int parent,int arrlen){
/*인덱스 0을 루트(부모 노드)로 삼고 인덱스 1(왼쪽 자식)부터 maxHeap형태로
 *만들어 주기 위해 swap */ 
    while(parent <= arrlen){
        int largest = parent;
        int l = parent * 2 + 1;
        int r = parent * 2 + 2;

        if(l < arrlen && array[largest] < array[l]){
            largest = l;
        }
        if(r < arrlen && array[largest] < array[r]){
            largest = r;
        }

        /*largest가 값이 바뀌었다면 swap해야한다는 뜻
        swap했다면 child로 내려가 아래 서브트리도 확인하기 위해
        parent값 largest로 변환 */
        if(largest != parent) {
            swap(array[parent],array[largest]); 
            parent = largest;
        }
        else parent = l;
    }
}

void top_down_HeapSort(int *array, int arrlen){
    top_down_heapify(array,arrlen);  //maxHeap형태로 만들어준다.

    for(int i= arrlen-1 ; i>=0; i--){
        swap(array[i],array[0]);    //가장 큰 숫자(루트)를 맨 뒷 노드로 swap해준다.
        top_down_heapify(array,i);           //swap한 마지막 노드를 제외하고 heapify를 해준다.
    }                               //결과적으로 큰 숫자들이 뒤에 오게 되며 오름차순으로 정렬이 된다.
}

void bottom_up_HeapSort(int *array, int arrlen){
    /*build max-heap
        루트 노드가 0 기준 ) n개의 노드를 가진 트리라면, 
                            마지막 노드 n의 부모 인덱스 번호는 n/2 -1 이다.

        루트 노드가 1 기준 )  n개의 노드를 가진 트리라면,
                            마지막 노드 n의 부모 인덱스 번호는 n/2  이다.
        leafnode들은 더이상 heapify를 안해줘도 되기 때문에 마지막 노드의 부모 노드 부터 
        heapify를 시작

        --> heap sort의 초반 build heap부분에서 bottom-up방식은 n/2개만 큼만 수행하므로
        top-down방식보다 bottom-up 방식이 조금 더 성능이 좋다.
    */
    for(int i= arrlen / 2 - 1; i >= 0; i--){
        bottom_up_heapify(array,i,arrlen);
    }

    for(int i = arrlen-1; i >= 0; i--){
        swap(array[i],array[0]);                //가장 큰 숫자(루트)를 맨 뒷 노드로 swap해준다.
        bottom_up_heapify(array,0,i);           //swap한 마지막 노드를 제외하고 heapify를 해준다.
    }
}



int main(){
    int *array = new int[MAX_ARRAY_SIZE];

    input_random(array,MAX_ARRAY_SIZE);     //배열에 랜덤값 삽입
    start = clock();
    bottom_up_HeapSort(array,MAX_ARRAY_SIZE);         //계수 정렬
    finish = clock();
    display(array,MAX_ARRAY_SIZE);          //show array
    CalcTime();
    
    return 0;
}