# 정렬

```
데이터를 오름차순 / 내림차순으로 나열 하는 것.
```
<br>

## ✔ 종류

- [선택 정렬 ( Selection Sort )](#Selection-Sort)
- [버블 정렬 ( Bubble Sort )](#Bubble-Sort)
- [삽입 정렬 ( Insertion Sort )](#Insertion-Sort)
- [셸 정렬 ( Shell Sort )](#Shell-Sort)
- 트리 정렬 ( Tree Sort)
- [퀵 정렬 ( Quick Sort )](#Quick-Sort)
- [힙 정렬 ( Heap Sort )](#Heap-Sort)
- [합병 정렬 ( Merge Sort )](#Merge-Sort)
- 큐브 정렬 ( Cube Sort )
- 팀 정렬 ( Tim Sort )
- [기수 정렬 ( Radix Sort )](#Radix-Sort)
- [계수(카운트) 정렬 ( Count Sort )](#Count-Sort)


<br><br>

## ✔ 시간 복잡도 ( Big-O )
<br>

알고리즘 | 최선 | 평균 | 최악
:---:|:---:|:---:|:---:
선택 정렬 | Ω(n^2) | Θ(n^2) | O(n^2)
버블 정렬 | Ω(n) | Θ(n^2) | O(n^2)
삽입 정렬 | Ω(n) | Θ(n^2) | O(n^2)
트리 정렬 | Ω(nlogn) | Θ(nlogn) | O(n^2)
퀵 정렬 | Ω(nlogn) | Θ(nlogn) | O(n^2)
셸 정렬 | Ω(n) | Θ(n^1.5) | O(n^1.5)
힙 정렬 | Ω(nlogn) | Θ(nlogn) | O(nlogn)
합병 정렬 |Ω(nlogn) | Θ(nlogn) | O(nlogn)
큐브 정렬 | Ω(n) | Θ(nlogn) | O(nlogn)
팀 정렬 | Ω(n) | Θ(nlogn) | O(nlogn)
기수 정렬 | Ω(nk) |  Θ(nk) |  O(nk)
계수 정렬 | Ω(n+k) |  Θ(n+k) |  O(n+k)

------

<Br><br>

## ✔ 공간 복잡도 ( Big-O )
<br>

알고리즘 | 최악
:---:|:---:|
선택 정렬 | O(1) 
버블 정렬 | O(1) 
삽입 정렬 | O(1) 
셸 정렬 | O(1) 
힙 정렬 | O(1)
퀵 정렬 | O(logn) 
합병 정렬 |O(n)
큐브 정렬 | O(n) 
트리 정렬 | O(n)
팀 정렬 | O(n)
계수 정렬 | O(k)
기수 정렬 | O(n+k) 
------

<br><br>

### Selection Sort 

- 추가 메모리 생성할 필요 X
- 배열 쭉 탐색 후 가장 작은 값 왼쪽부터 차곡차곡 쌓는 방식
```cpp
    int min;
    /*배열을 순차 탐색하며 제일 최솟값을 왼쪽부터 정렬*/
    for(int i=0; i<arrlen-1;i++){
        min=i;
        for(int j=i+1;j<arrlen;j++)         
        //최솟값이 들어있는 인덱스 search
            if(array[j]<array[min]) min=j;  
        swap( &array[i], &array[min] );  //가장 작은값을 왼쪽으로 이동     
        
    }
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/SelectionSort.cpp)

<br>

### Insertion Sort 

- 추가 메모리 생성할 필요 X
- 인덱스값을 한개씩 늘려가며 해당 값이 맞는 위치에 삽입
- 상황에 따라 모두 비교하지 않으므로 best case 경우 O(n)으로 빠른 시간을 갖는다.
```cpp
    for(int i=1;i<arrlen;i++){
        item=array[i];

        /*배열의 첫번째 가 아니고, 앞의 값보다 작다면 교체*/
        for(j=i-1;j>=0 && item < array[j] ;j--)
            array[j+1]=array[j];
        array[j+1]=item;
    }
```
 [Code 보기 (c++)](/algorithm/Sorting_Algorithm/InsertionSort.cpp)

<br>

### Bubble Sort

- 추가 메모리 생성할 필요 X
- 배열을 모두 탐색하며 가장 큰 값을 오른쪽부터 쌓는다.

```cpp
    /*한번 탐색할때마다 배열의 끝에 제일 큰 값이 채워지므로 배열의 길이-1만큼 반복문이 돈다*/
        for(int i=arrlen-1;i>0;i--){
            /*배열의 첫번째부터 다음 값과 비교해보면서 큰 값은 점점 뒤로 민다*/
            for(int j=0;j<i;j++)
                if(array[j]>array[j+1]) swap(&array[j],&array[j+1]); 
```
 [Code 보기 (c++)](/algorithm/Sorting_Algorithm/BubbleSort.cpp)

<br>           

### Merge Sort
- `분할과 정복` 원리 ( Divide & Conquer )
- 더이상 나누어지지 않을 때까지 반으로 분할하다가 더이상 나누어지지 않은경우, 원소(value)를 결합(combine)할 때,양쪽의 value를 비교 후 정렬방식대로 combine을 실행한다.
- `재귀`를 이용 ( recursion )
- 추가 메모리가 필요하다.

```cpp
    /*merge (병합) 과정*/
    /*
     * 왼쪽 배열과 오른쪽 배열 비교하며 sorted배열 ( 추가 메모리 공간 )에 삽입
     * 
     * 한쪽먼저 다 sorted에 삽입되었다면 남아 있는 다른쪽 배열 값 sorted 배열에 모두 삽입
     * 
     * sorted의 배열 ( 정렬되어 있는 배열 )을 원래 배열에 복사
     */

    
    void Merge_sort(int array[],int left, int right){
        int mid;
        if(left<right){
            mid = (left+right) /2;
            Merge_sort(array,left,mid);     // 재귀 
            Merge_sort(array,mid+1,right);  // 재귀
            Merge(array,left,mid,right);    // merge (병합)
        }
    }
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/MergeSort.cpp)

<br>

### Quick Sort
- `분할과 정복` 이용 ( Divide & Conquer )
- 분할시 `기준 값 (pivot)`을 설정 후 해당 pivot을 기준으로 좌, 우로 작은, 큰 값을 배치 시킨 후 pivot보다 작은 숫자들, 큰 숫자들의 집합을 다시 재귀 함수를 이용하여 분할 정렬을 하는 방식
- pivot은 기준점으로 중간값이기 때문에 재귀에 포함시키지 않는다.
- pivot을 계속 가장 작은 값 or 가장 큰 값을 설정시 worst case로 O(n^2)이 된다.
- 따라서 `pivot`을 어떻게 잡아서 `partitioning`할지가 중요하다.
- `balanced partitioning` : 좌우가 동일한 사이즈로 나누어지도록 pivot을 설정한 경우 => 가장 좋은 경우

```cpp

/*pivot을 0 ( 시작 점 )으로 설정하였을 경우*/
void QuickSort(int array[],int pivot, int arrlen){
   int left = pivot+1, right = arrlen-1;

    if(pivot>=arrlen-1) return;

    /*right가 left와 같거나 더 작아질때까지*/
    while(left<=right){
        while(left <= arrlen-1 && array[left]<=array[pivot])left++;    //피벗보다 큰 값 왼쪽부터 찾기
        while(right > pivot && array[right]>=array[pivot])right--;   //피벗보다 작은 값 오른쪽부터 찾기
        if(left<right) swap(array[left],array[right]);  //left와 right가 교차하지 않았다면 두 값을 swap

        /*교차 했다면, pivot의 값과 right값을 swap ( 이때 right값은 pivot보다 작은 값을 가리키고 있기 때문이다.)*/
        else swap(array[pivot],array[right]);  
   }
    QuickSort(array,pivot,right);   //pivot의 왼쪽 배열 정렬
    QuickSort(array,right+1,arrlen); //pivot의 오른쪽 배열 정렬
}
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/QuickSort.cpp)

<br>

### Shell Sort 
- 삽입정렬을 보완한 알고리즘 ( 어느정도 정렬된 배열에서 속도가 빠른 것에서 착안 )
- 삽입정렬은 삽입할 때, 이웃한 위치로만 이동이 가능하다는 단점이 있다. -> 이를 보완하여 셀 정렬은 멀리 떨어진 곳을 삽입정렬을 이용하여 정렬한다. 
- 삽입정렬과 다르게 한 번에 정렬하지 않는다.
- 간격을 설정 하여 k번째 요소들을 추출하여 해당 숫자들을 삽입정렬로 정렬 후, k를 절반으로 줄여 1이 될 때까지 반복
- 간격(gap) : 초깃값 = 정렬할 값의 수/2 <br>
생성된 부분 리스트의 개수는 gap과 같다.
```cpp
    void shell_sort(int list[], int n){
        int i, gap;  // gap의 초기 값 : 정렬할 값의 수/2

        for(gap=n/2; gap>0; gap=gap/2){
            if((gap%2) == 0){
                gap++; // gap을 홀수로 만든다.
            }

            // 부분 리스트의 개수는 gap과 같다.
            for(i=0; i<gap; i++){
            // 부분 리스트에 대한 삽입 정렬 수행
            insertion_sort(list, i, n-1, gap);
            }
        }
    }
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/ShellSort.cpp)

<br>

### Heap Sort
- `Heap` 자료구조 ( Complete Binary Tree 의 일종 )을 이용한 정렬 방법
- 배열을 `heapify`( heap으로 만들어 주는 것 ) 을 거쳐서 value를 꺼내는 방식의 정렬
- 추가 메모리 생성이 필요 없다.
- 오름차순 정렬을 위해 최대 힙을 구성하고, 내림차순 정렬을 위해 최소 힙을 구성
```cpp

void HeapSort(int *array, int arrlen){
    heapify(array,arrlen);  //maxHeap형태로 만들어준다.

    for(int i= arrlen-1 ; i>=0; i--){   //가장 큰 숫자(루트)를 맨 뒷 노드로 swap해준다.
        swap(array[i],array[0]);        //swap한 마지막 노드를 제외하고 heapify를 해준다.
        heapify(array,i);               //결과적으로 큰 숫자들이 뒤에 오게 되며 오름차순으로 정렬이 된다.
    }                               
}

```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/HeapSort.cpp)

<br>


### Radix Sort
- `Non-Comparisions` Sorting Algorithm ( 비교하지 않는 정렬 알고리즘 )
- `기수 (Radix)` : 데이터를 구성하는 기본요소
- 하나의 기수마다 버킷 (데이터 공간)을 생성하여 분류하여 버킷안에서 다시 정렬하는 방식
- 정렬 방식
    - `LSD ( Least Significant Digit )` : 덜 중요한 기수부터 정렬 <br>
    예를들어서 일의 자리수자부터 정렬하는 방식이다. 따라서 중간에 정렬 결과를 확인할 수 없다.
    - `MSD ( Most Significant Digit ) `: 가장 중요한 기수부터 정렬 <br>
    예를들어서 백의 자리숫자부터 정렬하는 방식이다. 따라서 중간에 정렬 결과를 확인 할 수있으나 확인하는 과정에서 메모리를 더 사용하게 된다.

```cpp

void RadixSort(int *array,int arrlen){
    int digit=1;
    int k;  //k는 radix(기수 = 각 자리수의 숫자)

    /*배열의 값 중 가장 큰 값의 자릿수 알아내기*/
    while(digit<MAXVALUE)
        digit*=10;
    
    /*가장 큰 값의 자릿수 만큼 만큼 반복*/
    for(int i=1; i<digit ; i*=10){
        /*queue(bucket)에 옮기기*/
        for(int j=0;j<arrlen;j++){
            k=(array[j]/i)%10;      
            q[k].push(array[j]);  //q는 bucket
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
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/RadixSort.cpp)

<br>

### Count Sort
-` Non-Comparisions Sorting Algorithm `( 비교하지 않는 정렬 알고리즘 )
- 좁은 범위의 데이터를 정렬할 때 유용 ( ex. Score )
- 법위가 넓어지게 되면 추가 메모리 공간이 많이 필요해지기 때문에 비효율
- 정렬을 위해 추가 배열을 생성하는데 사이즈를 정렬할 배열의 가장 큰 값만큼 생성해 준다.
- 과정
    - 정렬할 배열 A, 추가 배열 C를 생성해준다.
    - 배열 C는 모든 값을 0으로 초기화해준다.
    - 배열 A의 값을 토대로 배열 C의 인덱스값을 참조하여 값을 1씩올려준다. (예를 들어 배열 A의 값중 3이 있다고 한다면, C의 3번째 인덱스 값을 1더해준다.)
    - 배열 c의 각 값들을 직전 값을 더해 업데이트 해준다. <br>
    (예를 들어, 배열 C가 1,0,2,2 였다면, 1,1,3,5로 업데이트 해준다.)
    - 배열 C는 배열 A의 값들의 인덱스 값이므로, 배열 A를 끝에서부터 역순으로 훑으면서 배열 B에 정렬해 준다. (이때, 한 값을 B에 옮겨주었다면, 해당하는 인덱스의 배열 C의 값은 1을 빼준다.)

```cpp
    int *c = new int[maxValue+1];   //0도 포함한 숫자를 정렬 할 경우 maxValue + 1만큼 생성해주어야 한다.

/*각 숫자 횟수 카운틱하며 c배열 인덱스 값 증가*/
    for(int i = 0; i < a_size ; i++){
        c[a[i]]++;
    }

    /*배열 c의 인덱스 값 누적합 구하기*/
    for(int i=1; i < c_size; i++){
        c[i] += c[i-1];
    }

    /*배열 A역순으로 훑으며, 배열 C참조하여 정렬*/
    for(int i = a_size-1; i >= 0; i-- ){
        b[c[a[i]]-1] = a[i];
        --c[a[i]];
    }
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/CountSort.cpp)
