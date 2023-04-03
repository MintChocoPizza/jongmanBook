# 수행시간 측정

## 반복문
* 입력의 크기가 작을 때는 반복문 외의 다른 부분들이 갖는 비중이 클 수 있음.
* 입력의 크기가 커지면 커질수록 반복문이 알고리즘의 수행 시간을 지배하게 됨

### 코드 4.1
* 이 알고리즘의 수행 시간은 배열의 크기 N에 따라 변함.
* N번 수행되는 반복문이 두 개 겹쳐져 있으므로, 반복문의 가장 안쪽은 항상 N^2번 실행됨, 따라서 이 알고리즘의 수행 시간은 N^2임.
``` c++
int majority1(const vector<int>& A) {
    int N = A.size();
    int majority = -1, majorityCount = 0;
    for(int i=0; i<N; ++i) {
        // A에 등장하는 A[i]의 수를 센다.
        int V = A[i], count = 0;
        for(int j=0; j<N; ++j) {
            if(A[j] == V) {
                ++count;
            }
        }

        // 지금까지 본 최대 빈도보다 많이 출현했다면 답을 갱신한다.
        if(count > majorityCount) {
            majorityCount = count;
            majority = V;
        }
    }
    return majority;
}
```

### 코드 4.2
* 만약 수의 범위가 작다면 배열을 이용해 각 숫자가 등장하는 횟수를 쉽게 셀 수 있음.
* 그리고 마지막에 빈도수 배열을 순회하면서 최대치의 위치를 찾으면 됨.
* N번 수행되는 반복문과 100번 수행되는 반복문으로 전체 반복문 새행 횟수는 N+100이 된다.
* N이 커지면 커질수록 100번 수행되는 반복문의 비중은 점점 줄어들게 된다.
* 궁극적으로 이 알고리즘의 수행 시간은 N이 된다.
``` c++
int majority2(const vector<int>& A) {
    int N = A.size();
    vector<int> count(101, 0);      // 0~100까지 101개의 원소의 값을 0으로 초기화 하여 생성
    for(int i=0; i<N; ++i) {
        count[A[i]]++;
    }
    // 지금까지 확인한 숫자 중 빈도수가 제일 큰 것을 majority에 저장한다.
    int majority = 0;
    for(int i=1; i<=100; ++i) {
        if(count[i] > count[majority]) {
            majority = i;
        }
    }
    return majority;
}
```
