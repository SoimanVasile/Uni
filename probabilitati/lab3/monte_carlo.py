import random

n = 100
number_sim = 10000
ct = 0

for i in range(number_sim):
    k = random.randint(1, n)
    sample = list(random.sample(range(1, 101), k))

    m = max(sample)

    if m == 100:
        ct += 1


prob = ct / number_sim

print(f"Prob experimentala ca output sa fie 100: {prob}")

prob_t = (n * (n + 1) / 2) / 1e4

print(f"Prob teoretica: {prob_t}")
