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

## ▲정렬 알고리즘

## 거품 정렬
- 거품 정렬은 가장 단순한 정렬 알고리즘입니다. 기본적인 아이디어는 간단합니다. 첫번째와 두번째 값을 비교하고, 두번째와 세번째 값을 비교하고, ... n-1번째와 n번째 값을 비교합니다. 이 과정에서 순서가 맞지 않은 값을 서로 교환해줍니다. 이런 절차를 정렬이 될 때 까지 반복합니다.
- 교환 여부를 확인하기 위해 전체 값을 한 바퀴 도는데, 이 시간복잡도는 자연스럽게 O(N)이 될 것 입니다. 최악의 경우에는 O(N²)을 가집니다.
```C++
function bubble_sort(arr[])
  set len = arr.size
  
  for i = 0 ... i < len - 1
    for j = 0 ... j < len - 1 - i
      if arr[j] > arr[j + 1]
        set tmp = arr[j]
        arr[j] = arr[j + 1]
        arr[j + 1] = tmp
  
  return arr
```

## 선택 정렬
선택 정렬 시나리오
> 1. 전체 값 중 가장 작은 값을 찾음
> 2. 해당 값을 맨 첫번째에 배치함
> 3. 첫번째 값을 제외하고 가장 작은 값을 찾아 두번째에 배치함
> 4. 두번째, 세번째, ... n-1번째 값을 제외하고 가장 작은 값을 찾아 정해진 위치에 배치함.

- 중간에 정렬된 상태라면 종료될 수 있는 거품 정렬과는 다르게, 선택 정렬의 경우 반드시 n−1,n−2,...2,1번의 비교 연산을 수행해야 하기 때문에 약 n∗(n−1)/2 번의 연산을 필요로 합니다. 따라서, 자연스럽게 시간복잡도는 O(N²)이 될 것 입니다.
```C++
function selection_sort(arr[])
  set len = arr.size
  for i = 0 ... i < len-1
    set min = i
    for j = i+1 ... j < len
      if arr[j] < arr[min]
        min = j
    set tmp = arr[i]
    arr[i] = arr[min]
    arr[min] = tmp
  
  return arr
```

## 삽입 정렬
- 삽입정렬은, 앞에서부터 순서대로 보면서 앞에 있는 모든 원소가 정렬이 되어 있다는 가정 하에서 현재 원소의 위치를 적절하게 집어넣는 정렬입니다.
- 원소가 1개인 경우부터 시작해, 2번째 원소, 3번째 원소, ...n번째 원소까지 진행하며 지금까지 진행한 곳까지의 원소들을 전부 오름차순으로 정렬한 상태를 유지하며 진행하는 방법이 바로 삽입 정렬입니다.
- n개의 원소에 대해 값 삽입을 수행해야 하는데, 2번째 원소의 경우엔 최대 1개의 원소를 이동해야 하고, 3번째 원소의 경우엔 최대 2개의 원소를 이동해야 하며, n번째 원소까지 삽입하는 경우엔 최대 n−1개의 원소가 이동해야 하므로 결과적으로 최대 n(n−1)/2 개의 원소가 이동해야 하기 때문에, O(N²)의 시간복잡도가 나올 것이라고 판단할 수 있습니다.
```C++
function insertion_sort(arr[])
  set size = arr.size
  for i = 1 ... i < size
    set j = i - 1
    set key = arr[i]
    while j >= 0 && arr[j] > key
      arr[j + 1] = arr[j]
      j--
    arr[j + 1] = key
  return arr
```

## 기수 정렬
- 기수 정렬은 맨 뒤에 있는 자릿수 부터 해당 자리수를 기준으로 정렬한 뒤, 점점 앞으로 이동하며 각 자리수를 기준으로 정렬하다가 최종적으로 가장 높은 자리수를 기준으로 정렬하는 방법입니다.
- 기수정렬의 시간복잡도는 O(k∗n)으로, 여기서 k는 자릿수를 의미합니다. 각각의 데이터에 대해 매 자릿수마다 분류작업을 하기 때문에 분류작업이 k번 반복된다고 볼 수 있어 다음과 같은 시간복잡도가 나오는 것입니다.
```C++
function radix_sort(arr, k)
  for pos = k - 1 ... pos >= 0: //pos는 현재 보고 있는 자리의 위치를 의미합니다.
    set arr_new = [10][]
    for i = 0 ... i < arr.size
      set digit = posth digit of arr[i] //0에서 9사이의 숫자가 digit이라는 이름에 적히게 됩니다.
      arr_new[digit].append(arr[i])

    set store_arr = []
    for i = 0 ... i < 10
      for j = 0 ... j < arr_new[i].size
        store_arr.append(arr_new[i][j])
  
    arr = store_arr

  return arr
```

## 정렬간 속도 비교
거품, 선택, 삽입 정렬 알고리즘의 시간복잡도는 O(N²)라는 공통점이 있지만, 실제 소요되는 시간은 많이 다릅니다.

- **거품 정렬**의 경우, 일반적으로 셋 중 가장 느립니다. 그러나 정렬된 배열의 경우, sorted의 값이 계속 true이기 때문에 시간이 매우 빨라집니다.
- **선택 정렬**의 경우 배열의 상태와 상관 없이, 1번째로 작은 원소를 찾고, 2번째로 작은 원소를 찾고, ... 하는 과정을 거치기 때문에 어떠한 상황이던 동일한 시간을 보여줍니다.
- **삽입 정렬**의 경우 일반적으로는 가장 빠르나, 값이 반대로 정렬되어 있는 경우 성능이 많이 떨어진다는 단점이 있습니다. 또한, 앞 배열에 값을 삽입하는 알고리즘의 특성상 이미 정렬된 배열에 추가적으로 값을 몇개 추가하여 정렬하는 경우에 좋은 성능을 보여줍니다.