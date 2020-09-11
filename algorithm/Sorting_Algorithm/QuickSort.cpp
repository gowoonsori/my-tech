#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

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
void swap(int &a,int &b){
    int tmp=b;
    b=a;
    a=tmp;
}

void QuickSort(int array[],int pivot, int arrlen){
   int left = pivot+1, right = arrlen-1;

    if(pivot>=arrlen-1) return;
    while(left<=right){
        while(left <= arrlen-1 && array[left]<=array[pivot])left++;    //피벗보다 큰 값 왼쪽부터 찾기
        while(right > pivot && array[right]>=array[pivot])right--;   //피벗보다 작은 값 오른쪽부터 찾기
        if(left<right) swap(array[left],array[right]);
        else swap(array[pivot],array[right]);
   }
    QuickSort(array,pivot,right);
    QuickSort(array,right+1,arrlen);
}

int main(){
   
 int array[64];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    QuickSort(array,0,arr_sz);    //버블 정렬
    display(array,arr_sz);         //show array
}