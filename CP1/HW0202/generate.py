import os
import random

for in_file in os.scandir("./testcase/in"):
    os.system(f"./hw0202 < {in_file.path} > {in_file.path.replace('in', 'ans')}")

    with open(in_file.path.replace("in", "ans"), "r") as fr:
        line = fr.readlines()
        with open(in_file.path.replace("in", "ans"), "w") as fw:
            for i in line:
                fw.write(i.rstrip() + "\n")
