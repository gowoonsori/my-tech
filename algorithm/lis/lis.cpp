#include <bits/stdc++.h>

using namespace std;

void lis_dp(string);
void lis_bs(string);

bool cmp(const pair<char, int> &a, const pair<char, int> &b) { return a.first < b.first; }

int main() {
    string str = "35792148";

    // lis_dp(str);
    lis_bs(str);

    return 0;
}

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
