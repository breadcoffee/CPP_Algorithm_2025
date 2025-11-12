# CPP_Algorithm_2025
Mobius BootCamp 자료구조/알고리즘

## HASH
- 해싱은 특정 데이터가 들어온 순서 상관 없이 삽입, 삭제, 검색이 자주 발생하는 경우에 사용하기에 좋습니다.
- 하지만 해시 함수를 사용할 때는 각 타입(문자열, 숫자...) 에 맞는 해시 함수를 사용하여 해시 값으로 바꾸게 되는데. 대응할 수 없는 타입도 존재합니다.(대표적인 예시로 배열이 있습니다.)
- 삽입, 삭제, 탐색에 걸리는 시간이 전부 O(1) 이다.
```C++
function append(key, value)
  set index = hash_function(key)
  hash[index] = value
  
function find(key)
  set index = hash_function(key)
  if hash[index] != null
    return hash[index]
    
function remove(key, value)
  set index = hash_function(key)
  if hash[index] == null
    return 
  hash[index] = null
```
