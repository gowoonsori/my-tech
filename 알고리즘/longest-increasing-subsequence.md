# 최장 증가 수열 (Longes Increasing Subsequence)

주어진 수열에서 오름차순으로 정렬된 가장 긴 부분 수열.

예를 들어, `341256784134`라는 수열에서 LIS는 `345678` or `125678` 이 된다.

<br><br>

## 찾는 방법

찾는 방법은 [나무위키](https://namu.wiki/w/%EC%B5%9C%EC%9E%A5%20%EC%A6%9D%EA%B0%80%20%EB%B6%80%EB%B6%84%20%EC%88%98%EC%97%B4) 예시를 표와 함께 잘 설명해있다.

아래는 간단하게 두가지 방법을 요약해봤다.

lis크기 구하는 방법은 dp와 이분탐색에 따라 방법이 나뉘며 경로 추적(trace)방법은
두 방법 모두 인덱스를 가리키는 배열을 하나 추가하여, 탐색하면서 해당 값의 앞의 수열 인덱스를 저장하는 방법으로 구현한다.

이 배열을 가지고 가장 큰 부분순열을 갖는 값부터 역 추적하며 순열을 구한다. (원소를 구한다.)

<br>

## O(n^2)

---

`dp`를 이용해 찾는 방법이다.

현재 위치의 수를 끝으로 하는 최장 증가 수열의 값을 dp에 저장하는 방법

수열의 첫번째부터 끝까지 반복하며, 현재 위치보다 앞의 수들을 모두 비교하기 때문에 O(n^2)만큼 걸린다.

<br>

### 소스 코드

- lis 크기 구하기

```cpp
void lis_dp(string str) {
    vector<int> dp(str.length(), 0);              //해당 index의 값을 끝으로 하는 가장 긴 수열의 값 저장

    for (int i = 0; i <= str.length(); i++) {
        dp[i] = 1;  //처음값은 1로 시작
        for (int j = 0; j < i; j++) {
            if (str[i] > str[j] && dp[j] + 1 > dp[i]) {  //현재 위치의 앞의값중 가장 긴 수열의 길이 find
                dp[i] = dp[j] + 1;
            }
        }
    }
    cout << "\nmax length : " << max << endl << "Subsequence : ";

}
```

<br>

- lis 원소 구하기 (trace)

```cpp
void lis_dp(string str) {
    vector<int> dp(str.length(), 0);              //해당 index의 값을 끝으로 하는 가장 긴 수열의 값 저장
    vector<int> backtrace_idx(str.length(), -1);  //수열의 이전 값의 index값, -1이 처음 값
    vector<char> lis;                             //최장 증가 수열 값 trace
    int max = 0, idx;

    for (int i = 0; i <= str.length(); i++) {
        dp[i] = 1;  //처음값은 1로 시작
        for (int j = 0; j < i; j++) {
            if (str[i] > str[j] && dp[j] + 1 > dp[i]) {  //현재 위치의 앞의값중 가장 긴 수열의 길이 find
                dp[i] = dp[j] + 1;
                backtrace_idx[i] = j;  // trace 추적 위해
            }
        }
        // trace 추적위해
        if (dp[i] > max) {
            max = dp[i];
            idx = i;
        }
    }

    cout << "\nmax length : " << max << endl << "Subsequence : ";
    ;

    /*최장 증가 수열 처음 부분까지 역 추적하며 vector에 추가*/
    for (int i = idx; i >= 0; i = backtrace_idx[i]) {
        lis.push_back(str[i]);
    }

    reverse(lis.begin(), lis.end());  //큰 값부터 추가했으므로 reverse

    for_each(lis.begin(), lis.end(), [](char c) { cout << c << " "; });  // print
}
```

<br><br>

## O(nlgn)

---

`이분탐색`을 이용하는 방법으로 추가배열에 최장 증가 수열의 값을 저장하는 방법이다.

배열의 인덱스가 수열의 길이를 나타내고, 인덱스의 값은 인덱스만큼의 길이의 수열을 갖는 값을 나타낸다.

추가배열에 마지막값보다 탐색한 현재 값이 더 크다면 배열 마지막에 값을 추가해준다.
<br>_(부분수열의 크기를 1증가 시켜주는 것)_

탐색한 현재 값이 마지막 값보다 작다면, 추가배열에서 현재값보다 작은값들 중 가장 큰 값을 현재값으로 갱신해준다.
<br>_(이때 나오는 현재값보다 작은값들 중 가장 큰 값을 **lower bound**라고 한다)_

추가 배열은 항상 오름차순으로 정렬되어있으므로, `이분 탐색`으로 탐색이 가능하기 때문에 O(nlgn)이 된다.

<br>

- lis 크기 구하기

```cpp
void lis_bs(string str) {
    /*부분 수열 자리수에 해당하는 value값 담기 위한 배열*/
    vector<pair<char, int>> arr;                  // first = value,

    for (int i = 0; i < str.length(); i++) {
        //첫번째 값이거나 현재 값이 arr의  마지막 값보다 크다면 새로 추가 ==> 최장 증가 수열의 크기 1증가
        if (arr.empty() || arr.back().first < str[i]) {
            arr.push_back({str[i], i});
        }
        //현재 값이 arr 마지막 값보다 작다면, lis의 크기 증가는 안된다. lower bound의 값 갱신
        else {
            auto it = lower_bound(arr.begin(), arr.end(), make_pair(str[i], i), cmp);
            *it = {str[i], i};
        }
    }

    cout << "\nmax length : " << arr.size() << endl << "Subsequence : ";
}
```

<br>

-lis 원소 구하기 (trace)

```cpp
void lis_bs(string str) {
    /*부분 수열 자리수에 해당하는 value값 담기 위한 배열*/
    vector<pair<char, int>> arr;                  // first = value, second = idx ==> 배열의 길이가 lis 크기다.
    vector<int> backtrace_idx(str.length(), -1);  //수열의 이전 값의 index값, -1이 처음 값
    vector<char> lis;                             //최장 증가 수열 값 trace

    for (int i = 0; i < str.length(); i++) {
        //첫번째 값이거나 현재 값이 arr의  마지막 값보다 크다면 새로 추가 ==> 최장 증가 수열의 크기 1증가
        if (arr.empty() || arr.back().first < str[i]) {
            if (!arr.empty()) backtrace_idx[i] = arr.back().second;  //최장 증가 수열값 trace
            arr.push_back({str[i], i});
        }
        //현재 값이 arr 마지막 값보다 작다면, lis의 크기 증가는 안된다. lower bound의 값 갱신
        else {
            auto it = lower_bound(arr.begin(), arr.end(), make_pair(str[i], i), cmp);
            if (it != arr.begin()) backtrace_idx[i] = (it - 1)->second;  // lis 값 trace ==> lower bound 위치가 맨 앞이라면 수행 x
            *it = {str[i], i};
        }
    }

    cout << "\nmax length : " << arr.size() << endl << "Subsequence : ";

    //*최장 증가 수열 처음 부분까지 역 추적하며 vector에 추가*/
    for (int i = arr.back().second; i >= 0; i = backtrace_idx[i]) {
        lis.push_back(str[i]);
    }
    reverse(lis.begin(), lis.end());                                     //큰 값부터 추가했으므로 reverse
    for_each(lis.begin(), lis.end(), [](char c) { cout << c << " "; });  // print
}
```
