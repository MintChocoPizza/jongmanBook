// 코드 7.1 1부터 n까지의 합을 구하는 분할 정복 알고리즘

// 필수 조건: n은 자연수
// 1 + 2 + ... + n을 반환한다.
int fastSum(int n) {
    // 기저 사례
    if(n == 1) return 1;
    // 홀수인 입력이 주어질 때는 짝수인 n-1까지의 합을 재귀 호출로 계산하고 n을 더해 답을 구한다.
    if(n % 2 == 1) return fastSum(n-1) + n;
    return 2*fastSum(n/2) + (n/2)*(n/2);
}