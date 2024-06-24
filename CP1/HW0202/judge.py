import os

HW = "02"
P = "02"

for dir in os.scandir("./HW"):
    os.system("clear")

    if dir.name == ".DS_Store":
        continue
    ID = dir.name
    exefile = "./HW/" + dir.name + "/hw" + HW + P

    grade_file = open("./grade.csv", "r")
    grade_line = grade_file.readlines()
    have_ID = False
    for text in grade_line:
        if ID in text:
            have_ID = True
            break
    grade_file.close()
    if have_ID:
        continue

    c_file_name = "./HW/" + ID + "/hw" + HW + P + ".c"
    if not os.path.isfile(c_file_name):
        print(ID + "No C file.\n")
        input()
    else:
        c_file = open(c_file_name, "r")
        c_line = c_file.readlines()

        ban_word = False
        for text in c_line:
            if text.find("[") != -1 or text.find("]") != -1:
                ban_word = True
                break
        if ban_word:
            print(ID + " have [](y/n)\n")
            yorn = input()
            if yorn == "y":
                grade_file = open("./grade.csv", "a")
                grade_file.write(ID + ",0\n")
                grade_file.close()
                log = open("./log", "a")
                log.write(ID + ", use Array\n")
                log.close()
                continue

    if not os.path.isfile(exefile):
        print(ID + "No file.\n")
        grade_file = open("./grade.csv", "a")
        grade_file.write(ID + ",0\n")
        grade_file.close()
        input()
        continue

    os.makedirs("./HW/" + ID + "/out", exist_ok=True)
    for test in os.scandir("./testcase/in"):
        in_testname = test.name
        out_testname = test.name.replace(".in", ".out")
        os.system(
            exefile
            + " < ./testcase/in/"
            + test.name
            + " > ./HW/"
            + ID
            + "/out/"
            + out_testname
        )

    for out in os.scandir("./HW/" + ID + "/out"):
        out_file = open("./HW/" + ID + "/out/" + out.name, "r")
        out_lines = out_file.readlines()
        out_file.close()

        after_colon_space = False
        tmp_index = out_lines[0].find(": ")
        if tmp_index != -1:
            if out_lines[0].find(":", tmp_index + 1) != -1:
                after_colon_space = True

        if after_colon_space:
            out_lines[0] = out_lines[0].split(": ")[-1]
        else:
            out_lines[0] = out_lines[0].split(":")[-1]

        out_file = open("./HW/" + ID + "/out/" + out.name, "w")
        for text in out_lines:
            intext = text.rstrip() + "\n"
            intext = intext.replace("—", "-")
            out_file.write(intext)
        if "\n" not in out_lines[-1]:
            out_file.write("\n")
        out_file.close()

    score = 0
    wrong_number = []
    for out in os.scandir("./HW/" + ID + "/out"):
        out_file = open("./HW/" + ID + "/out/" + out.name, "r")
        ans_file = open("./testcase/ans/" + str(out.name).replace(".out", ".ans"), "r")

        out_line = out_file.readlines()
        ans_line = ans_file.readlines()
        out_file.close()
        ans_file.close()

        Same = True
        counter = 0
        for i in range(min(len(out_line), len(ans_line))):
            if out_line[i] != ans_line[i]:
                for j in range(min(len(out_line[i]), len(ans_line[i]))):
                    if out_line[i][j] != ans_line[i][j]:
                        counter += 1
                print("DIFF:", "\n", out_line[i], ans_line[i])
                Same = False

        if Same:
            score += 2
        else:
            this_score = 0
            print(
                "=============================================================================================="
            )
            print(ID + " Output:")
            print("Ans:")
            print("'''")
            for text in ans_line:
                print(text, end="")
            print("'''\n")
            print("\nOutput:")
            print("'''")
            for text in out_line:
                print(text, end="")
            print("'''\n")

            print("Counter:", counter)
            print("Score(0-2) (", this_score, "):", end="")
            in_score = input()
            if in_score != "":
                this_score = int(in_score)
            score += this_score
            if this_score < 2:
                wrong_number.append("t" + out.name[3:5])

            os.system("clear")
    if score < 20:
        log = open("./log", "a")
        log.write(ID + ",")
        for wrong in wrong_number:
            log.write(wrong + " ")
        log.write("\n")
        log.close()

    print(ID + " Score: " + str(score) + "\n")
    input()
    grade_file = open("./grade.csv", "a")
    grade_file.write(ID + "," + str(score) + "\n")
    grade_file.close()
