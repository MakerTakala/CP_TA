import os

TESTCASE = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
SCORE = [2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1]
HOMEWORK = "hw0203"


def get_id_list():
    with open("./../../namelist.csv", "r") as IDfile:
        ID_list = IDfile.readlines()
    for i in range(len(ID_list)):
        ID_list[i] = ID_list[i].strip()
    return ID_list


def check_have_grade(ID):
    with open("./grade.csv", "r") as grade_file:
        grade_line = grade_file.readlines()
        have_ID = False
        for text in grade_line:
            if ID in text:
                have_ID = True
                break
        return have_ID


def excute_exefile(ID, i):
    os.system(
        f"./HW/{ID}/1-build/{HOMEWORK} < ./testcase/{i}.in > ./HW/{ID}/out/{i}.out"
    )


def compare_output(ID, i):
    ans_line = []
    out_line = []

    with open(f"./HW/{ID}/out/{i}.out", "r") as outfile:
        lines = outfile.readlines()
        for line in lines:
            line = line.strip().replace(" ", "")
            if line != "":
                out_line.append(line)

    with open(f"./testcase/{i}.out", "r") as ansfile:
        lines = ansfile.readlines()
        for line in lines:
            line = line.strip().replace(" ", "")
            if line != "":
                ans_line.append(line)

    if len(out_line) != len(ans_line):
        return False
    for j in range(len(out_line)):
        if out_line[j] != ans_line[j]:
            return False

    return True


def show_output(ID, i):
    os.system("clear")
    with open(f"./HW/{ID}/out/{i}.out", "r") as outfile:
        lines = outfile.readlines()
        for line in lines:
            print(line.strip())
    print("\n\n--------------------\n\n")
    with open(f"./testcase/{i}.out", "r") as ansfile:
        lines = ansfile.readlines()
        for line in lines:
            print(line.strip())

    print("\n\n--------------------\n\n")


def write_grade(ID, score, log):
    with open("./grade.csv", "a") as grade_file:
        grade_file.write(f"{ID},{score},{log}\n")


if __name__ == "__main__":

    id_list = get_id_list()

    for id in id_list:
        os.system("clear")
        if check_have_grade(id):
            continue

        exefile = f"./HW/{id}/1-build/{HOMEWORK}"
        print(id + ":\n\n")

        if not os.path.isfile(exefile):
            print("No file or compile fail or segmentation fault\n")
            input()
            write_grade(id, 0, "No file or compile fail or segmentation fault")
            continue

        os.makedirs(f"./HW/{id}/out", exist_ok=True)

        score = 0
        log = "WRONG: "

        for i in TESTCASE:
            excute_exefile(id, i)
            if compare_output(id, i):
                print(f"Testcase {i}: Correct")
                score += SCORE[i]
            else:
                print(f"Testcase {i}: Wrong")
                log += f"T{i} "

        os.system("clear")
        print(id + ":\n\n")
        print("SCORE:", score)
        print("LOG:", log)
        input()
        write_grade(id, score, log)
