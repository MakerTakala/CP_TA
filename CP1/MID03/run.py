import os

for case in range(1, 21):
    os.system(
        "./refer_ans/mid03 < ./testcase/in/%d.in > ./testcase/ans/%d.ans" % (case, case)
    )
