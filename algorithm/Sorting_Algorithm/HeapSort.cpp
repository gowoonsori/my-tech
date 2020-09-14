#include <iostream>
#include <cstdlib>  //time
#include <ctime>    //rand, srand

using namespace std;

#define MAX_ARRAY_SIZE 64

int maxValue=0;


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

void HeapSort(int *array, int arrlen){
    
}

int main(){
    int *array = new int[MAX_ARRAY_SIZE];

    input_random(array,MAX_ARRAY_SIZE);     //배열에 랜덤값 삽입
    HeapSort(array,MAX_ARRAY_SIZE);       //계수 정렬
    display(array,MAX_ARRAY_SIZE);          //show array
}