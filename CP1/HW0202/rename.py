import os

for dir in os.scandir("./HW"):
    # os.system("tar -xzvf" + dir.path + " -C ./HW")
    # os.rename(dir.path, "./HW/" + dir.name[0:9])
    # print(dir.path)
    os.system("chmod 777 " + dir.path + "/hw0202")
