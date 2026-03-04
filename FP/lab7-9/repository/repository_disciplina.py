from domeniu.disciplina import Disciplina
from exceptii.EroareRepo import EroareRepo


class RepoDisciplina:
    def __init__(self, calea_disciplina: str):
        self.__disciplina = {}
        self.__calea_discipline = calea_disciplina

    def adaugare_disciplina(self, disciplina: Disciplina):
        '''
        functie care adauga o disciplina noua
        :parem disciplina -> disciplina
        :return -
        '''
        self.__read_discipline_din_fisier()
        id_disciplina = disciplina.get_id_disciplina()

        if id_disciplina in self.__disciplina:
            raise EroareRepo("Id disciplina exista deja!\n")

        self.__disciplina[id_disciplina] = disciplina

        self.__salveaza_discipline_in_fisier()
        return id_disciplina

    def stergere_disciplina(self, id_disciplina: int):
        '''
        functie care sterge disciplina din repo
        :parem disciplina -> disciplina
        :return -
        '''
        self.__read_discipline_din_fisier()
        if id_disciplina not in self.__disciplina.keys():
            raise EroareRepo("Id disciplina nu exista!\n")

        del self.__disciplina[id_disciplina]
        self.__salveaza_discipline_in_fisier()

    def update_disciplina(self, disciplina: Disciplina):
        '''
        actualizeaza o disciplina deja inserata
        :parem disciplina -> disciplina
        :return -
        '''
        self.__read_discipline_din_fisier()
        id_disciplina = disciplina.get_id_disciplina()

        if id_disciplina not in self.__disciplina:
            raise EroareRepo("Id disciplina nu exista!\n")

        self.__disciplina[id_disciplina] = disciplina
        self.__salveaza_discipline_in_fisier()

    def cauta_disciplina(self, id_disciplina: int):
        '''
        cauta disciplina cu idul dat
        :parem id_disciplina -> idul disciplinei
        :return disciplina sau None daca nu exista
        '''
        self.__read_discipline_din_fisier()
        return self.__disciplina.get(id_disciplina)

    def get_all_disciplina(self):
        self.__read_discipline_din_fisier()
        return list(self.__disciplina.values())

    def creare_id_disciplina(self):
        self.__read_discipline_din_fisier()
        id_existente = list(self.__disciplina.keys())
        if len(id_existente) == 0:
            return 1
        id_existente.sort()
        id_expected = 1
        for id in id_existente:
            if id_expected != id:
                return id_expected

            id_expected += 1

        self.__salveaza_discipline_in_fisier()

        return id_expected

    def __read_discipline_din_fisier(self):
        """
        citeste din fisier disciplinele
        """
        with open(self.__calea_discipline, "r") as f:
            self.__disciplina = {}
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if linie == '':
                    continue
                parti = linie.split(',')
                id_disciplina = int(parti[0])
                nume_disciplina = parti[1].strip()
                nume_profesor = parti[2].strip()
                disciplina = Disciplina(
                    id_disciplina, nume_disciplina, nume_profesor)
                self.__disciplina[id_disciplina] = disciplina

    def __salveaza_discipline_in_fisier(self):
        """
        salveaza disciplinele in fisier
        """
        with open(self.__calea_discipline, "w") as f:
            for disciplina in self.__disciplina.values():
                id_disciplina = disciplina.get_id_disciplina()
                nume_disciplina = disciplina.get_nume_disciplina()
                nume_profesor = disciplina.get_nume_profesor()
                f.write(f"{id_disciplina},{nume_disciplina},{nume_profesor}\n")
