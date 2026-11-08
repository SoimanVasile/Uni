from itertools import combinations_with_replacement


inghetata = "ACFKWVZ"
vec = list(combinations_with_replacement(inghetata, 3))

print(vec)
print(f"Numar de combinari: {len(vec)}")
