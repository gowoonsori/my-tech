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

void Insertion_sort(int *array,int arrlen){

    
    int j,item;
    for(int i=1;i<arrlen;i++){
        item=array[i];

        /*배열의 첫번째 가 아니고, 앞의 값보다 
        작다면 교체*/
        for(j=i-1;j>=0 && item < array[j] ;j--)
            array[j+1]=array[j];
        array[j+1]=item;
        
        
    }
}

int main(){
    int array[64];
    int arr_sz= sizeof(array)/sizeof(int);

    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    start = clock();
    Insertion_sort(array,arr_sz); //삽입 정렬
    finish = clock();
    display(array,arr_sz);         //show array
    CalcTime();

    return 0;
}