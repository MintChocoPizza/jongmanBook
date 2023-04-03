# 선형 시간 알고리즘
* 코드 4.4의 수행 시간은 N에 정비례함.
* 입력된 자료를 모두 한 번 훑어보는, 입력의 크기에 비례하는 시간, 즉 선형 시간
* 입력의 크기에 대비해 걸리는 시간을 그래프로 그려 보면 정확히 직선이 됨.
* 이러한 알고리즘을 선형 시간(linear time) 알고리즘이라고 부름

## 이동 평균
* 이동 평균(moving average)은 주식의 가격, 연간 국내 총생산(GDP), 몸무게 등 시간에 따라 변화하는 값들을 관찰할 때 유용하게 사용할 수 있는 통계적 기준치이다.
* 시간에 따라 관찰된 숫자들이 주어질 때 M-이동 평균은 마지막 M개의 관찰 값의 평균으로 정의됨.
* 따라서 새 관찰 값이 나오면 M-이동 평균은 새 관찰 값을 포함하도록 바뀐다.

### 코드 4.3
* 이 코드의 수행 시간은 두개의 for문에 의해 지배됨.
* j를 사용하는 반복문은 항상 M번 실행됨.
* i를 사용하는 반복문은 M-1부터 N-1까지 반복되어 (N-1) - (M-1) + 1 => N-M+1 번 실행됨
* 전체 반복문은 M * (N-M+1) = N * M - M^2 + M번 반복됨

``` C++
vector<double> movingAverage1(const vector<double>& A, int M) {
    vector<double> ret;
    int N = A.size();
    for(int i=M-1; i<N; ++i) {
        // A[i]까지의 이동 평균 값을 구하자.
        double partialSum = 0;
        for(int j=0; j<M; ++j)
            partialSum += A[i-j];
        ret.push_back(partialSum / M);
    }
    return ret;
}
```

### 코드 4.4
* 좀 더 빠른 프로그램 작성의 아이디어 __중복된 계산을 없애는 것__.
* 측정치가 M개는 되어야 이동 평균을 계산할 수 있으니, M-1일 부터 이동 평균을 계산할 수 있음.
* M-1일 부터 매일 M개의 측정치를 계산하는 것은 같은 값은 더하는 __중복된 계산__이 발생함
* M-1일에 구했던 측정치의 합 에서 __0일째에 측정치를 빼고 M일째에 측정치를 더하면__ 중복된 계산 제거
* 하나로 묶여잇던 두 개의 반복문을 분리함.
* 반복문 수행 횟수는 M-1 + {(N-1) - (M-1) + 1} == M-1 + (N-M+1) == N 이 된다.

``` C++
vector<double> movingAverage2(const vector<double>& A, int M) {
    vector<double> ret;
    int N = A.size();
    double partialSum = 0;
    for(int i=0; i<M-1; ++i) 
        partialSum += A[i];
    for(int i=M-1; i<N; ++i) {
        partialSum += A[i];
        ret.push_back(partialSum / M);
        partialSum -= A[i-M+1];
    }
    return ret;
}
```
