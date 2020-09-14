#include <iostream>
#include <cstdlib>  //time
#include <ctime>    //rand, srand

using namespace std;
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

//배열의 두 값을 교환
void swap(int *a,int* b){
    int t=*b;
    *b=*a;
    *a=t;
}

//선택 정렬
void Selection_sort(int *array,int arrlen){
    int min;
    /*배열을 순차 탐색하며 제일 최솟값을 왼쪽부터 정렬*/
    for(int i=0; i<arrlen-1;i++){
        min=i;
        for(int j=i+1;j<arrlen;j++)  //최솟값이 들어있는 인덱스 search
            if(array[j]<array[min]) min=j;  
        swap( &array[i], &array[min] );       //가장 작은값을 왼쪽으로 이동
    }
}

int main(){
    int array[64];
    int arr_sz= sizeof(array)/sizeof(int);

    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    Selection_sort(array,arr_sz); //선택 정렬
    display(array,arr_sz);         //show array

}