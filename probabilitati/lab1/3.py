from random import sample
from math import perm, comb
from itertools import permutations, combinations


def aranjamente(word: str, k: int, numar_total=False, aleator=False):
    if numar_total:
        return perm(len(word), k)

    if aleator:
        return sample(word, k)

    return list(permutations(word, k))


def combinari(word: str, k: int, numar_total=False, aleator=False):
    if numar_total:
        return comb(len(word), k)

    if aleator:
        return sample(word, k)

    return list(combinations(word, k))


print(aranjamente('word', 2))
print(aranjamente('word', 2, numar_total=True))
print(aranjamente("word", 3, aleator=True))

print("Combinari")

print(combinari('word', 2))
print(combinari('word', 2, numar_total=True))
print(combinari('word', 2, aleator=True))
