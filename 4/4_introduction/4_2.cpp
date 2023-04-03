// 코드 4.2 주어진 배열에서 가장 많이 등장하는 숫자를 반환하기 2

// A의 각 원소가 0부터 100 사이의 값일 경우 가장 많이 등장하는 숫자를 반환한다.
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
