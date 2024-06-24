import os

HW = "05"
P = "03"

ID_list = []
with open("../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

    exefile = "./HW/" + ID + "/1-build/hw" + HW + P

    with open("./grade.csv", "r") as grade_file:
        grade_line = grade_file.readlines()
        have_ID = False
        for text in grade_line:
            if ID in text:
                have_ID = True
                break
        if have_ID:
            continue

    print(ID + ":\n\n")

    if not os.path.isfile(exefile):
        print(ID + "No file.\n")
        input()
        with open("./grade.csv", "a") as grade_file:
            grade_file.write(f"{ID},0,No file\n")
        continue

    os.system(exefile + " > ./HW/" + ID + "/out")

    score = 0
    log = ""
    with open("./HW/" + ID + "/out", "r") as outfile:
        out_line = outfile.readlines()
        if len(out_line) != 2:
            print(f"{ID}:Duplicate or less output\n")
            input()
            with open("./grade.csv", "a") as grade_file:
                grade_file.write(f"{ID},0,Duplicate output\n")
            continue
        score = int(out_line[0])
        log = out_line[1]
    print(ID)
    print("SCORE:", score)
    print("LOG:", log)
    input()

    with open("./grade.csv", "a") as grade_file:
        grade_file.write(f"{ID},{score},{log}\n")
