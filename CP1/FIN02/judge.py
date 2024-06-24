import os

CASE = 11
SCORE = [1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1]

ID_list = []
with open("../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

    exefile = "./HW/" + ID + "/1-build/fin02"

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
    for test in range(1, CASE + 1):
        os.system(f"{exefile} < ./testcase/in/{test}.in > ./HW/{ID}/out/{test}.out")

    score = 0
    log = "wrong:"

    for i in range(1, CASE + 1):
        out_line = []
        ans_line = []
        with open("./HW/" + ID + "/out/" + str(i) + ".out", "r") as out_file:
            lines = out_file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    out_line.append(line)
        with open("./testcase/ans/" + str(i) + ".ans", "r") as ans_file:
            lines = ans_file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    ans_line.append(line)

        if len(out_line) != len(ans_line):
            log += f" {i}"
            continue

        wrong = False
        for j in range(len(out_line)):
            if out_line[j] != ans_line[j]:
                wrong = True
                break
        if wrong:
            log += f" {i}"
            continue

        score += SCORE[i - 1]

    print(ID)
    print("SCORE:", score)
    print("LOG:", log)
    input()

    with open("./grade.csv", "a") as grade_file:
        grade_file.write(f"{ID},{score},{log}\n")
