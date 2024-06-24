import os

HW = "04"
P = "05"
total_testcase = 14

ID_list = []
with open("../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

    exefile = f"./HW/{ID}/1-build/hw{HW}{P}"

    with open("./grade.csv", "r") as grade_file:
        grade_line = grade_file.readlines()
        have_ID = False
        for text in grade_line:
            if ID in text:
                have_ID = True
                break
        grade_file.close()
        if have_ID:
            continue

    print(ID + ":\n\n")

    if not os.path.isfile(exefile):
        print(ID + "No file.\n")
        input()
        with open("./grade.csv", "a") as grade_file:
            grade_file.write(ID + ",0,No file\n")
        continue

    os.makedirs("./HW/" + ID + "/out", exist_ok=True)
    for testcase in range(1, total_testcase + 1):
        os.system(
            f"./{exefile} < ./testcase/in/{testcase}.in > ./HW/{ID}/out/{testcase}.out"
        )

    total_score = 0
    ans_score = [5, 1, 2, 1, 1, 0.5, 2, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5]
    log = ""
    for testcase in range(1, total_testcase + 1):
        os.system("clear")
        print(ID + ":\n\n")
        print(f"Testcase {testcase}: {ans_score[testcase - 1]}")
        ans = []
        out = []
        with open(f"./testcase/ans/{testcase}.ans", "r") as ans_file:
            ans = ans_file.readlines()
        with open(f"./HW/{ID}/out/{testcase}.out") as out_file:
            out = out_file.readlines()

        print("-" * 50)
        flag = False
        for i in range(len(out)):
            if "The" in out[i]:
                flag = True
                tmp = out[i].split("The")[1]
                print(f"The{tmp}")
                continue
            if out[i] == "\n":
                continue
            if flag:
                if i < len(out):
                    out[i] = out[i].strip()
                if i >= len(out):
                    out.append("")
                print(f"{out[i]:<30}")
        print("-" * 50)
        for i in range(len(ans)):
            if i < len(ans):
                ans[i] = ans[i].strip()
            if i >= len(ans):
                ans.append("")
            print(f"{ans[i]:<30}")
        print("-" * 50)

        print(f"score({ans_score[testcase - 1]}): ", end="")
        score = input()
        if score == "":
            score = "0"

        sum_score = "0"
        if testcase <= 10:
            print("sum_score: ", end="")
            sum_score = input()
            if sum_score == "" or sum_score == "0" or float(sum_score) == 0:
                sum_score = "0"
            else:
                sum_score = "0.3"

        total_score += float(score) + float(sum_score)
        if 1 <= testcase <= 10:
            log += f" t{testcase}: {float(score) + float(sum_score)}/{ans_score[testcase - 1] + 0.3} "
        else:
            log += f" t{testcase}: {float(score)}/{ans_score[testcase - 1]} "

    print("Sorted: ", end="")
    sorted = input()
    if sorted == "":
        sorted = "0"
    log += f" sorted: {sorted}/1"
    total_score += float(sorted)

    print(ID + ":\n\n")
    print("total_score: " + str(total_score))
    print(log)
    input()
    with open("./grade.csv", "a") as grade_file:
        grade_file.write(f"{ID},{total_score},{log}\n")
