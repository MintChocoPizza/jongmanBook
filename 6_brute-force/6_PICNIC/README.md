# 문제: 소풍(문제ID: PICNIC, 난이도: 하)

## 완전 탐색
* 가능한 조합의 수를 계산하는 문제를 푸는 가장 간단한 방법은 완전 탐핵을 이용해 모든 조합을 만들어 보는 것이다.
* 재귀 호출을 이용해 문제를 해결하려면 우선 각 답을 만드는 과정을 여러 개의 조각으로 나누어야 한다.

### 코드 6.4 잘못된 재귀 호출 코드
``` C++
int n;
bool areFriends[10][10];
// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
    // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    bool finished = true;
    for(int i=0; i<n; ++i) if(!taken[i]) finished = false;
    if(finished) return 1;
    int ret = 0;

    // 서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            if(!taken[i] && !taken[j] && areFriends[i][j]) {
                taken[i] = taken[j] = true;
                ret += countPairings(taken);
                taken[i] = taken[j] = false;
            }
    return ret;
}
```
#### 위 코드의 문제점 
1. 같은 학생 쌍을 두 번 짝지어 준다. 예를 들어 (0,1)과 (1,0)을 따로 세고 있다.
2. 다른 순서로 학생들을 짝지어 주는 것을 서로 다른 경우로 세고 있다. 예를 들어 (0,1) 후에 (2,3)을 짝지어 주는 것과 (2,3) 후에 (0,1)을 짝지어주는 것은 완전히 같은 방법인데 다른 경우로 세고 있다.

* 실질적으로 같은 답을 중복으로 세는 이런 상황은 경우의 수를 다룰 때 굉장히 흔하게 마주치게 된다.
* 이 상황을 해결하기 위해 선택할 수 있는 좋은 방법은 항상 특정 형태를 갖는 답만을 세는 것이다.
* 흔히 사용하는 방법으로는 같은 답 중에서 사전순으로 가장 먼저 오는 답 하나만을 세는 것이 있다.

### 코드 6.5
```C++
int n;
bool areFriends[10][10];
// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
    // 남은 학생들 중 가장 번호가 빠른 학생을 찾는다.
    int firstFree = -1;
    for(int i=0; i<n; ++i) {
        if(!taken[i]) {
            firstFree = i;
            break;
        }
    }

    // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if(firstFree == -1) return 1;
    int ret = 0;
    // 이 학생과 짝지을 학생을 결정한다.
    for(int pairWith = firstFree+1; pairWith < n; ++pairWith) {
        if(!taken[pairWith] && areFriends[firstFree][pairWith]) {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
    return ret;
}
```
* 사전순으로 가장 먼저 오는 답 하나만을 세기 위하여, 각 단계에서 남아 있는 학생들 중 가장 번호가 빠른 학생의 짝을 찾아준다.
* (1,0) 과 같은 짝이나 (2,3),(0,1)의 순서로 짝을 지어줄 일도 없다.
