def gnome_sort (lista: list, key=lambda x:x, reverse=False):
    ind = 0
    n = len(lista)
    while ind<n:
        if ind == 0:
            ind += 1

        val_a = key(lista[ind])
        val_b = key(lista[ind-1])

        if not reverse:
            condition = val_a < val_b
        else:
            condition = val_a > val_b

        if condition:
            lista[ind],lista[ind-1] = lista[ind-1], lista[ind]
            ind -= 1
        else:
            ind += 1

    return lista
