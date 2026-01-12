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

## ▲ 정렬 알고리즘

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
- 선택 정렬 시나리오
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

## 병합 정렬
- 분할 정복(Divide and Conquer) 방식을 사용하여 데이터를 반복적으로 절반씩 나누다가, 나눈 부분 리스트들을 정렬된 상태로 합쳐(merge) 전체 리스트를 정렬하는 알고리즘입니다.
- 이 과정은 각 부분 리스트의 원소가 하나만 남을 때까지 반복되며, 이 과정에서 최악의 경우에도 **O(NlogN)**의 시간 복잡도를 보장합니다.
```C++
function merge_sort(arr[], low, high)
  if low < high                  // 원소의 개수가 2개 이상인 경우에만 진행
    set mid = (low + high) / 2   // 가운데 원소의 위치
    merge_sort(arr, low, mid)    // 왼쪽 부분에 대해 병합정렬 진행
    merge_sort(arr, mid+1, high) // 우측 부분에 대해 병합정렬 진행
    merge(arr, low, mid, high)   // 정렬된 두 리스트를 하나로 병합


set merged_arr = []           // 병합 이후의 결과를 담아줍니다.

function merge(arr[], low, mid, high)
  set i = low, j = mid + 1      // 각 리스트 내의 원소 위치를 잡습니다.

  set k = low                   // 병합 시 원소를 담을 위치를 유지합니다.
  while i <= mid && j <= high   // 두 리스트 내의 원소가 아직 남아있다면
    if arr[i] <= arr[j]          // 첫 번째 리스트 내의 원소가 더 작다면
      merged_arr[k] = arr[i]    // 해당 원소를 옮겨줍니다. 
      k += 1; i += 1
    else
      merged_arr[k] = arr[j]    // 그렇지 않다면 두 번째 리스트 내의
      k += 1; j += 1            // 원소를 옮겨줍니다.
  
  while i <= mid                // 아직 첫 번째 리스트 내 원소가 남아있다면
    merged_arr[k] = arr[i]      // 남은 원소들을 전부 옮겨줍니다.
    k += 1; i += 1

  while j <= high               // 아직 두 번째 리스트 내 원소가 남아있다면
    merged_arr[k] = arr[j]      // 남은 원소들을 전부 옮겨줍니다.
    k += 1; j += 1
  
  for k = low ... k <= high     // 병합된 리스트를 다시
    arr[k] = merged_arr[k]      // 원본 리스트에 옮겨줍니다.
  
  return arr 
```

## 퀵 정렬
- 퀵 정렬 시나리오
> 1. 피벗(Pivot) 선택: 정렬할 리스트 내에서 하나의 원소를 기준값(피벗)으로 선택합니다. 어떤 값을 피벗으로 선택하느냐가 알고리즘 성능에 중요한 영향을 미칩니다.
> 2. 분할(Partition): 피벗을 기준으로 리스트를 두 개의 하위 리스트로 나눕니다. 피벗보다 작은 값들은 왼쪽에, 큰 값들은 오른쪽에 위치시킵니다. 이 과정을 통해 피벗은 자신의 정확한 정렬 위치에 놓이게 됩니다.
> 3. 정복(Conquer): 좌우로 분할된 두 개의 하위 리스트 각각에 대해 다시 퀵 정렬을 재귀적으로 적용합니다.
> 4. 종료: 리스트의 크기가 0 또는 1이 되면 정렬이 완료된 것으로 간주하고 재귀 호출을 종료합니다. 

- 평균 시간 복잡도: O(NlogN)으로, 대부분의 상황에서 뛰어난 성능을 보입니다.
- 최악 시간 복잡도: O(N²)입니다. 이는 피벗 선택이 극단적으로 편향될 때(예: 이미 정렬된 리스트에서 가장 작은 값이나 큰 값을 피벗으로 계속 선택하는 경우) 발생할 수 있습니다.
```C++
function quick_sort(arr[], low, high)
  if low < high                     // 원소의 개수가 2개 이상인 경우에만 진행
    pos = partition(arr, low, high) // pivot 기준으로 좌우로 분할 한 후
                                    // 해당 pivot의 위치를 pos에 넣어줍니다.
    quick_sort(arr, low, pos - 1)   // pivot의 왼쪽 구간에 있는 원소들을 정렬합니다. 
    quick_sort(arr, pos + 1, high)  // pivot의 오른쪽 구간에 있는 원소들을 정렬합니다.

function partition(arr[], low, high)
  set pivot = select_pivot(arr, low, high)    // pivot을 고릅니다.
  set i = low - 1                             // 파란색 화살표 위치를 정해줍니다.
                                              // 파란색 화살표는 pivot보다 같거나 큰 
                                              // 원소를 가리키고 있습니다.
  for j = low ... j <= high - 1               // 빨간색 화살표를 움직입니다.
    if arr[j] < pivot                         // 빨간색 화살표가 가리키는 원소가
      i += 1                                  // pivot보다 작다면, 왼쪽으로 가야하므로
      swap (arr[i], arr[j])                   // 두 원소의 위치를 바꿔줍니다.
      
  swap (arr[i + 1], arr[high])                // 최종적으로 pivot을
                                              // 경계에 있는 원소와 교환해줍니다.
                                              // 이때 경계는 마지막 파란색 화살표 위치에
                                              // 1을 더한 위치입니다.
  return i + 1                                // pivot의 최종 위치를 반환해줍니다.
```

## 힙 정렬
- **힙(Heap)**이라는 특별한 자료구조를 이용하는 정렬 알고리즘입니다. 선택 정렬과 유사하게 가장 큰(또는 가장 작은) 원소를 찾아 제자리로 보내는 방식을 사용하지만, 힙 자료구조를 활용하여 이 과정을 효율적으로 만듭니다.
- 시간 복잡도: O(NlogN)입니다. 힙 구성 단계에서 O(N), 각 원소를 제자리로 옮기는 과정에서 O(logN)이 N번 반복되어 총 O(NlogN)의 시간 복잡도를 가집니다. 최선, 평균, 최악의 경우 모두 시간 복잡도가 O(NlogN)으로 일정합니다.
```C++
function heapify(arr[], n, i)
  set largest = i                     // 최대 노드가 i번이라고 가정합니다.
  set l = i * 2                       // 왼쪽 자식 노드 번호입니다.
  set r = i * 2 + 1                   // 오른쪽 자식 노드 번호입니다.

  if l <= n && arr[l] > arr[largest]  // 왼쪽 자식이 크다면, 최대 번호를 수정합니다.
    largest = l

  if r <= n && arr[r] > arr[largest] // 오른쪽 자식이 크다면, 최대 번호를 수정합니다.
    largest = r

  if largest != i                   // 최대 노드가 자식 노드라면
    swap(arr[i], arr[largest])      // 해당 자식과 현재 노드를 교환해준 뒤
    heapify(arr, n, largest)        // 내려간 위치에서 다시 heapify를 진행합니다.

function heap_sort(arr[], n)
  // 1. max-heap을 만들어 줍니다.
  for i = n / 2 ... i >= 1         // n / 2번째 원소부터 1번째 원소까지 돌며
    heapify(arr, n, i)             // heapify 과정을 진행하여 max-heap을 만들어줍니다.

  // 2. 정렬을 진행합니다.
  for i = n ... i > 1              // n을 하나씩 줄여나가며
    swap(arr[1], arr[i])           // 현재 최댓값과 가장 끝에 있는 노드를 교환해주고
    heapify(arr, i - 1, 1)         // 1번 노드를 기준으로 heapify를 진행하여
                                   // max-heap 상태를 계속 유지해줍니다. 
```

## 이진탐색
- 이진 탐색(Binary Search)은 정렬된 배열에서 특정한 값을 효율적으로 찾는 탐색 알고리즘입니다.
- 이 알고리즘의 기본 원리는 탐색 범위를 반으로 줄여가며 데이터를 찾는 것이며, 이 과정을 반복함으로써 탐색의 효율성을 극대화합니다.
- 이진 탐색은 분할 정복(Divide and Conquer) 방식의 대표적인 예시로 볼 수 있습니다.
- 이진 탐색의 시간 복잡도는 O(logN) 입니다.
- 탐색속도가 매우 빠르지만 단점은 배열이 반드시 정렬되어있어야 한다.
```C++
function solution(arr, target)
  set left = 0
  set right = arr.size - 1
  while left <= right
    set mid = (left + right) / 2
    if arr[mid] == target
      return mid

    if arr[mid] > target
      right = mid - 1
    else
      left = mid + 1
      
  return -1
```

## 동적 계획법
- 동적계획법이란 큰 문제에 대한 답을 얻기 위해 동일한 문제이지만 크기가 더 작은 문제들을 먼저 해결한 뒤, 그 결과들을 이용해 큰 문제를 비교적 간단하게 해결하는 기법을 뜻합니다.
- 보통 점화식을 기반으로 문제를 해결하며 for문이나 재귀함수를 이용하기도한다.

1. 메모이제이션(Memoization)
- Memoization은 top-down 방식으로, 큰 문제를 해결할 때 작은 하위 문제의 해답을 이용합니다. 
- 이전에 계산한 값을 메모리에 저장하여 중복적인 계산을 제거하여 전체적인 실행 속도를 빠르게 해주는 기법이다.
- 재귀함수를 사용하여 문제를 해결한다.

- 피보나치 수를 구할 때 이 메모이제이션을 사용하면 더 효율적으로 구성이 가능하다.
- 메모이제이션을 사용하면 기존에 O(2^n) 시간복잡도를 갖던 코드가, 이제는 O(n)에 답을 구할 수 있다.
```c++
function fibbo(n)
    if memo[n] != -1           // 이미 n번째 값을 구해본 적이 있다면
        return memo[n]         // memo에 적혀있는 값을 반환해줍니다.
    if n <= 2                  // n이 2이하인 경우에는 종료 조건이므로 
        memo[n] = 1            // 해당하는 숫자를 memo에 넣어줍니다.
    else                       // 종료조건이 아닌 경우에는 
        memo[n] = fibbo(n - 1) + fibbo(n - 2)   // 점화식을 이용하여 답을 구한 뒤
                                                // 해당 값을 memo에 저장해줍니다.
    return memo[n]             // memo 값을 반환합니다.
```

2. Tabulation
- Tabulation은 bottom-up 방식으로, 작은 하위 문제의 해답을 먼저 계산하고, 그것을 이용해 큰 문제의 해답을 계산하는 방식
- 배열을 사용하여 작은 문제의 해답을 저장하고 그것을 이용해 큰 문제의 해답을 계산한다.
- 주로 반복문을 사용한다.
```c++
function solution(n)
    dp = [0, 0, 0, ...]
    dp[1] = 1
    dp[2] = 1
  
    for i = 3 ... i <= n
        dp[i] = dp[i - 1] + dp[i - 2]
  
    return dp[n]
```

3. 0/1 Knapsack or Fractional Knapsack
- 0/1 Knapsack
  - 선택하지 않거나(0), 선택하거나(1) 두 가지 경우만 존재한다는 뜻입니다. 즉, 물건을 쪼갤 수 없는 상황
  - 매순간 최선의 값을 구하는 그리디 알고리즘으로는 해결이 불가능
  - 동적계획법으로 올바른 답을 구할 수 있다.
- Fractional Knapsack
  - 물건을 원하는 만큼 쪼개서(Fraction) 담을 수 있는 상황
  - 현재 상황에서 최선이다 싶은 것을 계속 반복하는 알고리즘을 그리디 알고리즘, 욕심쟁이 기법이라 부른다.
  - greedy 알고리즘이 Fractional Knapsack 문제에서는 실제 최적의 답을 가져와주게 된다.

## 그래프
그래프는 간선(Edge)과 노드(Node)의 집합으로 구성된 자료구조입니다.
그래프는 특성에 따라 여러가지로 분류할 수 있는데, 대표적으로 방향의 존재 여부로 방향 그래프/무방향 그래프로 나눌 수 있습니다.
그래프의 간선 위에 값이 적혀져 있는 경우도 있는데, 이때 우리는 이 값을 간선의 가중치라고 부릅니다.
또한, 연결 관계에서 특정 노드와 연결된 이웃 노드의 수를 차수(Degree)라고 부릅니다.

1. 그래프 탐색 (Graph Traversal)
그래프의 모든 정점을 방문하는 가장 기초적인 방법입니다.

- DFS (깊이 우선 탐색, Depth-First Search):
  - 한 방향으로 갈 수 있는 데까지 깊게 가다가 막히면 되돌아오는 방식입니다.
  - 특징: 스택(Stack)이나 재귀 함수를 사용합니다. 경로의 존재 여부를 파악할 때 유리합니다.
```python
def dfs(graph, v, visited):
  visited[v] = True
  print(v, end=' ')
  for i in graph[v]:
      if not visited[i]:
          dfs(graph, i, visited)
```

- BFS (너비 우선 탐색, Breadth-First Search):
  - 현재 정점에서 가까운 이웃들부터 먼저 방문하는 방식입니다.
  - 특징: 큐(Queue)를 사용합니다. 가중치가 없는 그래프에서 최단 경로를 찾을 때 사용됩니다.
```python
def bfs(graph, start, visited):
    queue = deque([start])
    visited[start] = True
    while queue:
        v = queue.popleft()
        print(v, end=' ')
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True
```

2. 최단 경로 알고리즘 (Shortest Path)
두 지점 사이의 가장 효율적인 경로를 찾는 알고리즘입니다.

- Dijkstra (다익스트라): 시작점이 1개고 가중치가 양수라면 사용
  - 음의 가중치가 없는 그래프에서 특정 시작점부터 다른 모든 정점까지의 최단 거리를 구합니다. (네비게이션의 기본 원리)
```python
def dijkstra(graph, start, n):
    distances = [float('inf')] * (n + 1)
    distances[start] = 0
    queue = []
    heapq.heappush(queue, [distances[start], start])

    while queue:
        current_distance, current_destination = heapq.heappop(queue)

        if distances[current_destination] < current_distance:
            continue
        
        for new_destination, weight in graph[current_destination]:
            distance = current_distance + weight
            if distance < distances[new_destination]:
                distances[new_destination] = distance
                heapq.heappush(queue, [distance, new_destination])
    return distances
```

- Bellman-Ford (벨만-포드): 가중치에 음수가 섞여 있다면 사용
  - 음의 가중치가 있는 그래프에서도 동작하며, '음의 사이클'이 있는지 확인할 수 있습니다.
```python
def bellman_ford(start, n, edges):
    dist = [float('inf')] * (n + 1)
    dist[start] = 0
    
    for i in range(n): # n번 반복
        for u, v, w in edges: # 모든 간선 확인
            if dist[u] != float('inf') and dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                if i == n - 1: # n번째에도 갱신되면 음수 사이클 존재
                    return "Negative Cycle Detected"
    return dist  
```

- Floyd-Warshall (플로이드-워셜): 모든 지점 간의 거리가 다 필요하다면 사용
  - 모든 정점 쌍 간의 최단 거리를 한 번에 다 구합니다. (거대한 2차원 배열 사용)
```python
def floyd_warshall(n, graph): # graph는 2차원 인접 행렬
    for k in range(1, n + 1):     # 거쳐가는 노드
        for a in range(1, n + 1): # 출발 노드
            for b in range(1, n + 1): # 도착 노드
                graph[a][b] = min(graph[a][b], graph[a][k] + graph[k][b])  
```

3. 최소 신장 트리 (MST, Minimum Spanning Tree)
그래프 내의 모든 정점을 가장 적은 비용으로 연결하는 '트리'를 찾는 알고리즘입니다.

- Kruskal (크루스칼) : 간선이 적거나 정렬이 쉽다면 사용
  - 간선들을 가중치 순으로 정렬한 뒤, 사이클을 만들지 않는 선에서 작은 가중치부터 선택합니다. (Union-Find 구조 활용)
```python
def find_parent(parent, x):
    if parent[x] != x:
        parent[x] = find_parent(parent, parent[x])
    return parent[x]

def union_parent(parent, a, b):
    a = find_parent(parent, a)
    b = find_parent(parent, b)
    if a < b: parent[b] = a
    else: parent[a] = b

# Kruskal 메인 로직
edges.sort() # 가중치 순 정렬
for edge in edges:
    cost, a, b = edge
    if find_parent(parent, a) != find_parent(parent, b):
        union_parent(parent, a, b)
        total_cost += cost  
```

- Prim (프림) : 간선이 매우 많을 때 사용
  - 하나의 정점에서 시작해 연결된 간선 중 가장 저렴한 것을 선택하며 확장해 나갑니다.
```python
def prim(start_node, n, adj):
    visited = [False] * (n + 1)
    pq = [(0, start_node)] # (가중치, 노드)
    total_weight = 0
    
    while pq:
        weight, u = heapq.heappop(pq)
        if visited[u]: continue
        
        visited[u] = True
        total_weight += weight
        
        for v, w in adj[u]:
            if not visited[v]:
                heapq.heappush(pq, (w, v))
    return total_weight  
```

4. 기타 중요 알고리즘
- 위상 정렬 (Topological Sort)
  - 방향 그래프에서 '순서'가 정해져 있을 때(예: 선수 과목 수강 순서), 그 순서를 거스르지 않게 나열하는 방법입니다.
```python
def topological_sort(n, indegree, graph):
    result = []
    q = deque()

    for i in range(1, n + 1):
        if indegree[i] == 0:
            q.append(i)

    while q:
        now = q.popleft()
        result.append(now)
        for i in graph[now]:
            indegree[i] -= 1
            if indegree[i] == 0:
                q.append(i)
    return result  
```

- Union-Find (서로소 집합)
  - 여러 노드가 같은 그룹에 속해 있는지 확인하고 합치는 알고리즘으로, 크루스칼 알고리즘의 핵심 도구입니다.
```python
def find_parent(parent, x):
    # 경로 압축: 루트 노드를 바로 부모로 설정
    if parent[x] != x:
        parent[x] = find_parent(parent, parent[x])
    return parent[x]

def union_parent(parent, a, b):
    root_a = find_parent(parent, a)
    root_b = find_parent(parent, b)
    if root_a != root_b:
        parent[root_b] = root_a # 보통 작은 번호를 부모로 합침  
```