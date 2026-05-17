def quick_sort(lista: list, key=lambda x: x, reverse=False):
    quick_sort_helper(lista, 0, len(lista)-1, key, reverse)
    return lista

def quick_sort_helper(lista: list, low:int, high: int, key, reverse):
    if low<high:

        pi = partition(lista, low, high, key, reverse)

        lista = quick_sort_helper(lista, low, pi-1, key, reverse)
        lista = quick_sort_helper(lista, pi+1, high, key, reverse)

    return lista

def partition(lista, low, high, key, reverse):
    pivot = lista[high]
    i = low
    for ind in range(low,high):
        val_ind = key(lista[ind])
        val_pivot = key(pivot)

        if not reverse:
            condition = val_ind <= val_pivot
        else:
            condition = val_ind >= val_pivot

        if condition:
            lista[i], lista[ind] = lista[ind], lista[i]
            i += 1

    lista[i], lista[high] = lista[high], lista[i]
    return i
