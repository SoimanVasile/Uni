def creeaza_cheltuiala(ziua:int ,suma:float,tip:str):
    '''
    functie care creeaza o cheltuiala cu ziua,suma si tip
    :parem ziua, un numar strict pozitiv, mai mic decat 31
    :parem suma, un numar real strict pozitiv
    :parem tip, un string care este una dintre " 
    :return o cheltuiala
    '''

    return {"ziua":ziua, "suma":suma, "tip":tip}

def get_ziua_cheltuiala(cheltuiala):
  '''
  functie care returneaza ziua cheltuielii
  :parem cheltuiala
  :return ziua cheltuielii
  '''
  return cheltuiala['ziua']

def get_suma_cheltuiala(cheltuiala):
  '''
  functie care returneaza suma cheltuielli
  :parem cheltuiala
  :return suma cheltuielii
  '''
  return cheltuiala['suma']

def get_tip_cheltuiala(cheltuiala):
  '''
  functie care returneaza tipul cheltuielii
  :parem cheltuiala
  :return tipul cheltuielii
  '''
  return cheltuiala['tip']

tipuri = ["mancare","intretinere","imbracaminte","telefon","altele"]

# def verificare_suma(ziua):
'''
functie care valideaza ziua inserata ca sa fie strict pozitiva si mai mic decat 32
:parem ziua, ziua
:return string gol daca ii bun
daca nu i bun atuncia o sa returneze "ziua invalida!"
'''
    # if ziua <0 and ziua>31
        # return "ziua invalida!"

    # return ""

def verificare_cheltuiala(cheltuiala):

  ''' functie care valideaza daca ziua este strict pozitiva si mai mic decat 31, tipul este "mancare","telefoane","intretinere","imbracaminte" sau "altele" si suma sa fie strict pozitiva
  :param cheltuiala: o cheltuiala
  :return -, daca datele sunt valide
  :raises: ValueError: cu mesajul string
    "ziua invalida!\n" - daca ziua <0 si ziua>31
    "tip invalid!\n" - daca tipul nu este una dintre "mancare","intretinere","imbracaminte","telefon" sau "altele"
    "suma invalida!\n" - daca suma <0
  '''
  
  erori =''
  if get_ziua_cheltuiala(cheltuiala)<0 or get_ziua_cheltuiala(cheltuiala)>31:
    erori += "ziua invalida!\n"
  if get_suma_cheltuiala(cheltuiala) < 0.0:
    erori += "suma invalida!\n"
  if get_tip_cheltuiala(cheltuiala) not in tipuri:
    erori += "tip invalid!\n"

  if erori!="":
    raise ValueError(erori)

def test_creeaza_cheltuiala():
  ziua = 2
  suma = 2.2
  tipul = "altele"
  cheltuiala = creeaza_cheltuiala(ziua,suma,tipul)
  assert get_ziua_cheltuiala(cheltuiala) == 2
  assert abs(get_suma_cheltuiala(cheltuiala) - suma) < 0.00001
  assert get_tip_cheltuiala(cheltuiala) == tipul
  
def test_verificare_cheltuiala():
  
  ziua = -1
  suma = -10.4
  tip = "asd"
  invalid_cheltuiala = creeaza_cheltuiala(ziua,suma,tip)
  try:
    verificare_cheltuiala(invalid_cheltuiala)
    assert False
  except ValueError as ve:
    assert str(ve) == "ziua invalida!\nsuma invalida!\ntip invalid!\n"

def test_wrapper():
  test_creeaza_cheltuiala()
  test_verificare_cheltuiala()

def main():
    # test_wrapper()
    cheltuiala = creeaza_cheltuiala(4,4.54,"altele")
    print(cheltuiala)

if __name__ == "__main__":
    main()
