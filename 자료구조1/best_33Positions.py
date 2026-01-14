'''
개념
N * N 크기의 격자 정보가 주어집니다. 이때 해당 위치에 동전이 있다면 1, 없다면 0이 주어집니다. 
N * N 격자를 벗어나지 않도록 3 * 3 크기의 격자를 적절하게 잘 잡아서 
해당 범위 안에 들어있는 동전의 개수를 최대로 하는 프로그램을 작성해보세요.

입력 형식
첫 번째 줄에는 격자의 크기를 나타내는 N이 주어집니다.

두 번째 줄부터는 N개의 줄에 걸쳐 격자에 대한 정보가 주어집니다. 
각 줄에는 각각의 행에 대한 정보가 주어지며, 
이 정보는 0또는 1로 이루어진 N개의 숫자로 나타내어지며 공백을 사이에 두고 주어집니다.

3 ≤ N ≤ 20

출력 형식
N * N 격자를 벗어나지 않으면서, 3 * 3 크기 격자 내에 들어올 수 있는 최대 동전의 수를 출력해주세요.

입출력 예제
예제1
입력:

3
1 0 1
0 1 0
0 1 0
출력:

4

예제2
입력:

5
0 0 0 1 1
1 0 1 1 1
0 1 0 1 0
0 1 0 1 0
0 0 0 1 1
출력:

6
'''


import sys

# 입력 받기
n = int(sys.stdin.readline())
grid = [
    list(map(int, sys.stdin.readline().split()))
    for _ in range(n)
]

def get_coin_count(row, col):
    """
    (row, col)을 왼쪽 상단으로 하는 3*3 격자 내 동전 개수를 반환합니다.
    """
    count = 0
    for i in range(row, row + 3):
        for j in range(col, col + 3):
            count += grid[i][j]
    return count

max_coins = 0

# 3*3 격자의 왼쪽 상단 모서리가 위치할 수 있는 모든 지점을 탐색합니다.
for i in range(n - 2):
    for j in range(n - 2):
        # 현재 위치에서의 동전 개수 계산
        current_coins = get_coin_count(i, j)
        
        # 최댓값 갱신
        if current_coins > max_coins:
            max_coins = current_coins

print(max_coins)