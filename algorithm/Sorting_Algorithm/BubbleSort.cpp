#include<iostream>
#include<cstdlib>
#include<ctime>

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

void swap(int *a,int* b){
    int t=*b;
    *b=*a;
    *a=t;
}

void Bubble_sort(int *array,int arrlen){

    /*한번 탐색할때마다 배열의 끝에 제일 큰 값이 채워지므로 
    배열의 길이-1만큼 반복문이 돈다*/
    for(int i=arrlen-1;i>0;i--){
        /*배열의 첫번째부터 다음 값과 비교해보면서
        큰 값은 점점 뒤로 민다*/
        for(int j=0;j<i;j++)
            if(array[j]>array[j+1]) swap(&array[j],&array[j+1]); 
    }
}

int main(){
   
 int array[64];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    Bubble_sort(array,arr_sz);    //버블 정렬
    display(array,arr_sz);         //show array
}