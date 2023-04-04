# 6.8 문제: 시계 맞추기 (문제 ID: CLOCKSYNC, 난이도: 중)

## 문제 변형하기
* 이 문제를 있는 그대로 풀려고 하면 꽤나 복잡해진다.
* 이 문제에서 스위치를 누르는 순서는 전혀 중요하지 않다.
* 완전 탐색 알고리즘을 사용하려면 스위치를 누르는 횟수의 모든 조합을 하나 하나 열거할 수 있어야 하는데, 각 스위치를 몇 번 누르는지는 상관없고 따라서 그 조합의 수는 무한하기 때문이다.
* __시계는 12시간이 지나면 제 자리로 돌아온다는 점을 이용하면 무한한 조합의 수를 유한하게 바꿀 수 있다.__
* 어떤 스위치를 네 번 누르면 연결된 시계는 모두 12시간씩 앞으로 이동하니 하나도 누르지 않은 것과 다름이 없다.
* 따라서 어떤 스위치건 간에 최대 세 번 이상 누를 일이 없다는 것을 알게 되었다.

## 완전 탐색 구현하기
* 문제를 모두 열 조각으로 나눈 후 각 조각에서 한 스위치를 누를 횟수를 정하는 식으로 구현됨.
* 재귀 호출의 깊이가 정해져 있기 때문에 사실 이 코드는 10중 for문과 다르지 않지만, 재귀 호출이 훨씬 구현하기도 편하고 디버깅 하기도 쉽다.

## 코드 6.8
```C++
const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
// linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있다.
// linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않다.
const char linked[SWITCHES][CLOCKS+1] = {
    // 0123456789012345
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    ".xxxxx..........",
    "...xxx...x...x..",
};
// 모든 시계가 12시를 가리키고 있는지 확인한다.
bool areAligned(const vector<int>& clocks);
// swtch번 스위치를 누른다.
void push(vector<int>& clocks, int swtch) {
    for(int clock = 0; clock < CLOCKS; ++clock) 
        if(linked[swtch][clock] == 'x') {
            clocks[clock] += 3;
            if(clocks[clock] == 15) clocks[clock] = 3;
        }
}
// clocks: 현재 시계들의 상태
// swtch: 이번에 누를 스위치의 번호가 주어질 때, 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환한다.
// 만약 불가능하다면 INF 이상의 큰 수를 반환한다.
int solve(vector<int>& clocks, int swtch) {
    if(swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
    // 이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
    int ret = INF;
    for(int cnt = 0; cnt < 4; ++cnt) {
        ret = min(ret, cnt + solve(clocks, swtch + 1));
        push(clocks, swtch);
    }
    // push(clocks, swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
    return ret;
}
```