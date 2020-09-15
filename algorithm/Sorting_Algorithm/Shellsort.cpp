#include <iostream>
#include <cstdlib>  //time
#include <ctime>    //rand, srand
#include <time.h>   //시간 측정

using namespace std;

clock_t start, finish, used_time=0;    //실행 시간 측정을 위한 변수

//배열의 item을 random으로 삽입
void input_random(int *array,int arrlen){
    srand((unsigned int)time(NULL));
    for(int i=0;i<arrlen;i++){
        array[i]=rand()%100;
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

/*기본은 삽입정렬 알고리즘
gap차이만큼의 숫자들을 삽입정렬로 정렬*/
void insertionSort(int *array,int first,int last,int gap){
    int item,j;
    for(int i=first+gap; i<last ; i+=gap ){
        item=array[i];
        /*배열의 제일 왼쪽이거나 앞의 값이 해당 값보다 작다면 배열을 한 칸씩 뒤로 미룸*/
        for(j=i-gap; j>=first && array[j]>item; j-=gap)  
            array[j+gap]=array[j];
        array[j+gap]=item;
    }
}


void Shell_sort(int *array,int arrlen){
    int gap;
    for( gap = arrlen/2 ; gap>0; gap/=2){
        if(gap%2 == 0) gap++;         //gap이 짝수라면 홀수로 맞추는 것이 더 좋은 것으로 분석이 됨
        
        for(int i=0;i<gap;i++){
            insertionSort(array,i,arrlen,gap);
        }
    }
}



int main(){
    int array[64];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    
    start = clock();
    Shell_sort(array,arr_sz); //삽입 정렬
    finish = clock();
    display(array,arr_sz);         //show array
    CalcTime();

    return 0;
}