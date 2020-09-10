# 정렬

```
데이터를 오름차순 / 내림차순으로 나열 하는 것.
```
<br>

## ✔ 종류

- 선택 정렬 ( Selection Sort )
- 삽입 정렬 ( Insertion Sort )
- 버블 정렬 ( Bubble Sort )
- 셸 정렬 ( Shell Sort )
- 퀵 정렬 ( Quick Sort )
- 힙 정렬 ( Heap Sort )
- 합병 정렬 ( Merge Sort )
- 기수 정렬 ( Radix Sort )
- 계수(카운트) 정렬 ( Count Sort )

<br><br>

## ✔ 시간 복잡도 ( Big-O )
<br>

알고리즘 | 최선 | 평균 | 최악
:---:|:---:|:---:|:---:
선택 정렬 | O(n^2) | O(n^2) | O(n^2)
버블 정렬 | O(n^2) | O(n^2) | O(n^2)
삽입 정렬 | O(n) | O(n^2) | O(n^2)
셸 정렬 | O(n) | O(n^1.5) | O(n^1.5)
퀵 정렬 | O(nlogn) | O(nlogn) | O(n^2)
힙 정렬 | O(nlogn) | O(nlogn) | O(nlogn)
합병 정렬 |O(nlogn) | O(nlogn) | O(nlogn)
기수 정렬 | O(dn) |  O(dn) |  O(dn)
계수 정렬 | O(dn) |  O(dn) |  O(dn)

------
<Br><br>


### 선택 정렬 ( Selection Sort )

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

### 삽입 정렬 ( Insertion Sort )

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

### 버블 정렬 ( Bubble Sort )

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

### 합병 정렬 ( Merge Sort )
- `분할과 정복` 원리 ( Divide & Conquer )
- 더이상 나누어지지 않을 때까지 반으로 분할하다가 더이상 나누어지지 않은경우, 원소(value)를 결합(combine)할 때,양쪽의 value를 비교 후 정렬방식대로 combine을 실행한다.
- `재귀`를 이용 ( recursion )
- 추가 메모리가 필요하다.

```cpp
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/MergeSort.cpp)

<br>

### 퀵 정렬 ( Quick Sort )
- `분할과 정복` 이용 ( Divide & Conquer )
- 분할시 `기준 값 (pivot)`을 설정 후 해당 pivot을 기준으로 좌, 우로 작은, 큰 값을 배치 시킨 후 pivot보다 작은 숫자들, 큰 숫자들의 집합을 다시 재귀 함수를 이용하여 분할 정렬을 하는 방식
- pivot은 기준점으로 중간값이기 때문에 재귀에 포함시키지 않는다.
- pivot을 계속 가장 작은 값 or 가장 큰 값을 설정시 worst case로 O(n^2)이 된다.


```cpp
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/QuickSort.cpp)

<br>

### 셀 정렬 ( Shell Sort )
-

```cpp
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/ShellSort.cpp)

<br>

### 힙 정렬 ( Heap Sort )
- `Heap` 자료구조 ( BST 의 일종 )을 이용한 정렬 방법
- 배열을 `heapify`( heap으로 만들어 주는 것 ) 을 거쳐서 value를 꺼내는 방식의 정렬

```cpp
```



### 기수 정렬 ( Radix Sort )
- `Non-Comparisions` Sorting Algorithm ( 비교하지 않는 정렬 알고리즘 )
- `기수 (Radix)` : 데이터를 구성하는 기본요소
- 데이터의 길이가 동일한 데이터만 정렬이 가능하다.
- 하나의 기수마다 버킷 (데이터 공간)을 생성하여 분류하여 버킷안에서 다시 정렬하는 방식
- 정렬 방식
    - `LSD ( Least Significant Digit )` : 덜 중요한 기수부터 정렬 <br>
    예를들어서 일의 자리수자부터 정렬하는 방식이다. 따라서 중간에 정렬 결과를 확인할 수 없다.
    - `MSD ( Most Significant Digit ) `: 가장 중요한 기수부터 정렬 <br>
    예를들어서 백의 자리숫자부터 정렬하는 방식이다. 따라서 중간에 정렬 결과를 확인 할 수있으나 확인하는 과정에서 메모리를 더 사용하게 된다.

```cpp
```
[Code 보기 (c++)](/algorithm/Sorting_Algorithm/RadixSort.cpp)

<br>

### 카운트 정렬 ( Count Sort )
-` Non-Comparisions Sorting Algorithm `( 비교하지 않는 정렬 알고리즘 )
- 좁은 범위의 데이터를 정렬할 때 유용 ( ex. Score )

```cpp
```
