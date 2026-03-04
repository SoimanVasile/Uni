from functionalitati import *

def test_inserare():
    lista = []
    stiva = []
    lista, stiva = inserare(lista, 10, 100.0, "mancare", stiva)
    assert lista == [{"ziua": 10, "suma": 100.0, "tip": "mancare"}]
    assert len(stiva) == 1

def test_actualizare():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 20.0, "tip": "mancare"}
    ]
    stiva = []
    lista, stiva = actualizare(lista, 1, 50.0, "altele", stiva)
    assert any(c["ziua"] == 1 and abs(c["suma"] - 50.0) < 1e-6 for c in lista)
    assert len(stiva) == 1

def test_stergere_cheltuieli_din_ziua_p():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 15.0, "tip": "mancare"},
        {"ziua": 1, "suma": 40.0, "tip": "telefoane"},
    ]
    stiva = []
    lista, stiva = stergere_cheltuieli_din_ziua_p(lista, 1, stiva)
    assert all(c["ziua"] != 1 for c in lista)
    assert len(stiva) == 1


def test_stergere_cheltuieli_din_intervalul_ziua1_ziua2():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 3, "suma": 20.0, "tip": "mancare"},
        {"ziua": 5, "suma": 30.0, "tip": "telefoane"},
    ]
    stiva = []
    rezultat = stergere_cheltuieli_din_intervalul_ziua1_ziua2(lista, 1, 3, stiva)
    lista = rezultat[0]
    stiva = rezultat[1]
    assert all(c["ziua"] > 3 for c in lista)
    assert len(stiva) == 1


def test_stergere_cheltuieli_dupa_tip():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 20.0, "tip": "mancare"},
        {"ziua": 3, "suma": 30.0, "tip": "altele"},
    ]
    stiva = []
    lista, stiva = stergere_cheltuieli_dupa_tip(lista, "altele", stiva)
    assert all(c["tip"] != "altele" for c in lista)
    assert len(stiva) == 1

def test_cheltuieli_mai_mari_decat_sumap():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 200.0, "tip": "mancare"},
    ]
    rezultat = cheltuieli_mai_mari_decat_sumap(lista, 100)
    assert rezultat == [{"ziua": 2, "suma": 200.0, "tip": "mancare"}]

def test_cheltuieli_mai_mici_sumap_inainte_ziuap():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 3, "suma": 50.0, "tip": "mancare"},
        {"ziua": 5, "suma": 30.0, "tip": "telefoane"},
    ]
    rezultat = cheltuieli_mai_mici_sumap_inainte_ziuap(lista, 4, 40)
    print(rezultat)
    assert rezultat == [{"ziua":1,"suma":10.0,"tip":"altele"}]

def test_cheltuieli_dupa_tip():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 20.0, "tip": "mancare"},
        {"ziua": 3, "suma": 30.0, "tip": "mancare"},
    ]
    rezultat = cheltuieli_dupa_tip(lista, "mancare")
    assert all(c["tip"] == "mancare" for c in rezultat)

def test_suma_totala_dupa_tip():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "mancare"},
        {"ziua": 2, "suma": 20.0, "tip": "mancare"},
        {"ziua": 3, "suma": 50.0, "tip": "altele"},
    ]
    rezultat = suma_totala_dupa_tip(lista, "mancare")
    assert abs(rezultat - 30.0) < 1e-6

def test_max_suma_dupa_zii():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 200.0, "tip": "mancare"},
        {"ziua": 2, "suma": 50.0, "tip": "altele"},
    ]
    rezultat = max_suma_dupa_zii(lista)
    assert rezultat == 2

def test_cheltuiala_cu_sumap():
    lista = [
        {"ziua": 1, "suma": 10.0, "tip": "altele"},
        {"ziua": 2, "suma": 20.0, "tip": "mancare"},
        {"ziua": 3, "suma": 10.0, "tip": "telefoane"},
    ]
    rezultat = cheltuiala_cu_sumap(lista, 10.0)
    assert all(abs(c["suma"] - 10.0) < 1e-6 for c in rezultat)

def test_sortare_lista_cheltuieli_dupa_tip():
    lista = [
        {"ziua": 5, "suma": 10.0, "tip": "telefoane"},
        {"ziua": 3, "suma": 5.0, "tip": "altele"},
        {"ziua": 2, "suma": 7.0, "tip": "mancare"},
    ]
    stiva = []
    rezultat = sortare_lista_cheltuieli_dupa_tip(lista, stiva)
    # verify sorting order by tip then ziua then suma
    tipuri = [c["tip"] for c in rezultat]
    assert tipuri == sorted(tipuri)

def test_undo():
    stiva = [
        [{"ziua": 1, "suma": 10.0, "tip": "altele"}],
        [{"ziua": 1, "suma": 10.0, "tip": "altele"},
         {"ziua": 2, "suma": 20.0, "tip": "mancare"}],
    ]
    rezultat, stiva_actualizata = undo(stiva)
    assert rezultat == [{"ziua": 1, "suma": 10.0, "tip": "altele"},
                        {"ziua": 2, "suma": 20.0, "tip": "mancare"}]
    assert isinstance(stiva_actualizata, list)

def test_wrapper():
    test_inserare()
    test_actualizare()
    test_stergere_cheltuieli_din_ziua_p()
    test_stergere_cheltuieli_din_intervalul_ziua1_ziua2()
    test_stergere_cheltuieli_dupa_tip()
    test_cheltuieli_mai_mari_decat_sumap()
    test_cheltuieli_mai_mici_sumap_inainte_ziuap()
    test_cheltuieli_dupa_tip()
    test_suma_totala_dupa_tip()
    test_max_suma_dupa_zii()
    test_cheltuiala_cu_sumap()
    # test_sortare_lista_cheltuieli_dupa_tip()
    test_undo()

def main():
    test_wrapper()

if __name__ == "__main__":
    main()

