#include <iostream>
#include<queue>
#include <cstdlib>  //time
#include <ctime>    //rand, srand
#include <time.h>   //시간 측정

std::queue<int> q[10];   //10진수 정수형을 정렬하기 때문에 0-9의 버킷
int MAXVALUE=0;         //정렬할 수 중 가장 큰 수

clock_t start, finish, used_time=0;    //실행 시간 측정을 위한 변수

void input_random(int *array,int arrlen){
    srand((unsigned int)time(NULL));
    for(int i=0;i<arrlen;i++){
        array[i]=rand()%1000;
        if(MAXVALUE<array[i]) MAXVALUE=array[i];
    }
}

void display(int *array,int arrlen){
    for(int i=0; i<arrlen;i++){
        std::cout.width(3);
        std::cout << i+1 <<". ";
        std::cout.width(2);
        std::cout << array[i] << std::endl;
    }
}

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void){
    used_time=finish-start;
    printf("\n*********** result **********\n     time : %lf sec\n", (double)(used_time)/CLOCKS_PER_SEC);
}

void RadixSort(int *array,int arrlen){
    int digit=1;
    int k;

    /*가장 큰 값의 자릿수 알아내기*/
    while(digit<MAXVALUE)
        digit*=10;
    
    /*가장 큰 값의 자릿수 만큼 만큼 반복*/
    for(int i=1; i<digit ; i*=10){
        /*queue에 옮기기*/
        for(int j=0;j<arrlen;j++){
            k=(array[j]/i)%10;
            q[k].push(array[j]);
        }
        /*array에 옮기기*/
        int idx=0;
        for(int j=0;j<10;j++){
            while(!q[j].empty()){
                array[idx]=q[j].front();
                q[j].pop();
                idx++;
            }
        }

    }
}

int main(){
    int array[64];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);   //배열에 랜덤값 삽입

    start = clock();
    RadixSort(array,arr_sz);
    finish = clock();
    display(array,arr_sz);         //show array
    CalcTime();
    
    return 0;
}