from functionalitati import *
from structura import verificare_cheltuiala


def afisare_comenzi():
    pass


def ui_inserare(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 3:
        raise ValueError("numar de parametri invalid")

    ziua = int(parametri_comanda[0])
    suma = float(parametri_comanda[1])
    tip = parametri_comanda[2]

    cheltuiala = {"ziua": ziua, "suma": suma, "tip": tip}
    try:
        verificare_cheltuiala(cheltuiala)
        return inserare(lista_cheltuieli, ziua, suma, tip, stiva_stari_cheltuieli)
    except ValueError as eroare:
        print(eroare)

    return [lista_cheltuieli, stiva_stari_cheltuieli]


def ui_actualizare(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 3:
        raise ValueError("numar de parametri invalid")

    ziua = int(parametri_comanda[0])
    suma = float(parametri_comanda[1])
    tip = parametri_comanda[2]

    cheltuiala = {"ziua": ziua, "suma": suma, "tip": tip}
    try:
        verificare_cheltuiala(cheltuiala)
        return actualizare(lista_cheltuieli, ziua, suma, tip, stiva_stari_cheltuieli)
    except ValueError as eroare:
        print(eroare)

    return [lista_cheltuieli, stiva_stari_cheltuieli]


def ui_stergere_cheltuieli_din_ziua_p(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    ziua = int(parametri_comanda[0])

    cheltuiala = {"ziua": ziua, "suma": 1, "tip": "altele"}
    try:
        verificare_cheltuiala(cheltuiala)
        return stergere_cheltuieli_din_ziua_p(lista_cheltuieli, ziua, stiva_stari_cheltuieli)
    except ValueError as eroare:
        print(eroare)

    return [lista_cheltuieli, stiva_stari_cheltuieli]


def ui_stergere_cheltuieli_din_intervalul_ziua1_ziua2(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 2:
        raise ValueError("numar de parametri invalid")

    ziua1 = int(parametri_comanda[0])
    ziua2 = int(parametri_comanda[1])

    cheltuiala1 = {"ziua": ziua1, "suma": 1, "tip": "altele"}
    cheltuiala2 = {"ziua": ziua2, "suma": 1, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala1)
        verificare_cheltuiala(cheltuiala2)
        return stergere_cheltuieli_din_intervalul_ziua1_ziua2(lista_cheltuieli, ziua1, ziua2, stiva_stari_cheltuieli)
    except ValueError as eroare:
        print(eroare)

    return [lista_cheltuieli, stiva_stari_cheltuieli]


def ui_stergere_cheltuieli_dupa_tip(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    tip = parametri_comanda[0]

    cheltuiala = {"ziua": 1, "suma": 1, "tip": tip}
    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    return stergere_cheltuieli_dupa_tip(lista_cheltuieli, tip, stiva_stari_cheltuieli)


def ui_cheltuieli_mai_mari_decat_sumap(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    suma = float(parametri_comanda[0])

    cheltuiala = {"ziua": 1, "suma": suma, "tip": "altele"}
    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    subsir = cheltuieli_mai_mari_decat_sumap(lista_cheltuieli, suma)
    print(subsir)


def ui_cheltuieli_mai_mici_sumap_inainte_ziuap(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 2:
        raise ValueError("numar de parametri invalid")

    ziua = int(parametri_comanda[0])
    suma = float(parametri_comanda[1])

    cheltuiala = {"ziua": ziua, "suma": suma, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    print("NIGGA    ", lista_cheltuieli)
    subsir = cheltuieli_mai_mici_sumap_inainte_ziuap(
        lista_cheltuieli, ziua, suma)
    print(subsir)


def ui_cheltuieli_dupa_tip(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    tip = parametri_comanda[0]

    cheltuiala = {"ziua": 1, "suma": 1, "tip": tip}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    subsir = cheltuieli_dupa_tip(lista_cheltuieli, tip)
    print(subsir)


def ui_suma_totala_dupa_tip(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    tip = parametri_comanda[0]
    cheltuiala = {"ziua": 1, "suma": 1, "tip": tip}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)
    total = suma_totala_dupa_tip(lista_cheltuieli, tip)
    print(total)


def ui_max_suma_dupa_zii(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 0:
        raise ValueError("numar de parametri invalid")

    cheltuiala = {"ziua": 1, "suma": 1, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)
    max = max_suma_dupa_zii(lista_cheltuieli)
    print(max)


def ui_cheltuiala_cu_sumap(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    suma = float(parametri_comanda[0])
    cheltuiala = {"ziua": 1, "suma": suma, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)
    return cheltuiala_cu_sumap(lista_cheltuieli, suma)


def ui_sortare_lista_cheltuieli_dupa_tip(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_stari_cheltuieli = context["stiva"]
    if len(parametri_comanda) != 0:
        raise ValueError("numar de parametri invalid")

    cheltuiala = {"ziua": 1, "suma": 1, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)
    return sortare_lista_cheltuieli_dupa_tip(lista_cheltuieli, stiva_stari_cheltuieli)


def ui_filtrarea_cheltuielilor_cu_tip_p(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    tip = parametri_comanda[0]
    cheltuiala = {"ziua": 1, "suma": 1, "tip": tip}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    subsir = filtrarea_cheltuielilor_cu_tip_p(lista_cheltuieli, tip)
    print(subsir)


def ui_filtrarea_cheltuielilor_cu_suma_mai_mica_sumap(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    if len(parametri_comanda) != 1:
        raise ValueError("numar de parametri invalid")

    suma = float(parametri_comanda[0])
    cheltuiala = {"ziua": 1, "suma": suma, "tip": "altele"}

    try:
        verificare_cheltuiala(cheltuiala)
    except ValueError as eroare:
        print(eroare)

    subsir = filtrarea_cheltuielilor_cu_suma_mai_mica_sumap(
        lista_cheltuieli, suma)
    print(subsir)


def ui_undo(context):
    lista_cheltuieli = context["lista_cheltuieli"]
    parametri_comanda = context["parametri"]
    stiva_start = context["stiva"]
    if len(parametri_comanda) != 0:
        raise ValueError("numar de parametri invalid")

    rezultat = undo(stiva_start)
    lista_cheltuieli = rezultat[0]
    stiva_start = rezultat[1]

    return [lista_cheltuieli, stiva_start]


def help():
    print(
        "1. inserare {ziua} {suma} {tip} - insereaza o cheltuiala noua in lista cu parametrii dati")
    print("2. actualizare {ziua} {suma} {tip} - actualizeaza cheltuiala care are ziua si tipul la fel cu suma data, dar daca nu ii nu se intampla nimica")
    print(
        "3. stergere_dupa_zi {ziua} - sterge toate cheltuielile din ziua {ziua}")
    print(
        "4. stergere_din_2zile {ziua1} {ziua2} - sterge toate cheltuielile din intervalul [min(ziua1,ziua2),max(ziua1,ziua2)")
    print(
        "5. stergere_dupa_tip {tip} - sterge toate cheltuielile de tipul {tip}")
    print("6. sortare_dupa_tip - sorteaza lista de cheltuieli dupa tip, zii, suma")
    print(
        "7. filtreaza_dupa_tip {tip} - elimina toate cheltuielile care au tipul {tip}")
    print(
        "8. filtrarea_mici_suma {suma} - elimina toate cheltuielile mai mici decat suma {suma}")
    print(
        "9. afiseaza_mare_suma {suma} - afiseaza toate cheltuielile care au suma strict mai mare decat {suma}")
    print(
        "10. afiseaza_mici_suma_inainte_zi {ziua} {suma} - afiseaza toate cheltuielile care au ziua mai mica decat {ziua} si suma mai mica decat {suma}")
    print(
        "11. afiseaza_dupa_tip {tip} - afiseaza toate cheltuielile care au tipul {tip}")
    print("12. afiseaza_zi_suma_maxima - afiseaza ziua care are suma maxima")
    print(
        "13. afiseaza_cu_suma_egala {suma} - afiseaza toate cheltuielile care au suma egala cu {suma}")
    print("14. undo - reia lista inainte de ultima schimbare")
    print("14. exit - se inchide programu")


def run():
    lista_cheltuieli = []
    stiva_stare_cheltuieli = []
    comenzi_modificare = {
        "inserare": ui_inserare,
        "actualizare": ui_actualizare,
        "stergere_dupa_zi": ui_stergere_cheltuieli_din_ziua_p,
        "stergere_din_2zile": ui_stergere_cheltuieli_din_intervalul_ziua1_ziua2,
        "stergere_dupa_tip": ui_stergere_cheltuieli_dupa_tip,
        "sortare_dupa_tip": ui_sortare_lista_cheltuieli_dupa_tip,
        "undo": ui_undo,
    }
    comenzi_afisare = {
        "afiseaza_mare_suma": ui_cheltuieli_mai_mari_decat_sumap,
        "afiseaza_mici_suma_inainte_zi": ui_cheltuieli_mai_mici_sumap_inainte_ziuap,
        "afiseaza_dupa_tip": ui_cheltuieli_dupa_tip,
        "afiseaza_suma_totala_tip": ui_suma_totala_dupa_tip,
        "afiseaza_zi_suma_maxima": ui_max_suma_dupa_zii,
        "afiseaza_cu_suma_egala": ui_cheltuiala_cu_sumap,
        "filtrare_dupa_tip": ui_filtrarea_cheltuielilor_cu_tip_p,
        "filtrare_mici_suma": ui_filtrarea_cheltuielilor_cu_suma_mai_mica_sumap
    }
    while True:
        print(lista_cheltuieli)
        print(stiva_stare_cheltuieli)
        text_comanda = input(">>>")
        text_comanda = text_comanda.strip()
        if text_comanda == "":
            continue
        if text_comanda == "exit":
            print("Sayonara, user!")
            break
        if text_comanda == "help":
            help()
            continue
        elemente_comanda = text_comanda.split()
        nume_comanda = elemente_comanda[0]
        parametri_comanda = elemente_comanda[1:]
        if nume_comanda in comenzi_modificare:
            context = {
                "lista_cheltuieli": lista_cheltuieli,
                "parametri": parametri_comanda,
                "stiva": stiva_stare_cheltuieli
            }
            try:
                raspuns = comenzi_modificare[nume_comanda](context)
                lista_cheltuieli = raspuns[0].copy()
                stiva_stare_cheltuieli = raspuns[1].copy()
            except ValueError as eroare:
                print(eroare)
        elif nume_comanda in comenzi_afisare:
            context = {
                "lista_cheltuieli": lista_cheltuieli,
                "parametri": parametri_comanda
            }
            try:
                comenzi_afisare[nume_comanda](context)
            except ValueError as eroare:
                print(eroare)
        else:
            print("nu am aceasta comanda")


def main():
    run()


if __name__ == "__main__":
    main()
