import os

ID_list = []
with open("./../../namelist.csv", "r") as IDfile:
    ID_list = IDfile.readlines()
ID_list.sort()

for ID in ID_list:
    ID = ID.strip()
    os.system("clear")

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
    exefile = f"./HW/{ID}/1-build/hw0104"

    if not os.path.isfile(exefile):
        print(ID + "No file or compile fail\n")
        input()
        with open("./grade.csv", "a") as grade_file:
            grade_file.write(f"{ID},0,No file or compile fail\n")
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
