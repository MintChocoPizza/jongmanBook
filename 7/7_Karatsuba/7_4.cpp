// 코드 7.4 카라츠바의 빠른 정수 곱셈 알고리즘

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