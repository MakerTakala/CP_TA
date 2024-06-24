import os

HW = "03"
P = "02"

ID_list = []
with open("../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

    exefile = "./HW/" + ID + "/1-build//hw" + HW + P

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

    os.system(exefile + " > ./HW/" + ID + "/out")

    out_lines = []
    ans_lines = []

    with open("./HW/" + ID + "/out", "r") as out_file:
        out_lines = out_file.readlines()
    with open("./refer_ans/ans", "r") as ans_file:
        ans_lines = ans_file.readlines()

    for out_line in out_lines:
        out_line = out_line.strip().replace(" ", "")
    for ans_line in ans_lines:
        ans_line = ans_line.strip().replace(" ", "")

    if len(out_lines) == 0:
        print(ID + "No output.\n")
        input()
        with open("./grade.csv", "a") as grade_file:
            grade_file.write(ID + ",0,No output\n")
        continue

    # return value_test
    return_score = 0
    initial_score = 0
    forward_score = 0
    turn_score = 0
    multi1_score = 0
    multi2_score = 0
    recurrsion_score = 0

    return_score = int(out_lines[0])

    # initialize_test, forward_test, turn_test
    for i in range(1, 10):
        out_text = out_lines[i]
        ans_text = ans_lines[i]
        if out_text == ans_text:
            if 1 <= i <= 3:
                initial_score += 1
            elif 4 <= i <= 6:
                forward_score += 1
            elif 7 <= i <= 9:
                turn_score += 1

    # multi_text1
    out_text = out_lines[10]
    ans_text = ans_lines[10]
    if out_text == ans_text:
        multi1_score = 2

    # multi_text2
    out_text = out_lines[11]
    ans_text = ans_lines[11]
    if out_text == ans_text:
        multi2_score = 2

    ## recurrsion_test
    recurrsion_score = 3
    for i in range(12, 20):
        out_text = out_lines[i]
        ans_text = ans_lines[i]
        if out_text != ans_text:
            recurrsion_score = 0
            break

    score = (
        return_score
        + initial_score
        + forward_score
        + turn_score
        + multi1_score
        + multi2_score
        + recurrsion_score
    )
    log = (
        "return: "
        + str(return_score)
        + "/4"
        + ", initial: "
        + str(initial_score)
        + "/3"
        + ", forward: "
        + str(forward_score)
        + "/3"
        + ", turn: "
        + str(turn_score)
        + "/3"
        + ", multi1: "
        + str(multi1_score)
        + "/2"
        + ", multi2: "
        + str(multi2_score)
        + "/2"
        + ", recurrsion: "
        + str(recurrsion_score)
        + "/3"
    )
    print(
        "return: "
        + str(return_score)
        + "/4\n"
        + "initial: "
        + str(initial_score)
        + "/3\n"
        + "forward: "
        + str(forward_score)
        + "/3\n"
        + "turn: "
        + str(turn_score)
        + "/3\n"
        + "multi1: "
        + str(multi1_score)
        + "/2\n"
        + "multi2: "
        + str(multi2_score)
        + "/2\n"
        + "recurrsion: "
        + str(recurrsion_score)
        + "/3\n"
    )

    print(ID + " " + str(score) + "\n")
    input()
    with open("./grade.csv", "a") as grade_file:
        grade_file.write(ID + "," + str(score) + "," + log + "\n")
