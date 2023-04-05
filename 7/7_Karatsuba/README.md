# 예제: 카라츠바의 빠른 곱셈 알고리즘

## 가장 기본적인 곱셈 알고리즘
* 곱셈을 계산하는 가장 기본적인 방법은 초등학교 산수 시간에 배운 방법을 그대로 사용하는 것
* 배열들의 곱할 수의 각 자릿수를 맨 아래 자리부터 저장한다.
* 이렇게 순서를 뒤집으면 입출력할 때는 불편하지만, A[i]에 주어진 자릿수의 크기를 $10^i$로 쉽게 구할 수 있다는 장점이 있다.

### 코드 7.3
```C++
// num[]의 자릿수 올림은 처리한다.
void normalize(vector<int>& num) {
    num.push_back(0);
    // 자릿수 올림을 처리한다.
    for(int i=0; i+1 < num.size(); ++i) {
        if(num[i] < 0) {
            int borrow = (abs(num[i]) + 9) / 10;
            num[i+1] -= borrow;
            num[i] += borrow* 10;
        }
        else {
            num[i+1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}
// 두 긴 자연수의 곱을 반환한다.
// 각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다.
// 예: multiply([3,2,1], [6,5,4]) = 123 * 456 = 56088 = {8,8,0,6,5}
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    // c의 size를 a와 b의 size의 합 + 1 만큼 할당하고, 0으로 초기화 한다.
    vector<int> c(a.size() + b.size() + 1, 0);
    for(int i=0; i<a.size(); ++i) 
        for(int j=0; j<b.size(); ++j)
            c[i+j] += a[i] * b[j];
    normalize(c);
    return c;
}
```

## 카라츠바의 빠른 곱셈 알고리즘
* 카라츠바의 빠른 곱셈 알고리즘은 두 수를 각각 절반으로 쪼갭니다.
* a와 b가 각각 256자리 수라면 $a_1$과 $b_1$은 첫 128자리, $a_0$과 $b_0$은 그 다음 128자리를 저장하도록 한다.

    $ \therefore a = a_1 \times 10 ^{128} + a_0$

    $ \therefore b = b_1 \times 10 ^{128} + b_0$

* 카라츠바는 이때 $a \times b$를 네 개의 조각을 이용해 표현하는 방법을 살펴보았다.
    
    $a \times b$
    
    $ = (a_1 \times 10^{128} + a_0) \times (b_1 \times 10^{128} + b_0) $
    
     $ = a_1 \times b_1 \times 10^{256}  + (a_1 \times b_0 + a_0 \times b_1) \times 10^{128} + a_0 \times b_0 $

* 여기서 카라츠바가 발견한 것은 $a \times b$를 표현했을 때 네 번 대신 세 번의 곱셈으로만 이 값을 계산할 수 있다는 것이다.

    $ a_1 \times b_1 \times 10^{256}  + (a_1 \times b_0 + a_0 \times b_1) \times 10^{128} + a_0 \times b_0 $

    $z_2 = a_1 \times b_1$

    $z_1 = (a_1 \times b_0 + a_0 \times b_1)$

    $z_0 = a_0 \times b_0$
* 조각들의 곱을 각각 위와 같이 $ z_2, z_1, z_0 $이라고 씁시다. 우선 $z_0$ 와 $z_2$를 각각 한번의 곱셈으로 구합니다. 그리고 다음 식을 이용한다.

    $ (a_0 + a_1) \times (b_0 + b_1)$ 
    
    $ = \{ a_0 \times b_0 \} + \{ a_1 \times b_0 + a_0 \times b_1 \} + \{ a_1 \times b_1 \}$

    $ = z_0 + z_1 + z_2$

* 따라서 위 식의 결과에서 $z_0$과 $z_2$를 빼서 $z_1$을 구할 수 있다.
```C++
z2 = a1 * b1;
z0 = a0 * b0;
z1 = (a0 + a1) * (b0 + b1) - z0 - z2;
```

## 코드 7.4
```C++
// a += b * (10^k); 를 구현한다.
 void addTo(vector<int>& a, const vector<int>& b, int k);
 // a -= b;를 구현한다. a >= b를 가정한다.
 void subFrom(vector<int>& a, const vector<int>& b);
 // 두 긴 정수의 곱을 반환한다.
 vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
    int an = a.size(), bn = b.size();
    // a가 b보다 짧을 경우 둘을 바꾼다.
    if(an < bn) return karatsuba(b, a);
    // 기저 사례: a나 b가 비어 있는 경우
    if(an == 0 || bn == 0) return vector<int>();
    // 기저 사례: a가 비교적 빫은 경우 O(n^2) 곱셈으로 변경한다.
    if(an <= 50) return multiply(a, b);
    int half = an / 2;
    // a와 b를 밑에서 half 자리와 나머지로 분리한다.
    // a의 내용을 원하는 길이만큼 받아서 초기화 할 수 있다.
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    
    // b.begin()은 b 벡터의 시작 위치를 가리키는 iterator이며, 
    // b.begin() + min<int>(b.size(), half)는
    // b 벡터의 시작 위치에서 min<int>(b.size(), half) 만큼 이동한 위치를 가리키는 iterator입니다. 
    // min<int>(b.size(), half)는 b 벡터의 크기와 half 중 작은 값을 반환합니다. 
    // 이를 이용하여 b 벡터가 half보다 작을 경우 벡터 전체를, half보다 큰 경우 half 길이만큼을 복사하여 b0 벡터를 생성합니다.
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    // z2 = a1 * b1
    vector<int> z2 = karatsuba(a1, b1);
    // z0 = a0 * b0;
    vector<int> z0 = karatsuba(a0, b0);
    
    // a0 = a0 + a1; b0 = b0 + b1
    addTo(a0, a1, 0); addTo(b0, b1, 0);
    
    // z1 = (a0*b0) - z0 - z2;)
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);

    // ret = z0 + z1 * 10^half + z2 * 10^(half*2);
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half+half);
    return ret;
 }
```