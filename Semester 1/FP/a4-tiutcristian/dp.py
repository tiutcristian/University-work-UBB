"""
Problem 4
---------
Given an n * n square matrix with integer values, find the maximum length of a snake sequence.

A snake sequence begins on the matrix's top row (coordinate (0, i), 0 <= i < n). Each element of the sequence,
except the first one, must have a value ±1 from the previous one and be located directly below,
or directly to the right of the previous element.

For example, element (i, j) can be succeeded by one of the (i, j + 1) or (i + 1, j) elements.
Display the length as well as the sequence of coordinates for one sequence of maximum length.
"""
import random


def naive_rec(n: int, d: list, i: int, j: int):
    crt = -1
    if j < n-1 and abs(d[i][j] - d[i][j+1]) == 1:  # if we can access element on the right and diff is 1
        crt = max(crt, naive_rec(n, d, i, j+1))  # update current max
    if i < n-1 and abs(d[i][j] - d[i+1][j]) == 1:  # if we can access element below and diff is 1
        crt = max(crt, naive_rec(n, d, i+1, j))  # update current max
    return 1+crt  # 1 + length of the list we continue or 0 (-1 + 1)


def naive(n: int, d: list) -> int:
    maxim = 0
    for j in range(n):  # consider each possible list starting on each element of the first line
        maxim = max(maxim, 1 + naive_rec(n, d, 0, j))  # update maximum
    return maxim


def dynamic(n: int, d: list) -> int:
    # DP FORMULA:
    # dp[n][n] = 1 + max(
    #       dp[n][n-1] (if abs(d[n][n] - d[n][n-1]) = 1),
    #       dp[n-1][n] (if abs(d[n][n] - d[n-1][n]) = 1),
    # )
    dp = [[1 for x in range(n + 1)] for x in range(n + 1)]

    maxim = 0  # initialize maximum length with a value less than the smallest possible value
    for i in range(n):
        for j in range(n):
            a = 0
            b = 0
            if j > 0 and abs(d[i][j] - d[i][j-1]) == 1:  # if we can access element on the left and diff is 1
                if dp[i][j-1] != 1 or i == 0:  # if previous element not 1 (default) or on first line
                    a = dp[i][j-1]
            if i > 0 and abs(d[i][j] - d[i-1][j]) == 1:  # if we can access element above and diff is 1
                if dp[i-1][j] != 1 or i == 1:  # if previous element not 1 (default) or on first line
                    b = dp[i-1][j]
            dp[i][j] += max(a, b)  # maximum of valid elements or 0 if none found
            if dp[i][j] > maxim:
                maxim = dp[i][j]  # update maximum element
    # print(dp)
    return maxim


def read_matrix(n: int) -> list:  # read matrix line by line by mapping each line to integer list
    matrix = []
    for i in range(n):
        single_row = list(map(int, input().split()))
        matrix.append(single_row)
    return matrix


def test():
    for n in [50, 100, 200, 400]:
        m = [[0 for x in range(n)] for x in range(n)]
        for i in range(n):
            for j in range(n):
                m[i][j] = random.randint(0, 3)  # small range to get bigger lengths
        # for i in range(n):
        #     print(m[i])
        # print(naive(n, m))
        # print(dynamic(n, m))
        assert (naive(n, m) == dynamic(n, m))


test()
"""
n = int(input("n = ").strip())
m = read_matrix(n)
print("Naive: ", naive(n, m))
print("Dynamic: ", dynamic(n, m))
"""
