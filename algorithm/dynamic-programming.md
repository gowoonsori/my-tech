# DP ( Dynamic Programming , 동적 계획법 )

전체 문제를 작은 문제로 단순화 한 후 점화식으로 만들어 재귀적으로 문제를 해결하는 방법 <br>

( 특정 범위까지의 값을 구하기 위해 그 전의 값들을 이용하여 효율적으로 값을 구하는 방법 )

<br>

## ◼ 대표적인 예 : 피보나치 수열
-----
 피보나치 수열과 같이 이미 계산 한 값인 데 불구하고 재귀를 통하여 여러번 반복하게 되면 굉장히 비효율 적이기 때문에 이미 계산한 값은 저장하여 값을 사용하는 방법이 dp이다.

<br>

### ✔ 피보나치 수열 코드
```cpp
int fibonacci(int n)
  {
    if (n<=2)
      return 1;
    else
      return fibo(n-1) + fibo(n-2);
   }
```
<br>

### ✔ DP로 구현한 피보나치 수열
```cpp
int fibonacci_data[100] = {0,}; //0으로 초기화

int fibonacci(int n)
{
  if (n<=2) 
    return 1;
  if (fibonacci_data[n]==0) //처음 계산된 연산이라면, 그 전 데이터를 이용하여 값 저장
    fibonacci_data[n] = fibonacci(n-1) + fibonacci(n-2);
  return fibonacci_data[n];
}
```
처음 계산된 연산은 새로 저장해두고, 저장해둔 데이터들을 가지고 추가 연산 없이 값을 구하게 된다.

<br>
<br>

## ◼ 구현 방식
### ✔ top-down

<Br>

문제를 위에서 아래로 진행하며 푸는 방식

```cpp
int fibonacci_data[100] = {0,}; //0으로 초기화

int fibonacci(int n)
{
  if (n<=2) 
    return 1;
  if (fibonacci_data[n]==0) //처음 계산된 연산이라면, 그 전 데이터를 이용하여 값 저장
    fibonacci_data[n] = fibonacci(n-1) + fibonacci(n-2);
  return fibonacci_data[n];
}
```

 위에서 보여드린 코드와 같이 값을 메모해 두었다가 필요할 때 꺼내어 사용하는 방식.
 
 <br>

**메모제네이션**
 >동일한 문제를 반복해야 할 경우, 한 번 계산된 결과를 저장해 두었다가 활용하는 방식으로 중복 계산을 줄이는 것을 메모이제이션(Memoization)이라고 한다.

<br>

### ✔ bottom-up

<br>

문제 풀이를 아래에서부터 차곡차곡 저장해 나가며 푸는 방식 ( 상향식 계산법 )
```cpp

int fibonacci_data[100];

int fibonacci(int n)
{
  fibonacci_data[0] = 0;
  fibonacci_data[1] = 1;
  for (int i=2; i<=n; i++){
    fibonacci_data[i] = fibonacci_data[i - 1] + fibonacci_data[i - 2];
  }
  return fibonacci_data[n];
}
```

top-down방식과는 다르게 재귀를 통해 계산한 값을 확인하고 사용하는 것이 아니라 목표하는 n까지 구하기 위해 초기 값 부터 차곡차곡 쌓아가며 푸는 방식이다.

<br>

### ⚡ [DP를 이용한 알고리즘 문제 및 풀이 예 ( bottom-up )](https://gowoonsori.site/solve-algorithm/hopscotch/) 