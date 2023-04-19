// 코드 8.5 외발 뛰기 문제를 히결하는 동적 계획법 알고리즘

int n, board[100][100];
int cache[100][100];
int jump2(int y, int x) {
    // 기저 사례 처리
    if(y >= n || x >= n) return 0;
    if(y == n-1 || x == n-1) return 1;
    // 메모이제이션
    int& ret = cache[y][x];
    if(ret != -1) return ret;
    int jumpSize = board[y][x];
    return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}