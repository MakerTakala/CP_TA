"""Judge the homework of the students"""

import os
import re

TESTCASE = [0, 1, 2, 3, 4, 5, 6, 7, 8]
SCORE = [3, 3, 3, 3, 3, 3, 3, 2, 2]
HOMEWORK = "mid01"
compare = re.compile(r"\[[-\[0-9,\]]*\]")
error_compare = re.compile(r"(?<=:)?([^:]+)$")


def get_id_list():
    """Get id_number list from namelist.csv"""
    with open("./../../namelist.csv", "r", encoding="utf-8") as id_file:
        id_list = id_file.readlines()
    for id_number in id_list:
        id_number = id_number.strip()
    return id_list


def check_have_grade(id_number):
    """Check if the id_number has been graded"""
    with open("./grade.csv", "r", encoding="utf-8") as grade_file:
        grade_line = grade_file.readlines()
        have_id = False
        for text in grade_line:
            if id_number in text:
                have_id = True
                break
        return have_id


def excute_exefile(id_number, i):
    """Excute the exefile with testcase i"""
    os.system(
        f"./HW/{id_number}/1-build/{HOMEWORK} < ./testcase/{i}.in > ./HW/{id_number}/out/{i}.out"
    )


def compare_output(id_number, testcase):
    """Compare the output of the exefile with the answer file"""
    ans_line = ""
    out_line = ""

    with open(f"./testcase/{testcase}.out", "r", encoding="utf-8") as ansfile:
        line = ansfile.read().strip().replace(" ", "").lower()
        if compare.search(line) is not None:
            ans_line = compare.search(line).group()
        elif error_compare.search(line) is not None:
            ans_line = error_compare.search(line).group()
        else:
            return False

    with open(f"./HW/{id_number}/out/{testcase}.out", "r", encoding="utf-8") as outfile:
        line = outfile.read().strip().replace(" ", "").lower()
        if compare.search(line) is not None:
            out_line = compare.search(line).group()
        elif error_compare.search(line) is not None:
            out_line = error_compare.search(line).group()
        else:
            return False

    return ans_line == out_line


def show_output(id_number, testcase):
    """Show the output of the exefile and the answer file"""
    os.system("clear")

    print(f"Checking {id_number} T{testcase}...\n")
    print("--------------------")
    print("ANSWER: ")
    print("--------------------")
    with open(f"./testcase/{testcase}.out", "r", encoding="utf-8") as ansfile:
        line = ansfile.read().strip().replace(" ", "").lower()
        if compare.search(line) is not None:
            ans_line = compare.search(line).group()
        elif error_compare.search(line) is not None:
            ans_line = error_compare.search(line).group()
        else:
            return False
        print(ans_line)

    print("--------------------")
    print("\n\n")
    print("--------------------")
    print("OUTPUT: ")
    print("--------------------")
    with open(f"./HW/{id_number}/out/{testcase}.out", "r", encoding="utf-8") as outfile:
        line = outfile.read().strip().replace(" ", "").lower()
        if compare.search(line) is not None:
            out_line = compare.search(line).group()
        elif error_compare.search(line) is not None:
            out_line = error_compare.search(line).group()
        else:
            return False
        print(out_line)

    print("--------------------")


def write_grade(id_number, score, log):
    """Write the grade to grade.csv"""
    with open("./grade.csv", "a", encoding="utf-8") as grade_file:
        grade_file.write(f"{id_number},{score},{log}\n")


def main():
    """Main function of the judge.py"""
    id_list = get_id_list()

    for id_number in id_list:
        id_number = id_number.strip()
        os.system("clear")
        if check_have_grade(id_number):
            continue

        exefile = f"./HW/{id_number}/1-build/{HOMEWORK}"
        print(id_number + ":\n\n")

        if not os.path.isfile(exefile):
            print("No file or compile fail or segmentation fault\n")
            input()
            write_grade(id_number, 0, "No file or compile fail or segmentation fault")
            continue

        os.makedirs(f"./HW/{id_number}/out", exist_ok=True)

        score = 0
        log = "WRONG: "

        for testcase in TESTCASE:

            excute_exefile(id_number, testcase)

            if compare_output(id_number, testcase):
                score += SCORE[testcase]
            else:
                # show_output(id_number, testcase)
                # input()
                log += f"T{testcase} "

        os.system("clear")
        print(id_number + ":\n\n")
        print("SCORE:", score)
        print("LOG:", log)
        input()
        write_grade(id_number, score, log)


if __name__ == "__main__":
    main()
