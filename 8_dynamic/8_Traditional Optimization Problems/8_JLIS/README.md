# 8.5 문제: 합친 LIS(문제 ID: JLIS, 난이도: 하)

## 탐욕법으로는 안 된다.

* 이 문제는 LIS 찾기 문제의 확장판 이다. 두 개의 수열에서 고를 수 잇다 뿐이지, 본질적으로는 LIS 찾기 문제와 그다지 다르지 않다.
* 이 문제를 보고 대부분의 사람들이 처음 생각하는 것은, 두 수열의 LIS를 각각 찾은 뒤 이들을 합치면 되지 않을까 하는 것이다. 그러나 안된다.

### 비슷한 문제를 풀어 본 적이 있군요
* 기존에 LIS를 찾는 데 사용했던 알고리즘을 변형해 이 문제를 풀어 보자
* 이렇게 비슷한 문제들은 비슷한 형태의 부분 문제 정의를 써서 풀 수 있는 경우가 많다.
* 수열 $S$의 최대 증가 부분 수열을 찾는 재귀 함수 $lis3()$의 정의는 다음과 같았다.

    $lis3(start) = S[start]$에서 시작하는 최대 증가 부분 수열의 길이

* 이제 수열이 $A, B$ 두 개로 늘었으니 재귀 함수도 두 개의 입력을 받아야한다. 다음과 같은 형태의 재귀 함수를 이용해 문제를 풀 수 있는지 생각해보자.

    $jlis(indexA, indexB) = A[indexA]$ 와 $B{indexB}$에서 시작하는 합친 증가 부분 수열의 최대 길이

* 두 수의 순서는 지정하지 않았으니, $A[indexA]$와 $B[indexB]$ 중 작은 쪽이 앞에 온다고 하자.
* 그러면 이 증가 부분 수열의 다음 숫자는 $A[indexA+1]$ 이후 혹은 $B[indexB+1]$ 이후의 수열 중 $max(A[indexA], B[indexB])$보다 큰 수 중 하나가 된다.
* 그리고 $A[nextA]$를 다음 숫자로 선택했을 경우에 합친 증가 부분 수열의 최대 길이는 $1+jlis(nextA, indexB)$가 된다. 점화식으로 쓰면 다음과 같다.


    $jlis(indexA, indexB) = max\begin{cases} max_{nextA \in NEXT(indexA) }jlis(nextA, indexB)+1 \\ max_{nextB \in NEXT(indexB) } jlis(indexA, nextB) + 1 \end{cases}$

* 이때 $NEXT(indexA)$와 $NEXT(indexB)$는 증가 부분 수열의 다음 위치에 올 수 있는 $A$와 $B$ 원소의 인덱스이다.
* 이러한 아이디어를 구현한 것이 코드 8.13이다. 
* $lis3()$과 같이 $A[-1]=B[-1] = - \infty $로 두고, 이 둘은 항상 $JLIS$에 포함된다고 가정하였다.

## 코드 8.13
```C++
// 입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
// 인위적인 최소치는 64비트여야 한다.

const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache[101][101];
// min(A[indexA], B[indexB]), max(A[indexA], B[indexB])로 시작하는
// 합친 증가 부분 수열의 최대 길이를 반환한다.
// 단 indexA == indexB == -1 혹은 A[indexA] != B[indexB]라고 가정한다.
int jlis(int indexA, int indexB) {
    // 메모이제이션
    int& ret = cache[indexA+1][indexB+1];
    if(ret != -1) return ret;
    // A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있다.
    ret = 2;
    long long a = (indexA == -1 ? NEGINF : A[indexA]);
    long long b = (indexB == -1 ? NEGINF : B[indexB]);
    long long maxElement = max(a, b);
    // 다음 원소를 찾는다.
    for(int nextA = indexA+1; nextA<n; ++nextA)
        if(maxElement < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for(int nextB = indexB+1; nextB<m; ++nextB)
        if(maxElement < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    return ret;
}
```
* 아주 작은 값을 표현하기 위해 64비트 정수인 NEGINF로 쓴 점을 눈여겨보자.
* 문제에는 입력의 번위가 32비트 부호있는 정수 전체라고 나와 있기 때문에 입력에 등장하지 않은 작은 값을 쓰려면 64비트 정수를 써야만 한다.
