# 예제: 삼각형 위의 최대 경로(문제 ID: TRIANGLEPATH, 난이도: 하) [here](#1)

## 완전 탐색으로 시작하기
* 가장 먼저 완전 탐색을 통해 이 문제를 해결해 보자
* 경로를 각 가로줄로 조각 낸 뒤, 각 조각에서는 아래로 내려갈지 오른쪽으로 내려갈지를 선택하면서 모든 경로를 만들기로 하자.
* 이때 재귀 호출 함수에는 현재 위치와 지금까지 만난 숫자들의 합을 전달하도록 하겠습니다.
* 그러면 다음과 같은 부분 문제를 얻을 수 있다.
    
    $pathSum(y, x, sum)=$ 현재 위치가 $(y, x)$이고, 지금까지 만난 수의 합이 $sum$일 때, 이 경로를 맨 아래줄까지 연장해서 얻을 수 있는 최대 합을 반환한다.

    이때 아래쪽으로 내려갔을 때와 오른쪽으로 내려갔을 때의 최대 합을 각각 $path()$를 이용해 표현하면 다음과 같은 __점화식__ 을 얻을 수 있다.
    
    $path1(y,x,sum) = max \begin{cases} patch(y+1, x, sum+triangle[y][x]) \\ patch(y+1, x+1, sum+triangle[y][x]) \end{cases} $

## 무식하게 메모이제이션 적용하기
* 앞에서 정의한 점화식은 답을 구하기 위해 모든 경로를 다 만들어 봐야 한다는 심각한 문제가 있다.
* 이 문제에서 가능한 경로의 개수는 삼각형의 가로줄이 하나 늘어날 때마다 두 배씩 늘어나기 때문에 n개의 가로줄이 있을 때 가능한 경로의 수는 $s^{n-1}$이 된다.
* $ n \le 20$ 정도라면 계산 가능한 분량이지만, $n$의 최대치가 100이라면 도저히 계산할 수 없다. 이때 메모이제이션을 적용하면 좋다.

## 코드 8.8
```C++
// MAX_NUMBER: 한 칸에 들어갈 숫자의 최대치
int n, triangle[100][100];
int cache[100][100][MAX_NUMBER*100+1];
// (y, x) 위치까지 내려오기 전에 만난 숫자들의 합이 sum 일 때
// 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로를 반환한다.
int path1(int y, int x, int sum) {
    // 기저 사례: 맨 아래 줄까지 도달했을 경우
    if(y == n-1) return sum + triangle[y][x];
    // 메모이제이션
    int& ret = cache[y][x][sum];
    if(ret != -1) return ret;
    sum += triangle[y][x];
    return ret = max(path1(y+1, x+1, sum), path1(y+1, x, sum));
}
```
* 코드 8.8은 아까의 점화식을 구현한 완전 탐색에 메모이제이션을 적용한 것이다.
* 이 코드는 멀쩡해 보이지만 큰 문제가 있다.
* 첫 번째 문제는 사용해야 하는 메모리가 너무 크다는 것이다. 배열의 크기가 입력으로 주어지는 숫자의 범위에 좌우된다.
* 또 다른 문제는 $path1()$이 특정 입력에 대해서는 완전 탐색처럼 동작한다는 것이다. 
    
    $2^i$꼴의 숫자로만 구성된 삼각형이 있다고 하면, 이때 서로 다른 경로는 합도 항상 다르다. 똑같은 (y,x)위치까지 내려왔다고 해도 경로마다 다 다른 합을 가지니 같은 계산을 두 번 할 일이 없다. 이래서는 완전 탐색과 다를 바가 없다.

## 입력 걸러내기
이 알고리즘을 더 빠르게 하는 힌트는 재귀 함수의 입력을 다음과 같이 두 부류로 나눠 보면 얻을 수 있다.
    
    1. y와 x는 재귀 호출이 풀어야 할 부분 문제를 지정합니다. 이 두 입력이 정해지면 앞으로 우리가 만들 수 있는 경로들이 정해지죠. 따라서 이들은 앞으로 풀어야 할 조각들에 대한 정보를 주는 입력들입니다.
    2. 반면 sum은 지금까지 어떤 경로로 이 부분 문제에 도달했는지를 나타냅니다. sum은 지금까지 풀었던 조각들에 대한 정보를 주는 입력이지요.

$ \underbrace{[0] \space [1] \cdots [y-1]}_{\text{이미 해결한 조각들}} \space \underbrace{[y] \space [y+1] \cdots [n-2] \space [n-1]}_{\text{아직 해결하지 못한 조각들}} $

* 다시 말하면 $(y, x)$는 그림 오른쪽에 아직 해결하지 못한 조각들을 정의하는 입력이고, $sum$은 왼쪽에 이미 결정한 조각들에 대한 정보이다.
* 그런데 과연 $sum$이 앞으로 남은 조각들을 푸는 데 필요할까요? $(y, x)$에서 맨 아래줄까지 내려가는 최대 경로는 $sum$이 얼마건 상관 없이 똑같습니다. 재귀 함수에 $sum$을 아예 입력으로 받지 않도록 하면 이 알고리즘은 훨씬 빨라질 겁니다. 
* 단 재귀 함수에서 $sum$을 입력으로 받지 않으면, 이전가지 어떤 숫자를 만났는지 알 수 없기 때문에 전체 경로의 최대 합을 반환할 수가 없다.
* 따라서 함수의 반환 값을 전체 경로의 최대치가 아니라 $(y, x)$에서 시작하는 부분 경로의 최대치로 바꿀 필요가 있다.
* 결과적으로 다음과 같은 부분 문제를 얻을 수 있다.

$path2(y,x) = (y,x)$에서 시작해서 맨 아래줄까지 내려가는 부분 경로의 최대 합을 반환한다.

* 전체 경로의 최대 합을 반환하는 것이 아니라 부분 경로의 최대합을 반환한다는 데 유의해야한다.
* 다시 말해 $path2()$는 앞으로 남은 조각들의 결과만을 반환한다.
* $path2()$의 동작은 다음과 같은 점화식으로 정의할 수 있다.

    $path2(y,x) = triangle[y][x] + max\begin{cases} patch2(y+1, x) \\ patch2(y+1, x+1) \end{cases}$

## 코드 8.9
```C++
int n, triangle[100][100];
int cache2[100][100];
// (y, x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x) {
    // 기저 사례
    if(y == n-1) return triangle[y][x];
    // 메모이제이션
    int& ret = cache2[y][x];
    if(ret != -1) return ret;
    return ret = max(path2(y+1, x), path2(y+1, x+1)) + triangle[y][x];
}
```
* 코드 8.9는 이런 새로운 점화식을 이용한 알고리즘을 보여준다. 
* 이 알고리즘에서 부분 문제의 수는 $O(n^2)$이고 각 부분 문제를 계산하는 데는 상수 시간밖에 안 걸리기 때문에 전체 시간 복잡도는 $O(n^2)$이 된다.

## 이론적 배경: 최적 부분 구조
* 코드 8.8의 동작 속도를 최적화 할 수 있었던 이유는 sum이라는 정보가 $(y, x)$에서 맨 아래줄까지 내려가는 문제를 해결하는데 아무 상관이 없다는 사실을 파악한 덕분이다.
 * 다시 말해, 지금까지 어떤 경로로 이 부분 문제에 도달했건 남은 부분 문제는 항상 최적으로 풀어도 상관 없다는 뜻이다.
 * 이것은 효율적인 동적 계획법 알고리즘을 적용하기 위해 아주 중요한 조건이다. 얼마나 중요할 정도냐면 최적 부분 구조(optimal substructure)라는 유식한 이름을 붙여서 동적 계획법의 중요 요소로 꼽을 정도이다.
 * 최적 부분 구조는 어떤 문제와 분할 방식에 성립하는 조건이다. 각 부분 문제의 최적해만 있으면 전체 문제의 최적해를 쉽게 얻어낼 수 있을 경우 이 조건이 성립한다고 한다.
 * 삼각형 문제에서는 어느쪽으로 내려갈지의 선택에 따라 두 개의 부분 문제로 문제를 분할할 수 있었다. 이때 지금까지의 선택과 상관 없이 각 부분 문제를 최적으로 풀기만 하면 전체 문제의 최적해도 알 수 있다. 따라서 최적 부분 구조가 성립함을 알 수 있다.
* 다른 예로 서울에서 부산까지 가는 최단 경로를 들 수 있다. 이 최단 경로가 대전을 지난다고 가정하자. 그렇다면 이 경로를 (서울, 대전)과 (대전, 부산)으로 나눕시다. 그리고 두 구간의 최단 경로를 찾아서 둘을 이으면 항상 서울에서 부산으로 가는 최단 경로를 얻을 수 있다.
* 최단 경로를 찾는 문제는 이렇게 각 부분의 최적해가 전체의 최적해로 이어지기 때문에 최적 부분 구조를 갖는다고 할 수 있다.
* 반면 더 작은 문제의 최적해만으로는 전체 문제의 최적해를 구할 수 없다면 해당 문제에는 최적 부분 구조가 존재하지 않는다고 말한다. 예를 들어 서울에서 부산으로 향하는데 고속도로의 통행료 합이 3만원을 초과하지 않는 최단 경로를 찾고 싶다고 한다. 대전에서 부산으로 가는 경로가 두 개가 있다.
    * 경로 $A$: 통행 시간 2시간, 통행료 1만원
    * 경로 $B$: 통행 시간 1시간, 통행료 2만원

* 하나는 좀더 오래 걸리지만 통행료가 적게 들고, 하나는 더 빠르게 갈 수 있지만 통행료가 많이 든다. 그러면 이 두 경로 중 어느 쪽을 택해야 할지는 서울-대전 구간의 통행료에 따라ㅏ 결정된다.
* 따라서 이 문제에서는 부분 문제의 최적해가 전체 문제의 최적해로 연결되지 않을 수도 있으며, 따라서 최적 부분 구조가 존재하지 않는다. 
* 이런 경우에는 부분 문제 정의에 지금가지 지출한 통행료를 포함시키는 등의 작업이 필요하다.
* 사실 많은 문제에서 최적 부분 구조는 굉장히 직관적으로 이해할 수 있어서 증명이 따로 필요하지 않는다. 다만 직관적이지 않은 경우에는 대개 귀류법 혹은 대우를 이용해 증명하게 된다.



[6]: https://www.acmicpc.net/problem/1932