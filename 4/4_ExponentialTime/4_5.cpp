// 코드 4.5 음식 메뉴 정하기

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
