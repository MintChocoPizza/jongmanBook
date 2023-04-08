# 7.2 문제: 쿼드 트리 뒤집기 (문제 ID: QUADTREE, 난이도: 하)
* 대량의 좌표 데이터를 메모리 안에 압축해 저장하기 위해 사용하는 여러 기법 중 쿼드 트리(quad tree)란 것이 있다.

* 이 문제를 풀 수 있는 가장 무식한 방법은 주어진 그림의 쿼드 트리 압축을 풀어서 실제 이미지를 얻고 상하 반전한 뒤 다시 쿼드 트리 압축하는 것이고, 실제로 이 생각이 가장 먼저 들었다.

### 쿼드 트리 압축 풀기
* 쿼드 트리가 재귀적으로 정의되어 있기 때문에 쿼드 트리를 압축하거나 해제하는 과정은 재귀 호출로 구현하는 것이 가장 자연스럽다.
* 문자열 s의 압축을 해제해서 $N \times N$ 크기의 배열에 저장하는 함수 $decompress()$를 구현한다고 한다.
* 기저 사례는 $s$의 첫 글자가 $w$나 $b$인 경우이고, 이때는 배열 전체에 해당 색을 칠하고 곧장 종료한다.
* 만약 첫 글자가 $x$라면 $decompress()$는 $s$의 나머지 부분을 넷으로 쪼개 재귀 호출한다.
* 이때 각 부분이 배열의 어느 부분에 저장되어야 하는지 지정하는 위치 오프셋 또한 절달해야 한다.
```C++
char decompressed[MAX_SIZE][MAX_SIZE];
// s를 압축 해제해서 decompressed[y..y + size-1][x..x + size-1] 구간에 쓴다.
void decompresse(const string& s, int y, int x, int size);
```
* 위와 같이 생각하고 구현을 시작하면 $s$의 나머지 부분을 넷으로 쪼개기가 까다롭다.
* 각 부분의 길이가 일정하지 않기 때문인데, 이를 해결할 수 있는 첫 번째 방법은 
* 주어진 위치에서 시작하는 압축 결과의 길이를 반환하는 함수 $getChunkLength()$를 만드는 것이다.

    $s[0]$이 $x$라고 하면, 왼쪽 위 조각을 나타내는 부분은 항상 $s[1]$에서부터 시작한다.
    이때 $getChunkLength(s, 1)$이 해당 부분 압축의 길이를 반환하도록 하는 것 이다.
    $getChunkLength(s,1)$이 5를 반환하면 다음 조각은 $s[6]$부터 시작한다는 것을 알 수 있고, 이와 같이 $s$의 나머지 부분을 분할할 수 있다.  $getChunkLength()$함수를 재귀 호출로 작성하ㅡㄴ 것은 어렵지 않지만, 비슷한 일을 하는 두 개의 함수를 각각 작성한다는 점이다.
* 이런 때 유용하게 사용할 수 있는 패턴은 $s$를 미리 쪼개는 것이 아니라 $decompress()$함수에서 __'필요한 만큼 가져다 쓰도록'__ 하는 것이다.
* $decompress()$함수에 $s$를 통째로 전달하는 것이 아니라, $s$의 한 글자를 가리키는 포인터를 전달하고, 함수 내에서는 한 글자를 검사할 때마다 이 포인터를 앞으로 한 칸씩 옮긴다.

## 코드 7.5
```C++
char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator& it, int y, int x, int size) {
    // 한 글자를 검사할 때마다 반복자를 한 칸 앞으로 옮긴다.
    char head = *(it++);
    // 기저 사례: 첫 글자가 b 또는 W인 경우
    if(head == 'b' || head == 'w') {
        for(int dy = 0; dy < size; ++dy)
            for(int dx = 0; dx < size; ++dx)
                decompressed[y+dy][x+dx] = head;
    }
    else {
        // 네 부분을 각각 순서대로 압축 해제한다.
        int half = size/2;
        decompress(it, y, x, half);
        decompress(it, y, x+half, half);
        decompress(it, y+half, x, half);
        decompress(it, y+half, x+half, half);       
    }
}
```

### 압축 다 풀지 않고 뒤집기
* $decompress()$의 기저 사례를 생각해보면 전체가 검은 색이나 흰 색인 그림은 뒤집어 봤자 다를게 없다.
* 전체가 한 가지 색이 아닌 경우에는 재귀 호출을 이용하여 네 부분을 각각 상하로 뒤집은 결과를 얻은 뒤, 이들을 병합해 답을 얻어야 한다.
```C++
string trverse(string::iterator& it) {
    char head = *it;
    ++it;
    if(head == 'b' || head == 'w')
        return string(1, head);
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    // 각각 위와 아래 조각들의 위치를 바꾼다.
    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}
```
* $x$인 경우 왼쪽 위 부터 차례대로 호출하고(분할) 병합하여 return한다.