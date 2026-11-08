from random import sample
from itertools import permutations
from math import factorial

vec = permutations("randomise", 9)


perms_list = list(vec)
print("Toate permutarile: ")
for elem in perms_list:
    print(elem)


val = factorial(9)
print(f"Numaru de permutari este egal cu: {val}")


print("Random permutation: ", sample("randomise", len("randomise")))
