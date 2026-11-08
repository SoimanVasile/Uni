from random import randint
from matplotlib.pyplot import plot, grid, xticks, yticks, suptitle, show, ylabel, xlabel, subplot, scatter, figure, title, bar

sum_counts1 = {total: 0 for total in range(3, 19)}
sum_counts2 = {total: 0 for total in range(3, 19)}
win = {total: 0 for total in range(1, 3)}

for i in range(100000):
    sum1 = 0
    sum2 = 0
    for j in range(3):
        sum1 += randint(1, 6)

    sum_counts1[sum1] += 1

    for j in range(3):
        sum2 += randint(1, 6)

    sum_counts2[sum2] += 1


figure(figsize=(6, 2))

subplot(131)
bar(sum_counts1.keys(), sum_counts1.values())
subplot(132)
bar(sum_counts2.keys(), sum_counts2.values())
# ylabel("Frecventa")
# xlabel("Suma")

show()
