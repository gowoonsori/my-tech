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
    Insertion_sort(array,arr_sz); //삽입 정렬
    display(array,arr_sz);         //show array
    
}