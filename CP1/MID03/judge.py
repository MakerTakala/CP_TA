import os

HW = "mid"
P = "03"

ID_list = []
with open("../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

ans = []
for testcase in range(1, 21):
    with open(("./testcase/ans/%d.ans" % (testcase)), "r") as ansfile:
        lines = ansfile.readlines()
        testcase_ans = ""
        for line in lines:
            if "SUCCESS" in line:
                ans.append("0\n")
            else:
                for text in line:
                    if text.isdigit():
                        testcase_ans += text
                ans.append(testcase_ans + "\n")

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

    exefile = "./HW/%s/1-build/%s%s" % (ID, HW, P)
    print(exefile)

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
        print("No file.\n")
        input()
        with open("./grade.csv", "a") as grade_file:
            grade_file.write(ID + ",0,No file\n")
        continue

    output = []
    os.makedirs("./HW/%s/out" % (ID), exist_ok=True)
    for testcase in range(1, 21):
        os.system(
            "%s < ./testcase/in/%d.in > ./HW/%s/out/%d.out"
            % (exefile, testcase, ID, testcase)
        )
        with open(("./HW/%s/out/%d.out" % (ID, testcase)), "r") as outfile:
            lines = outfile.readlines()
            testcase_output = ""
            for line in lines:
                if "SUCCESS" in line:
                    testcase_output = "0"
                    break
                else:
                    for text in line:
                        if text.isdigit():
                            testcase_output += text
            output.append(testcase_output + "\n")

    score = 0
    log = "wrong: "
    for i in range(20):
        print(output[i].strip(), ans[i].strip())
        if output[i].strip() == ans[i].strip():
            score += 1
        else:
            log += str(i + 1) + " "

    print("%s: %d\n%s\n" % (ID, score, log))
    input()
    with open("./grade.csv", "a") as grade_file:
        grade_file.write("%s,%d,%s\n" % (ID, score, log))
