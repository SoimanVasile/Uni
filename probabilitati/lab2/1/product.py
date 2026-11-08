from itertools import product
from random import randint
from matplotlib.pyplot import plot, grid, xticks, yticks, title, show


sum_counts = {total: 0 for total in range(3, 19)}

for roll in product(range(1,7), repeat=3):
    (a, b, c) = roll
    sum_counts[a + b + c] += 1


plot(sum_counts.keys(), sum_counts.values(), 'ro')

show()
