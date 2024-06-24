import os
import random

while True:
    cnt = [0] * 4
    for case in range(11, 21):
        with open("testcase/in/%d.in" % case, "w") as f:
            for i in range(random.randint(30, 300)):
                num = random.randint(0, 9)
                f.write("%d\n" % num)
            f.write("-1\n")
        os.system(
            "./mid03 < ./testcase/in/%d.in > ./testcase/ans/%d.ans" % (case, case)
        )

        with open("testcase/ans/%d.ans" % case, "r") as f:
            lines = f.readlines()[0].strip()
            for num in lines:
                cnt[int(num)] += 1
    print(cnt)
    if 2 <= cnt[0] <= 7 and 2 <= cnt[1] <= 6 and 2 <= cnt[2] <= 6 and 2 <= cnt[3] <= 6:
        break
