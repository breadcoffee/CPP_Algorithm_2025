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