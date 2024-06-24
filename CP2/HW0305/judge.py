import os

TESTCASE = [
    "-i ./testcase/maldives.bmp -o ./output1.bmp -w 1600 -h 800 -l 5",
    "-i ./testcase/cat.bmp -o ./output2.bmp -w 1600 -h 800 -l 3",
]
HOMEWORK = "hw0305"


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

def write_grade(id_number, score, log):
    """Write the grade to grade.csv"""
    with open("./grade.csv", "a", encoding="utf-8") as grade_file:
        grade_file.write(f"{id_number},{score},{log}\n")


def main():
    """Main function of the judge.py"""
    id_list = get_id_list()

    for id_number in map(str.strip, id_list):
        os.system("clear")
        if os.path.isfile("./output1.bmp"):
            os.remove("./output1.bmp", )
        if os.path.isfile("./output2.bmp"):
            os.remove("./output2.bmp")
        print(id_number)
        if check_have_grade(id_number):
            continue

        exefile = f"./HW/{id_number}/1-build/{HOMEWORK}"
        if not os.path.isfile(exefile):
            print("No file or compile fail or segmentation fault\n")
            input()
            write_grade(id_number, 0, "No file or compile fail or segmentation fault")
            continue
        
        if not os.path.isfile("./output1.bmp") and os.path.isfile("./output2.bmp"):
            print("No generate image\n")
            input()
            write_grade(id_number, 0, "No generate image")
            continue
        
        score = 0

        for i, testcase in enumerate(TESTCASE):
            os.system(f"{exefile} {testcase}")
        log = input("Log: ")
        score = int(input("Score: "))
       

        os.system("clear")
        print(f"\n{id_number}:\n")
        print(f"SCORE: {score}")
        print(f"LOG: {log}")
        input()
        write_grade(id_number, score, log)


if __name__ == "__main__":
    main()
