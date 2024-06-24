import os
import itertools
import shutil


def move(destination):
    all_files = []
    for root, _dirs, files in itertools.islice(os.walk(destination), 1, None):
        for filename in files:
            all_files.append(os.path.join(root, filename))
    for filename in all_files:
        if not os.path.isfile(filename):
            shutil.move(filename, destination)


for dir in os.scandir("./HW"):
    print(f"Moving {dir.path}...")
    move(f"{dir.path}/0-raw/")
