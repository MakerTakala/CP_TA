import os

for i in range(11):
    os.system(f"cd ./refer && ./hw0203 < ../testcase/{i}.in > ../testcase/{i}.out")
