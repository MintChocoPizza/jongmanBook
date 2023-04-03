# 지수 시간 알고리즘 

## 다항 시간 알고리즘
* 변수 N과 N^2, 그 외 N의 거듭제곱들의 선형 결합으로 이루어진 식들을 다항식 이라고 부른다.
* 반복문의 수행 횟수를 입력 크기의 다항식으로 표현할 수 있는 알고리즘들을 다항 시간 알고리즘이라고 부른다.

### 코드 4.5
#### 알러지가 심한 친구들
* 여러 개의 답이 있고 그중 가장 좋은 답을 찾는 문제들을 풀 때 가장 간단한 방법은 모든 답을 일일이 고려해 보는 것이다.
* 이러한 모든 경우를 탐색하는 알고리즘을 구현하는 가장 쉬운 방법은 재귀 호출을 이용하는 것이다.
* M가지 음식을 만든다/ 안만든다 2가지 선택지가 있으니, 2^M가지의 경우의 수가 있다.
* 이와 같이 N이 하나 증가할 때마다 걸리는 시간이 배로 증가하는 알고리즘들은 지수 시간(exponential time)에 동작한다고 말한다.
* 

``` C++
const int INF = 987654321;
// 이 메뉴로 모두가 식사할 수 있는지 여부를 반환한다.
bool canEverybodyEat(const vector<int>& menu);
// 요리할 수 있는 음식의 종류 수
int M;
// food 번째 음식을 만들지 여부를 결정한다.
int selectMenu(vector<int>& menu, int food) {
    // 기저 사례: 모든 음식에 대해 만들지 여부를 결정했을 때
    if(food == M) {
        if(canEverybodyEat(menu)) return menu.size();
        // 아무것도 못 먹는 사람이 있으면 아주 큰 값을 반환한다.
        return INF;
    }
    // 이 음식을 만들지 않는 경우의 답을 계산한다.
    int ret = selectMenu(menu, food+1);
    // 이 음식을 만드는 경우의 답을 계산해서 더 작은 것을 취한다.
    menu.push_back(food);
    ret = min(ret, selectMenu(menu, food+1));
    menu.pop_back();
    return ret;
}
```

