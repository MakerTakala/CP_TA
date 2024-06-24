import os

for dir in os.scandir("./HW"):
    os.rename("./HW/" + dir.name, "./HW/" + dir.name[0:9])
