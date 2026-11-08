from scipy.stats import binom
from matplotlib.pyplot import bar, hist, grid, show, legend

random_numbers = binom.rvs(5, 0.6, size=1000)
bin_edges = [k + 0.5 for k in range(-1, 6)]

hist(random_numbers, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'frecvente relative')

distribution = dict( [ (k, binom.pmf(k, 5, 0.6)) for k in range(6)])

bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black', alpha = 0.6, label = 'probabilitati')


fq = {3: 0,
      4: 0,
      5: 0,
      }
for elem in random_numbers:
    if elem >= 3:
        fq[elem] += 1

sum = 0
for elem in fq.values():
    sum += elem

prob = sum / 1000
print(f"Probabilitate experimentata la 2 < X <=5 : {prob}")

prob_t = 0

for key in distribution:
    if key >= 3:
        prob_t += distribution[key]

print(f"Prob teoretica la 2 < X <= 5 : {prob_t}")

grid()
show()

