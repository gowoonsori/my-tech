# 정렬
------
```
데이터를 오름차순 / 내림차순으로 나열 하는 것.
```

## :heavy_check_mark: 종류

- 선택 정렬 ( Selection Sort )
- 삽입 정렬 ( Insertion Sort )
- 버블 정렬 ( Bubble Sort )
- 셸 정렬 ( Shell Sort )
- 퀵 정렬 ( Quick Sort )
- 힙 정렬 ( Heap Sort )
- 합병 정렬 ( Merge Sort )
- 기수 정렬 ( Radix Sort )
- 계수(카운트) 정렬 ( Count Sort )


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
### 선택 정렬

- 추가 메모리 생성할 필요 X
- 배열 쭉 탐색 후 가장 작은 값 왼쪽부터 차곡차곡 쌓는 방식
```
    int min;
    /*배열을 순차 탐색하며 제일 최솟값을 왼쪽부터 정렬*/
    for(int i=0; i<arrlen-1;i++){
        min=i;
        for(int j=i+1;j<arrlen;j++)         //최솟값이 들어있는 인덱스 search
            if(array[j]<array[min]) min=j;  
        swap( &array[i], &array[min] );       //가장 작은값을 왼쪽으로 이동
    }
```

### 삽입 정렬

- 추가 메모리 생성할 필요 X
- 인덱스를 한개씩 늘려가며 해당 값이 맞는 위치에 삽입
- 상황에 따라 모두 비교하지 않으므로 O(n)으로 빠른 시간을 갖는다.
```
    for(int i=1;i<arrlen;i++){
        item=array[i];

        /*배열의 첫번째 가 아니고, 앞의 값보다 작다면 교체*/
        for(j=i-1;j>=0 && item < array[j] ;j--)
            array[j+1]=array[j];
        array[j+1]=item;
    }
```
 
### 버블 정렬

- 추가 메모리 생성할 필요 X
- 배열을 모두 탐색하며 가장 큰 값을 오른쪽부터 쌓는다.

```
    /*한번 탐색할때마다 배열의 끝에 제일 큰 값이 채워지므로 배열의 길이-1만큼 반복문이 돈다*/
        for(int i=arrlen-1;i>0;i--){
            /*배열의 첫번째부터 다음 값과 비교해보면서 큰 값은 점점 뒤로 민다*/
            for(int j=0;j<i;j++)
                if(array[j]>array[j+1]) swap(&array[j],&array[j+1]); 
```
            