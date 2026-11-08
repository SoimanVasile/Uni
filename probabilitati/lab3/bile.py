from random import sample
from math import comb


def prob_cond(nr_sim):
    countA, countB = 0, 0
    for _ in range(nr_sim):
        bile_extrase = sample(['red', 'blue', 'green'], counts = [5, 3, 2], k = 3)
        if 'red' in bile_extrase:
            countA += 1
            if len(set(bile_extrase)) == 1:
                countB += 1
    return countB/countA


res = prob_cond(50000)
print(f"Probabilitatea experiemntala: {res}")

prob_A_in_B = comb(5, 3) / comb(10, 3)
prob_A = 1 - comb(5, 3) / comb(10, 3)

teoretic_prob = prob_A_in_B / prob_A

print(f"Probabilitatea teoretica: {teoretic_prob}")
