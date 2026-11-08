from random import random, choice
from matplotlib.pyplot import axis, plot, show
from math import dist


corner_square = [[0.0, 0.0], [0.0, 1.0], [1.0, 1.0], [1.0, 0.0]]
center_square = [0.5, 0.5]


def cerc(point1):
    return dist(point1, center_square) <= 0.5


def corners(point1):
    mn = 22.0
    for corner in corner_square:
        mn = min(mn, dist(point1, corner))

    return dist(point1, center_square) <= mn


def obtuse_triangle(point1):

    ct = 0
    for i in range(4):
        corner1 = corner_square[i]
        corner2 = corner_square[(i+1) % 4]

        if (dist(point1, corner1)**2 + dist(point1, corner2)**2) < 1:
            ct += 1

    return ct == 2


def lower_bar(point1):
    return dist(point1, center_square) < point1[1]


def problema_patrat(nr_puncte, cerinta):
    freq = 0
    for i in range(0, N):
        x = random()
        y = random()
        if cerinta([x, y]):
            freq += 1
            plot([x], [y], 'ro')
    print(f"Probabilitatea relativa: {freq/N}")


axis((0, 1, 0, 1))


_l = [500, 1000, 2000]
N = choice(_l)

problema_patrat(N, lower_bar)


show()
