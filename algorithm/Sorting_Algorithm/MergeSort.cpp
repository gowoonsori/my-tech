#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
int sorted[64];

//배열의 item을 random으로 삽입
void input_random(int *array,int arrlen){
    srand((unsigned int)time(NULL));
    for(int i=0;i<arrlen;i++){
        array[i]=rand()%100;
    }
}

void display(int *array,int arrlen){
    for(int i=0; i<arrlen;i++){
        cout.width(2);
        cout << i+1 <<". ";
        cout.width(2);
        cout << array[i] << endl;
    }
}

void Merge(int array[],int left,int mid,int right){
    int l;
    int i=left;
    int j=mid+1;
    int k=left;

    /*왼쪽 배열과 오른쪽 배열 비교하며 sorted배열에 삽입*/
    while(i<= mid && j<=right){
        if(array[i]<=array[j])
            sorted[k++]=array[i++];
        else
            sorted[k++]=array[j++];
    }

    /*한쪽먼저 다 sorted에 삽입되어 남아있는 배열 값 모두 삽입*/
    if(i>mid){
        for(l=j;l<=right;l++)
            sorted[k++]=array[l];
    }
    else{
        for(l=i; l<=mid; l++)
            sorted[k++]=array[l];   
    }

    /*배열 복사*/
    for(l=left; l<=right; l++){
        array[l]=sorted[l];
    }
}
void Merge_sort(int array[],int left, int right){
    int mid;
    if(left<right){
        mid = (left+right) /2;
        Merge_sort(array,left,mid);
        Merge_sort(array,mid+1,right);
        Merge(array,left,mid,right);
    }
}


int main(){
    int array[1];
    int arr_sz= sizeof(array)/sizeof(int);
    input_random(array,arr_sz);   //배열에 랜덤값 삽입
    Merge_sort(array,0,arr_sz-1);    //합병 정렬
    display(array,arr_sz);         //show array
}

