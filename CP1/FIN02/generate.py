import os
import random

N = 16
M = 30
TESTCASE = 6

for testcase in range(1, TESTCASE + 1):
    map = [[-1] * (M + 1) for _ in range(N + 1)]
    booms = [[random.randint(0, N), random.randint(0, M)] for _ in range(60)]
    for boom in booms:
        map[boom[0]][boom[1]] = -2
    with open(f"testcase/{testcase}.in", "w") as f:
        for i in range(1, N + 1):
            for j in range(1, M + 1):
                f.write(f"{map[i][j]} ")
            f.write("\n")
