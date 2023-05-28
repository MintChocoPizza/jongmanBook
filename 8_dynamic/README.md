# 동적 계획법

* 자주 사용되는 디자인 패러다임
* 동적 계획법(dynamic programming)는 최적화 문제를 연구하는 수학 이론에서 왔으며, 우리가 전산학 전반에서 일반적으로 사용하는 동적(dynamic), 혹은 프로그래밍(programming)이란 단어와는 아무런 관련이 없다.
* 따라서 dynamic programming의 적절한 번역은 동적 프로그래밍이 아니라 동적 계획법이다.

## 중복되는 문제
* 동적 계획법은 큰 의미에서 분할 정복과 같은 접근 방식을 의미한다.
* 동적 계획법을 사용하는 알고리즘들 또한 처음 주어진 문제를 __더 작은 문제들로 나눈뒤__ 각 조각의 답을 계산하고, 이 답들로부터 원래 문제에 대한 답을 계산해 내기 때문이다.
* 동적 계획법과 분할 정복의 차이가 발생하는 부분은 문제를 나누는 방식이다.
* 동적 계획법에서 __어떤 부분 문제는__ __두 개 이상의 문제를 푸는데 사용될 수 있기 때문에__, 이 문제의 답을 여러 번 계산하는 대신 __한 번만 계산 하고 계산 결과를 재활용함으로써__ 속도의 향상을 꾀할 수 있다.
* 그러기 위해서는 각 문제의 답을 메모리에 저장해 둘 필요가 있다.
* 이때 이미 계산한 값을 저장해두는 메모리의 장소를 캐시(cache)라고 부르며, 두 번 이상 계산되는 부분 문제를 중복되는 부분 문제(overlapping subproblems)라고 부른다.


[When memoization can be applied][1]

## 메모이제이션의 시간 복잡도 분석
* 메모이제이션을 사용하는 알고리즘의 시간 복잡도를 굉장히 간단하게(주먹구구로) 계산할 수 있는 방법이 있다.

    (존재하는 부분 문제의 수) X (한 부분 문제를 풀 때 필요한 반복문의 수행 횟수)

* 위 식을 이항 계수를 계산하는 $bino2()$에 적용해보자.

* $r$의 최대치는 $n$이니 $bino2(n, r)$을 계산할 때 만날 수 있는 부분 문제의 수는 최대 $O(n^2)$이다.

* 각 부분 문제를 계산할 때 걸리는 시간은 반복문이 없으니 $O(1)
이고, 그러면 위 식에 따라 $bino2(n, r)$을 계산하는 데 걸리는 시간 복잡도는 $O(n^2) \times O(1) = O(n^2)$이 된다.

<A href=https://github.com/MintChocoPizza/jongmanBook/tree/master/8_dynamic/8_Traditional%20Optimization%20Problems/8_LIS#my_tag>최적화 문제 동적 계획법 레시피 </a>

<A href=https://github.com/MintChocoPizza/jongmanBook/tree/master/8_dynamic/Number%20of%20Cases%20and%20Probabilities>경우의 수와 확률</a>

[1]: https://github.com/MintChocoPizza/jongmanBook/tree/master/8_dynamic/Memoization

[2]: https://github.com/MintChocoPizza/jongmanBook/tree/master/8_dynamic/8_Traditional%20Optimization%20Problems/8_LIS#my_tag
