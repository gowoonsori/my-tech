#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>

using namespace std;

int maxValue=0;

//배열의 item을 random으로 삽입
void input_random(int *array,int arrlen){
    srand((unsigned int)time(NULL));
    for(int i=0;i<arrlen;i++){
        array[i]=rand()%100;
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


void count_sort(int *array,int arrlen){
    int *c = new int[maxValue+1]; 
    int c_size = (maxValue+1)*sizeof(int);
    int *b = new int[arrlen];

    memset(c,0,c_size);
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
        int val = array[i];
        int &idx = c[val];

        b[idx--] = val;
    }
    array = b;
}

int main(){
   
    int array[64];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);     //배열에 랜덤값 삽입
    count_sort(array,arr_sz);       //계수 정렬
    display(array,arr_sz);          //show array
}