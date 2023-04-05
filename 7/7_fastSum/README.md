# 예제: 수열의 빠른 합과 행렬의 빠른 제곱

* $recursiveSum()$은 $1+2+ \cdots + n$의 합을 재귀 호출을 이용하여 계산하는 함수이다. 
* 분할 정복을 이용한 $fastSum()$ 함수를 만들어 본다.
* 1부터 n까지의 합을 n개의 조각으로 나눈 뒤, 이들을 반으로 뚝 잘라 $\frac{n}{2}$개의 조각들로 만들어진 부분 문제 두 개를 만든다.
* $fastSum() = 1 + 2 + \cdots + n = \left( 1+2+ \cdots+  \frac{n}{2} \right) + \left( \left( \frac{n}{2} + 1 \right)+ \cdots + n \right)$
* 첫 번째 부분 문제는 $fastSum(\frac{n}{2})$로 나타낼 수 있지만, 두 번째 부분 문제는 그럴 수 없다.
* 문제를 재귀적으로 풀기 위해서는 각 부분 문제를 '1부터 n까지의 합' 꼴로 표현할 수 있어야 하는데, 위의 분할에서 두 번째 조각은 'a부터 b까지의 합'형태를 가지고 있기 때문이다.
* 따라서 다음과 같이 두 번째 부분 문제를 $fastSum(x)$를 포함하는 형태로 바꿔야 한다.
* $ \left( \frac{n}{2}+1 \right)+ \cdots + n = \left( \frac{n}{2}+1 \right) + \left( \frac{n}{2}+2 \right) + \cdots + \left( \frac{n}{2}+\frac{n}{2} \right)$
* $= \frac{n}{2} \times \frac{n}{2} +  \left( 1+2+3+ \cdots \frac{n}{2}\right)$
* $= \frac{n}{2} \times \frac{n}{2} + fastSum\left( \frac{n}{2} \right)$
* 공통된 항 $\frac{n}{2}$을 따로 빼내면 놀랍게도 $fastSum\left( \frac{n}{2} \right)$이 나타난다.

* $\therefore fastSum\left( n \right) = 2 \times fastSum\left( \frac{n}{2} \right) + \frac{n^2}{4} (n이 짝수일 때)$

## 코드 7.1
```C++
// 필수 조건: n은 자연수
// 1 + 2 + ... + n을 반환한다.
int fastSum(int n) {
    // 기저 사례
    if(n == 1) return 1;
    // 홀수인 입력이 주어질 때는 짝수인 n-1까지의 합을 재귀 호출로 계산하고 n을 더해 답을 구한다.
    if(n % 2 == 1) return fastSum(n-1) + n;
    return 2*fastSum(n/2) + (n/2)*(n/2);
}
```