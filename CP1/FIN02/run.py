import os

for test in range(1, 12):
    os.system(
        f"cd refer_ans && ./fin02 < ../testcase/in/{test}.in > ../testcase/ans/{test}.ans"
    )
