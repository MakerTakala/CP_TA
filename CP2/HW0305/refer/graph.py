import cv2
import matplotlib.pyplot as plt

img = cv2.imread("./Image/cat.jpg")

color = ["b", "g", "r"]
name = ["Blue.jpg", "Green.jpg", "Red.jpg"]
for i, col in enumerate(color):
    histr = cv2.calcHist([img], [i], None, [256], [0, 256]).squeeze()
    data = []
    for j in range(256):
        for k in range(int(histr[j])):
            data.append(j)
    plt.hist(data, color=col, bins=256, range=(0, 256))
    plt.savefig("Image/" + name[i])
    plt.clf()
