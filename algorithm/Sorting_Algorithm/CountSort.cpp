#include <iostream>
#include <cstdlib>  //time
#include <ctime>    //rand, srand
#include <string.h> //memset
#include <time.h>   //시간 측정

using namespace std;

#define MAX_ARRAY_SIZE 64

int maxValue=0;

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

int* count_sort(int *array,int arrlen){
    int *c = new int[maxValue+1]; 
    int c_size = maxValue+1;
    int *b = new int[arrlen];

    memset(c,0,c_size*sizeof(int)); //배열c 0으로 초기화

    /*각 숫자 횟수 카운틱하며 c배열 인덱스 값 증가*/
    for(int i = 0; i < arrlen ; i++){
        c[array[i]]++;
    }

    /*배열 c의 인덱스 값 누적합 구하기*/
    for(int i=1; i < c_size; i++){
        c[i] += c[i-1];
    }

    /*배열 A역순으로 훑으며, 배열 C참조하여 정렬*/
    for(int i = arrlen-1; i >= 0; i-- ){
        b[c[array[i]]-1] = array[i];
        --c[array[i]];
    }

    return b;
}

int main(){
    int *array = new int[MAX_ARRAY_SIZE];

    input_random(array,MAX_ARRAY_SIZE);     //배열에 랜덤값 삽입
    delete array;

    start = clock();
    array = count_sort(array,MAX_ARRAY_SIZE);       //계수 정렬
    finish = clock();
    display(array,MAX_ARRAY_SIZE);          //show array
    CalcTime();

    delete array;
    return 0;
}